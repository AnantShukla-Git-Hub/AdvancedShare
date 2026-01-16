#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include "../transfer/file.cpp"
#include "../network/socket_init.h"
#include "../common/config.h"

/* cout (buffered):
  -Output pehle buffer me jaata hai
  -Kab print hoga → later decide hota hai

   cerr (unbuffered):
  -Turant screen pe print hota hai
  -Crash se pehle bhi dikhta hai
  */

int main()
{
    // 1. Init socket system
    if (!init_socket()) {
        std::cerr << "Socket init failed\n";
        return 1;
    }

    // 2. Create server socket
    socket_t server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    // 3. Bind address
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    // 4. Listen
    listen(server_fd, 1);
    std::cout << "Receiver listening on port " << PORT << "...\n";

    // 5. Accept sender
    socket_t client_fd = accept(server_fd, nullptr, nullptr);
    if (client_fd < 0) {
        std::cerr << "Accept failed\n";
        return 1;
    }

    // 6. Receive request
    std::string incoming;
    char buffer[512];

    while (true) {
        int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (n <= 0) {
            std::cerr << "Receive failed or connection closed\n";
            return 1;
        }

        buffer[n] = '\0';
        incoming += buffer;

        if (incoming.find("END\n") != std::string::npos)
            break;
    }

    // 7. Parse request
    std::istringstream iss(incoming);
    std::string line;
    std::string filename;
    std::string message;
    uint64_t filesize=0;
    while(std::getline(iss,line)){
        if(line.rfind("REQ|",0)==0){
            size_t p1=line.find('|');
            size_t p2=line.find('|',p1+1);
            filename=line.substr(p1+1,p2-p1-1);
            filesize=std::stoull(line.substr(p2+1));
        }
        else if (line.rfind("MSG",0)==0){
            message=line.substr(4);
        }
        else if(line=="END"){
            break;
        }
    }

    // 8. Show file info
    std::cout << "\nIncoming file request:\n";
    std::cout << "File name: " << filename << "\n";
    std::cout<<std::fixed<<std::setprecision(2);
    double size_mb = filesize / (1024.0 * 1024.0);
    double size_gb = filesize / (1024.0 * 1024.0 * 1024.0);

    if (size_gb >= 1.0) {
        std::cout << "File size: " << size_gb << " GB\n";
    } 
    else {
        std::cout << "File size: " << size_mb << " MB\n";
    }
    if(!message.empty()){
        std::cout<<"Message: "<<message<<"\n";
    }
    std::cout<<"Accept? (Y/N): ";
    char choice;
    std::cin >> choice;

    // 9. Send response
    if (choice == 'Y' || choice == 'y') {
        send(client_fd, "ACC", 3, 0);
        receive_file(client_fd, filename, filesize);
    } else {
        send(client_fd, "REJ", 3, 0);
        std::cout << "Rejected.\n";
    }

    close_socket(client_fd);
    close_socket(server_fd);
    cleanup_socket();
    return 0;
}

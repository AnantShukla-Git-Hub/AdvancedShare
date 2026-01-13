#include <iostream>
#include <string>
#include "../common/utils.h"
#include "../network/socket_init.h"
#include "../common/config.h"

int main()
{
    if (!init_socket()) {
        std::cerr << "Socket init failed\n";
        return 1;
    }

    socket_t sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    std::string ip, message;
    std::cout << "Hello, Welcome to Anant's Sharing App!\n";
    std::cout << "Enter receiver IP: ";
    std::cin >> ip;
    std::cin.ignore();
    std::string file_path;
    std::cout << "Enter file path: ";
    std::getline(std::cin, file_path);

    
    
    if (!file_exists(file_path)) {
        std::cerr << "File does not exist\n";
        close_socket(sock);
        cleanup_socket();
        return 1;
    }
    std::string filename;
    size_t pos = file_path.find_last_of("/\\");
    if (pos != std::string::npos)
        filename = file_path.substr(pos + 1);
    else
        filename = file_path;
    uint64_t filesize = get_file_size(file_path);

    char choice;
    
    std::cout << "Do you want to send a message with file? (Y/N): ";
    std::cin >> choice;
    std::cin.ignore();
    if (choice == 'Y' || choice == 'y') {
        std::cout << "Enter message: ";
        std::getline(std::cin, message);
    }

    //sockaddr_in server{}-->this contain IP address and port number of server and adress family(IPv4-we are using/IPv6)
    sockaddr_in server{};

    //server.sin--> ye server ka address store karega
    server.sin_family = AF_INET;
    //htons(PORT)-->host to network short- ye ensure karta hai ki port number network byte order me ho(jab data network pe bheja jata hai to ek specific order me bheja jata hai jise network byte order kehte hain)
    server.sin_port = htons(PORT);
    //.c_str()-->ye C-style string return karta hai(jisme null terminator hota hai)
    //inet_addr-->ye function IP address ko convert karta hai human-readable format se jo hum enter karte hain usse ek binary format me jo network operations ke liye suitable hota hai
    //ip--> ye user dwara enter kiya gaya IP address hai
    //.s_addr--> ye server address ko store karta hai jo inet_addr function se milta hai
    //.sin_addr--> ye server ka IP address store karega
    server.sin_addr.s_addr = inet_addr(ip.c_str());

    //connect--> ye function client socket ko server se connect karta hai
    //sock--> ye client socket hai jo humne create kiya hai
    //(sockaddr*)&server--> ye server ka address hai jise hum connect karna chahte hain
    //cerr-->standard error stream hai jo error messages ko display karne ke liye use hota hai
    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Connection failed\n";
        close_socket(sock);
        cleanup_socket();
        return 1;
    }

    std::string payload;
    payload += "REQ " + filename + " " + std::to_string(filesize) + "\n";
    if (!message.empty()) {
        payload += "MSG " + message + "\n";
    }
    payload+="END\n";

    send(sock, payload.c_str(), payload.size(), 0);
    char response[16]{};
    
    int r = recv(sock, response, sizeof(response) - 1, 0);
    if (r <= 0) {
    std::cerr << "Connection closed before response\n";
        close_socket(sock);
        cleanup_socket();
        return 1;
    }
    response[r] = '\0';  // null-terminate
    std::string reply(response);
    if (reply.find("ACC") != std::string::npos) {
        std::cout << "Receiver ACCEPTED\n";
    } else if (reply.find("REJ") != std::string::npos) {
        std::cout << "Receiver REJECTED\n";
    } else {
        std::cerr << "Unknown response: " << reply << "\n";
    }

    close_socket(sock);
    cleanup_socket();
    return 0;
}

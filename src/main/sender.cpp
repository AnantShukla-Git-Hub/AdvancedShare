#include <iostream>
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
    std::cout << "Enter message: ";
    std::getline(std::cin, message);

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
        return 1;
    }

    //send--> ye function data ko socket ke through bhejne ke liye use hota hai
    send(sock, message.c_str(), message.size(), 0);
    std::cout << "Message sent successfully\n";

    close_socket(sock);
    cleanup_socket();
    return 0;
}

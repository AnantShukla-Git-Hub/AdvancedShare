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
    std::cout << "Enter receiver IP: ";
    std::cin >> ip;
    std::cin.ignore();
    std::cout << "Enter message: ";
    std::getline(std::cin, message);

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Connection failed\n";
        return 1;
    }

    send(sock, message.c_str(), message.size(), 0);
    std::cout << "Message sent successfully\n";

    close_socket(sock);
    cleanup_socket();
    return 0;
}

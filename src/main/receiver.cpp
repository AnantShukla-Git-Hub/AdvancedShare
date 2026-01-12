#include <iostream>
#include "../network/socket_init.h"
#include "../common/config.h"

int main()
{
    if (!init_socket()) {
        std::cerr << "Socket init failed\n";
        return 1;
    }

    socket_t server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    listen(server_fd, 1);
    std::cout << "Receiver started. Waiting for connection...\n";

    socket_t client_fd = accept(server_fd, nullptr, nullptr);
    if (client_fd < 0) {
        std::cerr << "Accept failed\n";
        return 1;
    }

    char buffer[BUFFER_SIZE]{};
    recv(client_fd, buffer, BUFFER_SIZE, 0);
    std::cout << "Message received: " << buffer << "\n";

    close_socket(client_fd);
    close_socket(server_fd);
    cleanup_socket();
    return 0;
}

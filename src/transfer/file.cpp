#include <fstream>
#include <iostream>
#include <cstring>

#include "../common/config.h"
#include "../common/utils.h"
#include "../network/socket_init.h"

bool send_file(socket_t sock, const std::string& path, uint64_t filesize)
{
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file\n";
        return false;
    }

    char buffer[CHUNK_SIZE];
    uint64_t sent = 0;

    while (sent < filesize) {
        file.read(buffer, CHUNK_SIZE);
        std::streamsize n = file.gcount();

        if (n <= 0) break;

        int s = send(sock, buffer, (int)n, 0);
        if (s <= 0) {
            std::cerr << "Send failed\n";
            return false;
        }

        sent += s;
        int percent = (int)((sent * 100) / filesize);
        std::cout << "\rSending: " << percent << "%" << std::flush;
    }

    std::cout << "\nFile sent successfully\n";
    return true;
}

bool receive_file(socket_t sock,
                  const std::string& filename,
                  uint64_t filesize)
{
    ensure_directory(RECEIVE_DIR);
    std::string out_path = std::string(RECEIVE_DIR) + "/" + filename;

    std::ofstream out(out_path, std::ios::binary);
    if (!out) {
        std::cerr << "Failed to create output file\n";
        return false;
    }

    char buffer[CHUNK_SIZE];
    uint64_t received = 0;

    while (received < filesize) {
        int n = recv(sock, buffer, CHUNK_SIZE, 0);
        if (n <= 0) {
            std::cerr << "Receive failed\n";
            return false;
        }

        out.write(buffer, n);
        received += n;

        int percent = (int)((received * 100) / filesize);
        std::cout << "\rReceiving: " << percent << "%" << std::flush;
    }

    std::cout << "\nFile received successfully\n";
    return true;
}

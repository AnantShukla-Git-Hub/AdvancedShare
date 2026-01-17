#pragma once
#include <string>
#include <functional>
#include "../common/config.h"
#include "../network/socket_init.h"

bool send_file(
    unsigned int sock,
    const std::string& path,
    unsigned long long filesize,
    std::function<void(unsigned long long)> on_chunk_sent
);

bool receive_file(
    unsigned int sock,
    const std::string& path,
    unsigned long long filesize
);

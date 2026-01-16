#pragma once
#include <string>
#include <functional>
#include "../common/config.h"
#include "../network/socket_init.h"

bool send_file(
    socket_t sock,
    const std::string& path,
    uint64_t filesize,
    std::function<void(uint64_t)> on_chunk_sent
);

bool receive_file(
    socket_t sock,
    const std::string& path,
    uint64_t filesize
);

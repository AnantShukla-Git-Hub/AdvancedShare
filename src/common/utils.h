#pragma once
#include <string>
#include <cstdint>

uint64_t get_file_size(const std::string& path);
bool file_exists(const std::string& path);
void compiler_warning();

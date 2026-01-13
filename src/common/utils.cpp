#include "utils.h"
#include <iostream>

#if __cplusplus >= 201703L
    // ✅ Modern compiler
    #include <filesystem>
    namespace fs = std::filesystem;

    uint64_t get_file_size(const std::string& path) {
        return fs::file_size(path);
    }

    bool file_exists(const std::string& path) {
        return fs::exists(path);
    }

    void compiler_warning() {
        // no warning needed
    }

#else
    // ⚠️ Legacy compiler fallback
    #include <sys/stat.h>

    uint64_t get_file_size(const std::string& path) {
        struct stat st;
        if (stat(path.c_str(), &st) != 0) return 0;
        return st.st_size;
    }

    bool file_exists(const std::string& path) {
        struct stat st;
        return stat(path.c_str(), &st) == 0;
    }

    void compiler_warning() {
        static bool shown = false;
        if (!shown) {
            std::cerr <<
            "[WARNING] Your compiler does NOT fully support C++17.\n"
            "[WARNING] Using legacy filesystem fallback.\n"
            "[WARNING] File operations may be slower.\n"
            "[WARNING] Recommended: GCC >= 9 or MSVC >= 2019.\n\n";
            shown = true;
        }
    }
#endif

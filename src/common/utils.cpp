#include "utils.h"
#include <iostream>
//cerrno is used to report error numbers from system calls and some library functions
#include <cerrno>
/*define ho rha ki cpp compiler if c++17 hai to good else old compiler user kar lo */
#if __cplusplus >= 201703L
    #include <filesystem>
    //namespace fs ko std::filesystem ke naam se refer karne ke liye-->alias
    namespace fs = std::filesystem;
#else
    #ifdef _WIN32
        #include <sys/stat.h>   // _stat-->file info ke liye
        #include <direct.h>     // _mkdir-->directory or folder create karne ke liye
    #else //if linux or macOS
        #include <sys/stat.h>   // stat-->file info ke liye
        #include <unistd.h>     //mkdir-->directory or folder create karne ke liye
    #endif //os check end
#endif

//unit64_t-->64 bit unsigned integer type-- large file store ke liye safe
//cont --> function ke andar path change nahi hoga
uint64_t get_file_size(const std::string& path) {
#if __cplusplus >= 201703L
    return fs::file_size(path);
#else
    #ifdef _WIN32
        struct _stat st;
        if (_stat(path.c_str(), &st) != 0) return 0;
        return static_cast<uint64_t>(st.st_size);
    #else
        struct stat st;
        if (stat(path.c_str(), &st) != 0) return 0;
        return st.st_size;
    #endif
#endif
}

bool file_exists(const std::string& path) {
#if __cplusplus >= 201703L
    return fs::exists(path);
#else
    #ifdef _WIN32
        struct _stat st;
        return _stat(path.c_str(), &st) == 0;
    #else
        struct stat st;
        return stat(path.c_str(), &st) == 0;
    #endif
#endif
}

bool ensure_directory(const std::string& dir) {
#if __cplusplus >= 201703L
    if (!fs::exists(dir))
        return fs::create_directories(dir);
    return true;
#else
    #ifdef _WIN32
        return _mkdir(dir.c_str()) == 0 || errno == EEXIST;
    #else
        return mkdir(dir.c_str(), 0755) == 0 || errno == EEXIST;
    #endif
#endif
}

void compiler_warning() {
#if __cplusplus < 201703L
    static bool shown = false;
    if (!shown) {
        std::cerr <<
        "[WARNING] Your compiler does NOT fully support C++17.\n"
        "[WARNING] Using legacy filesystem fallback.\n\n";
        shown = true;
    }
#endif
}

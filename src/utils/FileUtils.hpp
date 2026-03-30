#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

class FileUtils {
public:
    static bool create_directory(const std::string& path) {
        if (fs::exists(path)) return true;
        try {
            return fs::create_directories(path);
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error creating directory " << path << ": " << e.what() << std::endl;
            return false;
        }
    }

    static bool write_file(const std::string& path, const std::string& content) {
        std::ofstream file(path);
        if (!file.is_open()) {
            std::cerr << "Error writing file " << path << std::endl;
            return false;
        }
        file << content;
        file.close();
        return true;
    }

    static void set_executable(const std::string& path) {
        fs::permissions(path, fs::perms::owner_all | fs::perms::group_read | fs::perms::others_read);
    }
};

#endif

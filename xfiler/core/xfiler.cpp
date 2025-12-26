#include "xfiler.h"
#include <iostream>
#include <fstream>
#include "xfilerrorhandler.h"
#include <filesystem>

uint64_t XFile::calculateHash(const std::string& path2file) const {
    std::ifstream file(path2file, std::ios::binary);
    if (!file) throw XFileError(path2file);
    uint64_t hash = OFFSET;
    char byte;
    while (file.get(byte)) {
        hash ^= static_cast<unsigned char>(byte);
        hash *= PRIME;
    }
    return hash;
}

bool XFile::verifyData(const std::string& path2file, uint64_t& expectedHash) {
    if (!std::filesystem::exists(path2file) || !std::filesystem::is_regular_file(path2file))
        throw XFileError(path2file);
    return calculateHash(path2file) == expectedHash;
}
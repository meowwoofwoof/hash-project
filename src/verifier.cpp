/**
 * @file verifier.cpp
 * @brief Реализация функции проверки хэш-алгоритмов.
 */

#include "../include/verifier.h"
#include "../include/hash.h"

bool verify_md5(const std::string& path, const std::string& expected) {
    std::string actual = md5_file(path);
    return actual == expected;
}

bool verify_sha1(const std::string& path, const std::string& expected) {
    std::string actual = sha1_file(path);
    return actual == expected;
}

bool verify_sha256(const std::string& path, const std::string& expected) {
    std::string actual = sha256_file(path);
    return actual == expected;
}
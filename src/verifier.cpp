/**
 * @file verifier.cpp
 * @brief Реализация функции проверки MD5-хеша.
 */

#include "verifier.h"
#include "hash.h"

/**
 * @brief Проверяет соответствие MD5-хеша файла ожидаемому значению.
 *
 * Вычисляет MD5-хеш содержимого файла и сравнивает его с заданным хешем.
 *
 * @param path Путь к файлу для проверки.
 * @param expected Ожидаемый MD5-хеш в виде строки (в нижнем регистре).
 * @return true — если хеш совпадает с expected; false — иначе.
 */
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
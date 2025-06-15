#ifndef HASH_H
#define HASH_H

#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <array>
#include <cstdint>
#include <algorithm>
#include <string>

bool verify_md5(const std::string& filepath, const std::string& hash);
bool verify_sha1(const std::string& filepath, const std::string& hash);
bool verify_sha256(const std::string& filepath, const std::string& hash);

/**
 * @brief Вычисляет MD5‑хеш указанного файла.
 *
 * Файл читается в бинарном режиме и дополняется согласно спецификации MD5.
 * При невозможности открыть файл функция возвращает пустую строку.
 *
 * @param filepath Полный или относительный путь к файлу.
 * @return 32‑символьная строка в нижнем регистре (hex‑представление MD5).
 */
std::string md5_file(const std::string& filepath);

/**
 * @brief Вычисляет SHA‑1‑хеш указанного файла.
 *
 * Аналогична md5_file, но использует алгоритм SHA‑1.
 *
 * @param filepath Полный или относительный путь к файлу.
 * @return 40‑символьная строка в нижнем регистре (hex‑представление SHA‑1).
 */
std::string sha1_file(const std::string& filepath);

/**
 * @brief Вычисляет SHA‑256‑хеш указанного файла.
 *
 * Аналогична md5_file, но использует алгоритм SHA‑256.
 *
 * @param filepath Полный или относительный путь к файлу.
 * @return 64‑символьная строка в нижнем регистре (hex‑представление SHA‑256).
 */
std::string sha256_file(const std::string& filepath);

namespace md5_internal {
    extern const std::array<uint32_t, 64> K;
    extern const std::array<uint32_t, 64> S;

    uint32_t left_rotate(uint32_t x, uint32_t c);
    void md5_transform(std::array<uint32_t, 4>& H, const std::array<uint8_t, 64>& block);
}

#endif

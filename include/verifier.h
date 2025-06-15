#ifndef VERIFIER_H
#define VERIFIER_H

#include <string>

bool verify_md5(const std::string& filepath, const std::string& hash);
bool verify_sha1(const std::string& filepath, const std::string& hash);
bool verify_sha256(const std::string& filepath, const std::string& hash);
/**
 * @brief Проверяет совпадение хеша файла с ожидаемым значением.
 *
 * Функция вычисляет хеш указанным алгоритмом и сравнивает
 * результат с эталонной строкой, заданной пользователем.
 *
 * @param filepath Путь к проверяемому файлу.
 * @param expected Ожидаемый хеш в нижнем регистре (hex).
 * @param algo     Строка‑идентификатор алгоритма: "md5", "sha1" или "sha256".
 * @return true  — если вычисленный хеш совпадает c expected;  
 *         false — в противном случае или при неизвестном алгоритме.
 */
 
bool verify_md5(const std::string& path, const std::string& expected);
bool verify_sha1(const std::string& path, const std::string& expected);
bool verify_sha256(const std::string& path, const std::string& expected);

#endif
#ifndef VERIFIER_H
#define VERIFIER_H

#include <string>

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

/**
 * @brief Проверяет соответствие SHA-1-хеша файла ожидаемому значению.
 *
 * Вычисляет SHA-1-хеш содержимого файла и сравнивает его с заданным хешем.
 *
 * @param path Путь к файлу для проверки.
 * @param expected Ожидаемый SHA-1-хеш в виде строки (в нижнем регистре).
 * @return true — если хеш совпадает с expected; false — иначе.
 */
bool verify_sha1(const std::string& path, const std::string& expected);

/**
 * @brief Проверяет соответствие SHA-256-хеша файла ожидаемому значению.
 *
 * Вычисляет SHA-256-хеш содержимого файла и сравнивает его с заданным хешем.
 *
 * @param path Путь к файлу для проверки.
 * @param expected Ожидаемый SHA-256-хеш в виде строки (в нижнем регистре).
 * @return true — если хеш совпадает с expected; false — иначе.
 */
bool verify_sha256(const std::string& path, const std::string& expected);

#endif
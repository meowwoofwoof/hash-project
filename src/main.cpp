/**
 * @file main.cpp
 * @brief Консольное приложение для вычисления и проверки хешей файлов.
 *
 * Поддерживаются алгоритмы MD5, SHA‑1, SHA‑256. Реализация всех хеш‑функций написана вручную.
 * Пользователь может выбрать режим: получение хеша или проверка соответствия хеша.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "hash.h"

/**
 * @brief Очищает экран консоли.
 *
 * Использует системную команду `cls` для Windows.
 */
void clear_screen() {
    system("cls");
}

/**
 * @brief Показывает меню возврата в главное меню или выхода из программы.
 */
void wait_menu_or_exit() {
    while (true) {
        std::cout << "\nwhat next?\n";
        std::cout << "[1] return to main menu\n";
        std::cout << "[0] exit\n";
        std::cout << "> ";
        int option;
        std::cin >> option;
        if (option == 1) return;
        else if (option == 0) exit(0);
        else {
            std::cout << "invalid choice.\n";
        }
    }
}

/**
 * @brief Отображает меню выбора алгоритма хеширования.
 *
 * @return Название алгоритма ("md5", "sha1", "sha256") или пустую строку для выхода.
 */
std::string select_algorithm() {
    while (true) {
        clear_screen();
        std::cout << "select algorithm:\n";
        std::cout << "[1] md5\n";
        std::cout << "[2] sha1\n";
        std::cout << "[3] sha256\n";
        std::cout << "[0] back\n";
        std::cout << "> ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: return "md5";
            case 2: return "sha1";
            case 3: return "sha256";
            case 0: return "";
            default: std::cout << "invalid choice.\n";
        }
    }
}

/**
 * @brief Вычисляет хеш файла по указанному алгоритму.
 *
 * @param algo Алгоритм ("md5", "sha1", "sha256").
 * @param filepath Путь к файлу.
 * @return Хеш в формате hex или пустая строка при ошибке.
 */
std::string get_hash(const std::string& algo, const std::string& filepath) {
    if (algo == "md5") return md5_file(filepath);
    if (algo == "sha1") return sha1_file(filepath);
    if (algo == "sha256") return sha256_file(filepath);
    return "";
}

/**
 * @brief Интерфейс режима получения хеша.
 *
 * Пользователь выбирает алгоритм, файл и способ вывода хеша (в консоль или файл).
 */
void run_hash() {
    std::string algo = select_algorithm();
    if (algo.empty()) return;

    clear_screen();
    std::string filepath;
    std::cout << "enter file path:\n> ";
    std::cin >> filepath;

    clear_screen();
    std::cout << "select output:\n[1] console\n[2] file\n[0] back\n> ";
    int output;
    std::cin >> output;
    if (output == 0) return;

    std::string hash = get_hash(algo, filepath);

    clear_screen();
    if (output == 1) {
        std::cout << "hash: " << hash << "\n";
    } else if (output == 2) {
        std::string outpath;
        std::cout << "enter output file name:\n> ";
        std::cin >> outpath;
        std::ofstream out(outpath);
        if (!out) {
            std::cerr << "file write error.\n";
            wait_menu_or_exit();
            return;
        }
        out << hash;
        std::cout << "hash saved to file.\n";
    } else {
        std::cerr << "invalid output option.\n";
        wait_menu_or_exit();
        return;
    }

    wait_menu_or_exit();
}

/**
 * @brief Интерфейс режима проверки хеша.
 *
 * Пользователь выбирает алгоритм, файл и источник ожидаемого хеша (вручную или из файла).
 * Затем выполняется сравнение хешей.
 */
void run_verify() {
    std::string algo = select_algorithm();
    if (algo.empty()) return;

    clear_screen();
    std::string filepath;
    std::cout << "enter file path:\n> ";
    std::cin >> filepath;

    clear_screen();
    std::cout << "hash input:\n[1] manual\n[2] from file\n[0] back\n> ";
    int input;
    std::cin >> input;
    if (input == 0) return;

    std::string expected;
    if (input == 1) {
        std::cout << "enter expected hash:\n> ";
        std::cin >> expected;
    } else if (input == 2) {
        std::string hashfile;
        std::cout << "enter hash file path:\n> ";
        std::cin >> hashfile;
        std::ifstream in(hashfile);
        if (!in) {
            std::cerr << "file read error.\n";
            wait_menu_or_exit();
            return;
        }
        std::getline(in, expected);
    } else {
        std::cerr << "invalid input option.\n";
        wait_menu_or_exit();
        return;
    }

    std::string actual = get_hash(algo, filepath);

    clear_screen();
    if (expected == actual) {
        std::cout << "hash matches.\n";
    } else {
        std::cout << "hash does not match.\n";
        std::cout << "expected:  " << expected << "\n";
        std::cout << "actual:    " << actual << "\n";
    }

    wait_menu_or_exit();
}

/**
 * @brief Главная функция. Отображает основное меню и запускает выбранный режим.
 *
 * Цикл продолжается до тех пор, пока пользователь не выберет выход.
 */
int main() {
    while (true) {
        clear_screen();
        std::cout << "=== main menu ===\n";
        std::cout << "[1] get hash\n";
        std::cout << "[2] verify hash\n";
        std::cout << "[0] exit\n";
        std::cout << "> ";
        int mode;
        std::cin >> mode;

        switch (mode) {
            case 1: run_hash(); break;
            case 2: run_verify(); break;
            case 0: return 0;
            default: std::cout << "invalid choice.\n";
        }
    }
}
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "../include/hash.h"
#include <filesystem>

// Вспомогательная функция для создания тестового файла
void create_test_file(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
}

// Вспомогательная функция для удаления тестового файла
void remove_test_file(const std::string& filename) {
    std::filesystem::remove(filename);
}

TEST_SUITE("Hash Functions Tests") {
    TEST_CASE("MD5 Hash") {
        const std::string test_file = "md5_test.txt";
        const std::string test_content = "hello";
        const std::string empty_file = "empty_md5.txt";
        
        SUBCASE("MD5 correct hash for known input") {
            create_test_file(test_file, test_content);
            std::string hash = md5_file(test_file);
            CHECK(hash == "5d41402abc4b2a76b9719d911017c592");
            remove_test_file(test_file);
        }

        SUBCASE("MD5 empty file") {
            create_test_file(empty_file, "");
            std::string hash = md5_file(empty_file);
            CHECK(hash == "d41d8cd98f00b204e9800998ecf8427e");
            remove_test_file(empty_file);
        }

        SUBCASE("MD5 non-existent file") {
            std::string hash = md5_file("non_existent_file.txt");
            CHECK(hash.empty());
        }
    }

    TEST_CASE("SHA1 Hash") {
        const std::string test_file = "sha1_test.txt";
        const std::string test_content = "hello";
        const std::string empty_file = "empty_sha1.txt";
        
        SUBCASE("SHA1 correct hash for known input") {
            create_test_file(test_file, test_content);
            std::string hash = sha1_file(test_file);
            CHECK(hash == "aaf4c61ddcc5e8a2dabede0f3b482cd9aea9434d");
            remove_test_file(test_file);
        }

        SUBCASE("SHA1 empty file") {
            create_test_file(empty_file, "");
            std::string hash = sha1_file(empty_file);
            CHECK(hash == "da39a3ee5e6b4b0d3255bfef95601890afd80709");
            remove_test_file(empty_file);
        }

        SUBCASE("SHA1 non-existent file") {
            std::string hash = sha1_file("non_existent_file.txt");
            CHECK(hash.empty());
        }
    }

    TEST_CASE("SHA256 Hash") {
        const std::string test_file = "sha256_test.txt";
        const std::string test_content = "hello";
        const std::string empty_file = "empty_sha256.txt";
        
        SUBCASE("SHA256 correct hash for known input") {
            create_test_file(test_file, test_content);
            std::string hash = sha256_file(test_file);
            CHECK(hash == "2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824");
            remove_test_file(test_file);
        }

        SUBCASE("SHA256 empty file") {
            create_test_file(empty_file, "");
            std::string hash = sha256_file(empty_file);
            CHECK(hash == "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
            remove_test_file(empty_file);
        }

        SUBCASE("SHA256 non-existent file") {
            std::string hash = sha256_file("non_existent_file.txt");
            CHECK(hash.empty());
        }
    }

    TEST_CASE("Hash Verification") {
        const std::string test_file = "verify_test.txt";
        const std::string test_content = "test content";
        
        SUBCASE("MD5 verification correct") {
            create_test_file(test_file, test_content);
            std::string hash = md5_file(test_file);
            bool result = verify_md5(test_file, hash);
            CHECK(result == true);
            remove_test_file(test_file);
        }

        SUBCASE("MD5 verification incorrect") {
            create_test_file(test_file, test_content);
            bool result = verify_md5(test_file, "incorrecthash123");
            CHECK(result == false);
            remove_test_file(test_file);
        }

        SUBCASE("SHA1 verification correct") {
            create_test_file(test_file, test_content);
            std::string hash = sha1_file(test_file);
            bool result = verify_sha1(test_file, hash);
            CHECK(result == true);
            remove_test_file(test_file);
        }

        SUBCASE("SHA1 verification incorrect") {
            create_test_file(test_file, test_content);
            bool result = verify_sha1(test_file, "incorrecthash123");
            CHECK(result == false);
            remove_test_file(test_file);
        }

        SUBCASE("SHA256 verification correct") {
            create_test_file(test_file, test_content);
            std::string hash = sha256_file(test_file);
            bool result = verify_sha256(test_file, hash);
            CHECK(result == true);
            remove_test_file(test_file);
        }

        SUBCASE("SHA256 verification incorrect") {
            create_test_file(test_file, test_content);
            bool result = verify_sha256(test_file, "incorrecthash123");
            CHECK(result == false);
            remove_test_file(test_file);
        }
    }
}
/**
 * @file hash.cpp
 * @brief Реализация алгоритмов хеширования MD5, SHA-1 и SHA-256 для проверки целостности файлов.
 */

#include "hash.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <array>
#include <cstdint>
#include <algorithm>

// ======================= MD5 =======================
namespace md5_internal {
    const std::array<uint32_t, 64> K = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    };

    const std::array<uint32_t, 64> S = {
        7,12,17,22, 7,12,17,22, 7,12,17,22, 7,12,17,22,
        5, 9,14,20, 5, 9,14,20, 5, 9,14,20, 5, 9,14,20,
        4,11,16,23, 4,11,16,23, 4,11,16,23, 4,11,16,23,
        6,10,15,21, 6,10,15,21, 6,10,15,21, 6,10,15,21
    };

    uint32_t left_rotate(uint32_t x, uint32_t c) {
        return (x << c) | (x >> (32 - c));
    }

    void md5_transform(std::array<uint32_t, 4>& H, const std::array<uint8_t, 64>& block) {
        uint32_t A = H[0], B = H[1], C = H[2], D = H[3], F, g, M[16];
        for (int i = 0; i < 16; ++i)
            M[i] = block[i*4] | (block[i*4+1] << 8) | (block[i*4+2] << 16) | (block[i*4+3] << 24);
        for (int i = 0; i < 64; ++i) {
            if (i < 16) { F = (B & C) | (~B & D); g = i; }
            else if (i < 32) { F = (D & B) | (~D & C); g = (5*i + 1) % 16; }
            else if (i < 48) { F = B ^ C ^ D; g = (3*i + 5) % 16; }
            else { F = C ^ (B | ~D); g = (7*i) % 16; }
            F += A + K[i] + M[g]; A = D; D = C; C = B; B += left_rotate(F, S[i]);
        }
        H[0] += A; H[1] += B; H[2] += C; H[3] += D;
    }
}

std::string md5_file(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) return "";

    std::array<uint32_t, 4> H = {
        0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476
    };

    std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    uint64_t original_size = data.size();
    data.push_back(0x80);
    while ((data.size() % 64) != 56) data.push_back(0x00);
    uint64_t bit_len = original_size * 8;
    for (int i = 0; i < 8; ++i)
        data.push_back((bit_len >> (8 * i)) & 0xFF);

    for (size_t i = 0; i < data.size(); i += 64) {
        std::array<uint8_t, 64> block;
        std::copy(data.begin() + i, data.begin() + i + 64, block.begin());
        md5_internal::md5_transform(H, block);
    }

    std::ostringstream result;
    for (uint32_t h : H)
        for (int i = 0; i < 4; ++i)
            result << std::hex << std::setw(2) << std::setfill('0') << ((h >> (8 * i)) & 0xFF);
    return result.str();
}

// ======================= SHA1 =======================
std::string sha1_file(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) return "";

    std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    uint64_t original_size = data.size();
    data.push_back(0x80);
    while ((data.size() % 64) != 56) data.push_back(0x00);
    uint64_t bit_len = original_size * 8;
    for (int i = 0; i < 8; ++i)
        data.push_back((bit_len >> (8 * (7 - i))) & 0xFF);

    uint32_t h0 = 0x67452301, h1 = 0xEFCDAB89, h2 = 0x98BADCFE, h3 = 0x10325476, h4 = 0xC3D2E1F0;

    for (size_t i = 0; i < data.size(); i += 64) {
        uint32_t w[80] = {};
        for (int t = 0; t < 16; ++t)
            w[t] = (data[i + 4*t] << 24) | (data[i + 4*t + 1] << 16) | (data[i + 4*t + 2] << 8) | data[i + 4*t + 3];
        for (int t = 16; t < 80; ++t)
            w[t] = ((w[t-3] ^ w[t-8] ^ w[t-14] ^ w[t-16]) << 1) | ((w[t-3] ^ w[t-8] ^ w[t-14] ^ w[t-16]) >> 31);

        uint32_t a = h0, b = h1, c = h2, d = h3, e = h4;
        for (int t = 0; t < 80; ++t) {
            uint32_t f, k;
            if (t < 20) { f = (b & c) | (~b & d); k = 0x5A827999; }
            else if (t < 40) { f = b ^ c ^ d; k = 0x6ED9EBA1; }
            else if (t < 60) { f = (b & c) | (b & d) | (c & d); k = 0x8F1BBCDC; }
            else { f = b ^ c ^ d; k = 0xCA62C1D6; }

            uint32_t temp = ((a << 5) | (a >> 27)) + f + e + k + w[t];
            e = d; d = c; c = (b << 30) | (b >> 2); b = a; a = temp;
        }

        h0 += a; h1 += b; h2 += c; h3 += d; h4 += e;
    }

    std::ostringstream result;
    for (uint32_t h : {h0, h1, h2, h3, h4})
        result << std::hex << std::setw(8) << std::setfill('0') << h;
    return result.str();
}

// ======================= SHA256 =======================
std::string sha256_file(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) return "";

    std::vector<uint8_t> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    uint64_t original_size = data.size();
    data.push_back(0x80);
    while ((data.size() % 64) != 56) data.push_back(0x00);
    uint64_t bit_len = original_size * 8;
    for (int i = 0; i < 8; ++i)
        data.push_back((bit_len >> (8 * (7 - i))) & 0xFF);

    uint32_t h[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    const uint32_t k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    for (size_t i = 0; i < data.size(); i += 64) {
        uint32_t w[64] = {};
        for (int t = 0; t < 16; ++t)
            w[t] = (data[i + 4*t] << 24) | (data[i + 4*t + 1] << 16) | (data[i + 4*t + 2] << 8) | data[i + 4*t + 3];
        for (int t = 16; t < 64; ++t) {
            uint32_t s0 = ((w[t-15] >> 7) | (w[t-15] << 25)) ^ ((w[t-15] >> 18) | (w[t-15] << 14)) ^ (w[t-15] >> 3);
            uint32_t s1 = ((w[t-2] >> 17) | (w[t-2] << 15)) ^ ((w[t-2] >> 19) | (w[t-2] << 13)) ^ (w[t-2] >> 10);
            w[t] = w[t-16] + s0 + w[t-7] + s1;
        }

        uint32_t a = h[0], b = h[1], c = h[2], d = h[3];
        uint32_t e = h[4], f = h[5], g = h[6], hh = h[7];
        for (int t = 0; t < 64; ++t) {
            uint32_t S1 = ((e >> 6) | (e << 26)) ^ ((e >> 11) | (e << 21)) ^ ((e >> 25) | (e << 7));
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t temp1 = hh + S1 + ch + k[t] + w[t];
            uint32_t S0 = ((a >> 2) | (a << 30)) ^ ((a >> 13) | (a << 19)) ^ ((a >> 22) | (a << 10));
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;

            hh = g; g = f; f = e;
            e = d + temp1; d = c; c = b; b = a;
            a = temp1 + temp2;
        }

        h[0] += a; h[1] += b; h[2] += c; h[3] += d;
        h[4] += e; h[5] += f; h[6] += g; h[7] += hh;
    }

    std::ostringstream result;
    for (uint32_t v : h)
        result << std::hex << std::setw(8) << std::setfill('0') << v;
    return result.str();
}

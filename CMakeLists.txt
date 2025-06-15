cmake_minimum_required(VERSION 3.10)
project(hash_verifier)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

include_directories(src)

add_executable(hash_verifier
    src/main.cpp
    src/hash.cpp
    src/verifier.cpp
)

add_executable(tests
    tests/test_verifier.cpp
    src/hash.cpp
    src/verifier.cpp
)

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_test(NAME run_tests COMMAND tests)

cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_C_COMPILER gcc)

set(CMAKE_C_STANDARD 99)

set(CMAKE_BUILD_TYPE Release)

project(njvm C)

include(cmake/FetchCMocka.cmake)

add_compile_options(-g -Wall -pedantic)

include_directories(include)

add_executable(
    njvm 
    src/njvm.c 
    src/cpu/processor.c 
    src/cpu/instruction.c 
    src/cpu/debugger.c 
    src/memory/ir.c 
    src/memory/stack.c
    src/memory/sda.c
    src/utils/utils.c
)

enable_testing()

add_executable(tests test/test.c)

target_link_libraries(tests PRIVATE cmocka-static)

add_test(Test tests)

cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_COMPILER gcc)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_TYPE Release)

project(njvm C)

add_compile_options(-g -Wall -pedantic)

include_directories(include)

enable_testing()

add_executable(
    njvm 
    src/njvm.c 
    src/cpu/control_unit.c 
    src/cpu/instructions.c 
    src/memory/program_memory.c 
    src/memory/stack.c
    src/memory/static_data_area.c
)

add_executable(tests test/test.c)

add_test(Test tests)

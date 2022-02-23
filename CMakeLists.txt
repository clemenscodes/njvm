cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_COMPILER gcc)

set(CMAKE_C_STANDARD 99)

set(EXECUTABLE_OUTPUT_PATH "../")

project(njvm C)

add_compile_options(-g -Wall -pedantic)

add_executable(
    njvm 
    src/njvm.c 
    src/boot/boot.c 
    src/cpu/control_unit.c 
    src/cpu/instructions.c 
    src/memory/program_memory.c 
    src/memory/stack.c
    src/memory/static_data_area.c
)

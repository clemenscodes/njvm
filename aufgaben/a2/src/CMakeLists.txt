cmake_minimum_required(VERSION 3.5)

project(njvm C)

add_executable(
    njvm 
    njvm.c 
    boot/boot.c 
    cpu/control_unit.c 
    cpu/instructions.c 
    memory/program_memory.c 
    memory/stack.c
    memory/static_data_area.c
)

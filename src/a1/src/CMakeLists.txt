cmake_minimum_required(VERSION 3.5)

project(njvm C)

add_executable(njvm njvm.c boot.c control_unit.c instructions.c program_memory.c stack.c)

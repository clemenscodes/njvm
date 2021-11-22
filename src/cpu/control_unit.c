#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "control_unit.h"
#include "instructions.h"
#include "../memory/program_memory.h"
#include "../memory/static_data_area.h"

void init(void) {
    printf("Ninja Virtual Machine started\n");
}

void read_file(char *arg) {
    FILE *fp = open_file(arg);
    check_ninja_binary_format(fp, arg);
    check_ninja_version(fp, arg);
    initialize_sda(check_ninja_variable_count(fp));
    read_instructions_into_memory(fp);
    close(fp);
}

void read_instructions_into_memory(FILE *fp) {
    uint32_t instruction_count = check_ninja_instruction_count(fp);
    size_t read_objects = 0;
    int start_of_instructions = 16;
    initialize_ram(instruction_count);
    fseek(fp, start_of_instructions, SEEK_SET);
    read_objects = fread(program_memory, sizeof(uint32_t), instruction_count, fp);
    if (read_objects != instruction_count) {
        printf("Error: Could only read [%lu] of [%d] items.\n", read_objects, instruction_count);
        exit(1);
    }
    pc = instruction_count;
}

FILE *open_file(char *arg) {
    FILE *fp = fopen(arg, "r");
    if (!fp) {
        printf("Error: cannot open code file '%s'\n", arg);
        exit(1);
    }
    return fp;
}

void check_ninja_binary_format(FILE *fp, char *arg) {
    int start = 0;
    uint32_t bytecode;
    fseek(fp, start, SEEK_SET);
    fread(&bytecode, sizeof(uint32_t), 1, fp);
    if (!(bytecode == NINJA_BINARY_FORMAT)) {
        printf("Error: file '%s' is not a Ninja binary\n", arg);
        exit(1);
    }
}

void check_ninja_version(FILE *fp, char *arg) {
    int start_of_version = 4;
    uint32_t bytecode;
    fseek(fp, start_of_version, SEEK_SET);
    fread(&bytecode, sizeof(uint32_t), 1, fp);
    // printf("ninja_version = [0x%08x]\n", bytecode);
    if (!(bytecode == NINJA_BINARY_VERSION)) {
        printf("Error: file '%s' does not have the correct Ninja version\n", arg);
        exit(1);
    }
}

uint32_t check_ninja_instruction_count(FILE *fp) {
    int start_of_instruction_count = 8;
    uint32_t bytecode;
    fseek(fp, start_of_instruction_count, SEEK_SET);
    fread(&bytecode, sizeof(uint32_t), 1, fp);
    // printf("ninja_instruction_count = [0x%08x]\n", bytecode);
    return bytecode;
}

uint32_t check_ninja_variable_count(FILE *fp) {
    int start_of_variable_count = 12;
    uint32_t bytecode;
    fseek(fp, start_of_variable_count, SEEK_SET);
    fread(&bytecode, sizeof(uint32_t), 1, fp);
    // printf("ninja_variable_count = [0x%08x]\n", bytecode);
    return bytecode;
}

void execute_binary(char *arg) {
    init();
    read_file(arg);
    print_memory();
    work();
}

void close(FILE *fp) {
    if (fclose(fp) != 0) {
        perror("Error (fclose)");
        exit(1);
    }
}

void work(void) {
    for (int i = 0; i < pc; i++) {
        execute_instruction(program_memory[i]);
    }
}

void execute_instruction(uint32_t bytecode) {
    Instruction instruction = decode_instruction(bytecode);
    Opcode opcode = instruction.opcode;
    int immediate = instruction.immediate;
    switch (opcode) {
        case halt:
            halt_instruction();
        case pushc:
            pushc_instruction(immediate);
            break;
        case add:
            add_instruction();
            break;
        case sub:
            sub_instruction();
            break;
        case mul:
            mul_instruction();
            break;
        case divide:
            div_instruction();
            break;
        case mod:
            mod_instruction();
            break;
        case rdint:
            rdint_instruction();
            break;
        case wrint:
            wrint_instruction();
            break;
        case rdchr:
            rdchr_instruction();
            break;
        case wrchr:
            wrchr_instruction();
            break;
        case pushg:
            pushg_instruction(immediate);
            break;
        case popg:
            popg_instruction(immediate);
            break;
        default:
            printf("Unknown opcode %d\n", opcode);
            halt_instruction();
    }
}

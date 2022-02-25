
#include "control_unit.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "instructions.h"
#include "program_memory.h"
#include "stack.h"
#include "static_data_area.h"

void init(void) {
    printf("Ninja Virtual Machine started\n");
}

void read_file(char *arg) {
    FILE *fp = open_file(arg);
    check_ninja_binary_format(fp, arg);
    check_ninja_version(fp, arg);
    int variable_count = check_ninja_variable_count(fp);
    if (variable_count > 0) {
        initialize_sda(variable_count);
    }
    read_instructions_into_memory(fp);
    close(fp);
}

void read_instructions_into_memory(FILE *fp) {
    uint32_t instruction_count = check_ninja_instruction_count(fp);
    int start_of_instructions = 16;
    initialize_ram(instruction_count);
    fseek(fp, start_of_instructions, SEEK_SET);
    size_t read_objects = fread(ir.data, sizeof(uint32_t), instruction_count, fp);
    if (read_objects != instruction_count) {
        printf("Error: Could only read [%lu] of [%d] items.\n", read_objects, instruction_count);
        close(fp);
        exit(1);
    }
    ir.pc = instruction_count;
}

FILE *open_file(char *arg) {
    FILE *fp = fopen(arg, "r");
    if (!fp) {
        printf("Error: cannot open code file '%s'\n", arg);
        close(fp);
        exit(1);
    }
    return fp;
}

void check_ninja_binary_format(FILE *fp, char *arg) {
    int start = 0;
    uint32_t bytecode;
    fseek(fp, start, SEEK_SET);
    if (!fread(&bytecode, sizeof(uint32_t), 1, fp)) {
        printf("Error: could not read ninja binary format");
        exit(1);
    }
    if (!(bytecode == NINJA_BINARY_FORMAT)) {
        printf("Error: file '%s' is not a Ninja binary\n", arg);
        close(fp);
        exit(1);
    }
}

void check_ninja_version(FILE *fp, char *arg) {
    int start_of_version = 4;
    uint32_t bytecode;
    fseek(fp, start_of_version, SEEK_SET);
    if (!fread(&bytecode, sizeof(uint32_t), 1, fp)) {
        printf("Error: could not read ninja version");
        exit(1);
    }
    if (!(bytecode == NINJA_BINARY_VERSION)) {
        printf("Error: file '%s' does not have the correct Ninja version\n", arg);
        close(fp);
        exit(1);
    }
}

uint32_t check_ninja_instruction_count(FILE *fp) {
    int start_of_instruction_count = 8;
    uint32_t bytecode;
    fseek(fp, start_of_instruction_count, SEEK_SET);
    if (!fread(&bytecode, sizeof(uint32_t), 1, fp)) {
        printf("Error: could not read instruction count");
        exit(1);
    }
    if (bytecode == 0) {
        printf("Error: no instructions\n");
        close(fp);
        exit(1);
    }
    return bytecode;
}

uint32_t check_ninja_variable_count(FILE *fp) {
    int start_of_variable_count = 12;
    uint32_t bytecode;
    fseek(fp, start_of_variable_count, SEEK_SET);
    if (!fread(&bytecode, sizeof(uint32_t), 1, fp)) {
        printf("Error: could not variable count");
        exit(1);
    }
    return bytecode;
}

void execute_binary(char *arg) {
    read_file(arg);
    init();
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
    ir.pc = 0;
    while (true) {
        uint32_t instruction = ir.data[ir.pc];
        ir.pc++;
        execute_instruction(instruction);
        if (decode_instruction(instruction).opcode == HALT) break;
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
        case asf:
            asf_instruction(immediate);
            break;
        case rsf:
            rsf_instruction();
            break;
        case pushl:
            pushl_instruction(immediate);
            break;
        case popl:
            popl_instruction(immediate);
            break;
        case brf:
            brf_instruction(immediate);
            break;
        case brt:
            brt_instruction(immediate);
            break;
        case jump:
            jump_instruction(immediate);
            break;
        default:
            printf("Unknown opcode %d\n", opcode);
            halt_instruction();
    }
}

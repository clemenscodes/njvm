#include "control_unit.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../memory/program_memory.h"
#include "../memory/stack.h"
#include "../memory/static_data_area.h"
#include "instructions.h"

void init(void) {
    printf("Ninja Virtual Machine started\n");
}

void shutdown(void) {
    printf("Ninja Virtual Machine stopped\n");
    exit(0);
}

FILE *open_file(char *arg) {
    FILE *fp = fopen(arg, "r");
    if (!fp) {
        printf("Error: cannot open code file '%s'\n", arg);
        exit(1);
    }
    return fp;
}

bool check_ninja_binary_format(FILE *fp) {
    int start = 0;
    uint32_t bytecode;
    fseek(fp, start, SEEK_SET);
    fread(&bytecode, sizeof(uint32_t), 1, fp);
    return bytecode == NINJA_BINARY_FORMAT;
}

bool check_ninja_version(FILE *fp) {
    int start = 4;
    uint32_t bytecode;
    fseek(fp, start, SEEK_SET);
    fread(&bytecode, sizeof(uint32_t), 1, fp);
    // printf("ninja_version = [0x%08x]\n", bytecode);
    return bytecode == NINJA_BINARY_VERSION;
}

int check_ninja_instruction_count(FILE *fp) {
    int start = 8;
    uint32_t bytecode;
    fseek(fp, start, SEEK_SET);
    fread(&bytecode, sizeof(uint32_t), 1, fp);
    // printf("ninja_instruction_count = [0x%08x]\n", bytecode);
    return bytecode;
}

int check_ninja_variable_count(FILE *fp) {
    int start = 12;
    uint32_t bytecode;
    fseek(fp, start, SEEK_SET);
    fread(&bytecode, sizeof(uint32_t), 1, fp);
    // printf("ninja_variable_count = [0x%08x]\n", bytecode);
    return bytecode;
}

void execute_binary(char *arg) {
    read_file(arg);
    work();
}

void read_file(char *arg) {
    size_t read_objects = 0;
    FILE *fp = open_file(arg);
    if (!check_ninja_binary_format(fp)) {
        printf("Error: file '%s' is not a Ninja binary\n", arg);
        exit(1);
    }
    if (!check_ninja_version(fp)) {
        printf("Error: file '%s' does not have the correct Ninja version\n", arg);
        exit(1);
    }
    int instruction_count = check_ninja_instruction_count(fp);
    int variable_count = check_ninja_variable_count(fp);
    initialize_ram(instruction_count);
    initialize_sda(variable_count);
    if (program_memory == NULL || sda == NULL) {
        perror("malloc");
        exit(1);
    }
    fseek(fp, 16, SEEK_SET);
    read_objects = fread(program_memory, sizeof(uint32_t), instruction_count, fp);
    if (read_objects != instruction_count) {
        printf("Error: Could only read [%lu] of [%d] items.\n", read_objects, instruction_count);
        exit(1);
    }
    pc = instruction_count;
    close(fp);
}

void close(FILE *fp) {
    if (fclose(fp) != 0) {
        perror("Error (fclose)");
        exit(1);
    }
}

void execute(uint32_t bytecode, int i) {
    Instruction instruction = decode_instruction(bytecode);
    Opcode opcode = instruction.opcode;
    int immediate = instruction.immediate;
    int n2;
    int n1;
    char c;
    switch (opcode) {
        case halt:
            shutdown();
        case pushc:
            push(immediate);
            break;
        case add:
            n2 = pop();
            n1 = pop();
            push(n1 + n2);
            break;
        case sub:
            n2 = pop();
            n1 = pop();
            push(n1 - n2);
            break;
        case mul:
            n2 = pop();
            n1 = pop();
            push(n1 * n2);
            break;
        case divide:
            n2 = pop();
            n1 = pop();
            if (n2 == 0) {
                printf("Division by zero error\n");
                exit(1);
            }
            push(n1 / n2);
            break;
        case mod:
            n2 = pop();
            n1 = pop();
            if (n2 == 0) {
                printf("Division by zero error\n");
                exit(1);
            }
            push(n1 % n2);
            break;
        case rdint:
            scanf("%d", &n2);
            push(n2);
            break;
        case wrint:
            printf("%d", pop());
            break;
        case rdchr:
            scanf("%c", &c);
            push(c);
            break;
        case wrchr:
            c = pop();
            printf("%c", c);
            break;
        case pushg:
            push_global(immediate);
            break;
        case popg:
            pop_global(immediate);
            break;
        default:
            printf("Unknown opcode %d\n", opcode);
            shutdown();
    }
}

void work(void) {
    init();
    print_memory();
    print_sda();
    for (int i = 0; i < pc; i++) {
        execute(program_memory[i], i);
    }
    free_sda();
    free_ram();
}

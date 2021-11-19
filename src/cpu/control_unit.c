#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "control_unit.h"
#include "../ram/program_memory.h"
#include "../stack/stack.h"
#include "instructions.h"
#include "stdbool.h"

void init(void) {
    printf("Ninja Virtual Machine started\n");
}

void shutdown(void) {
    printf("Ninja Virtual Machine stopped\n");
    exit(0);
}

void execute_binary(char *arg) {
    read_file(arg);
    print_memory();
    // work();
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
    int ninja_binary_format = 0x46424a4e;
    int start = 0;
    uint32_t bytecode;
    fseek(fp, start, SEEK_SET);
    fread(&bytecode, sizeof(uint32_t), 1, fp);
    return bytecode == ninja_binary_format;
}

bool check_ninja_version(FILE *fp) {
    int ninja_binary_version = 0x00000002;
    int start = 4;
    uint32_t bytecode;
    fseek(fp, start, SEEK_SET);
    fread(&bytecode, sizeof(uint32_t), 1, fp);
    // printf("ninja_version = [0x%08x]\n", bytecode);
    return bytecode == ninja_binary_version;
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
    // int variable_count = check_ninja_variable_count(fp);
    fseek(fp, 16, SEEK_SET);
    read_objects = fread(&program_memory, sizeof(uint32_t), instruction_count, fp);
    if (read_objects != instruction_count) {
        printf("Error: Could only read [%lu] of [%d] items.\n", read_objects, instruction_count);
        exit(1);
    }
    pc = instruction_count;
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
            printf("%03d:\t", i);
            printf("halt\n");
            shutdown();
            break;
        case pushc:
            printf("%03d:\tpushc\t%d\n", i, immediate);
            push(immediate);
            break;
        case add:
            printf("%03d:\t", i);
            printf("add\n");
            n2 = pop();
            n1 = pop();
            push(n1 + n2);
            break;
        case sub:
            printf("%03d:\t", i);
            printf("sub\n");
            n2 = pop();
            n1 = pop();
            push(n1 - n2);
            break;
        case mul:
            printf("%03d:\t", i);
            printf("mul\n");
            n2 = pop();
            n1 = pop();
            push(n1 * n2);
            break;
        case divide:
            printf("%03d:\t", i);
            printf("div\n");
            n2 = pop();
            n1 = pop();
            if (n2 == 0) {
                printf("Division by zero error\n");
                exit(1);
            }
            push(n1 / n2);
            break;
        case mod:
            printf("%03d:\t", i);
            printf("mod\n");
            n2 = pop();
            n1 = pop();
            if (n2 == 0) {
                printf("Division by zero error\n");
                exit(1);
            }
            push(n1 % n2);
            break;
        case rdint:
            printf("%03d:\t", i);
            printf("rdint\n");
            scanf("%d", &n2);
            push(n2);
            break;
        case wrint:
            printf("%03d:\t", i);
            printf("wrint\n");
            printf("%d", pop());
            break;
        case rdchr:
            printf("%03d:\t", i);
            printf("rdchr\n");
            scanf("%c", &c);
            push(c);
            break;
        case wrchr:
            printf("%03d:\t", i);
            printf("wrchr\n");
            c = pop();
            printf("%c", c);
            break;
        default:
            printf("Unknown opcode %d\n", opcode);
            break;
    }
}

void work(void) {
    init();
    for (int i = 0; i < pc; i++) {
        execute(program_memory[i], i);
    }
}

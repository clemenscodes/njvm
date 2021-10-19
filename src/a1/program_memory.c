#ifndef _MEMORY_C
#define _MEMORY_C

#include <string.h>

#include "instructions.c"
#include "stack.c"

int pc = 0;
uint32_t program_memory[MAXITEMS];

void print_instruction(uint32_t bytecode) {
    Instruction instruction = decode_instruction(bytecode);
    Opcode opcode = instruction.opcode;
    int immediate = instruction.immediate;
    switch (opcode) {
        case halt:
            printf("halt\n");
            break;
        case pushc:
            printf("pushc   %d\n", immediate);
            break;
        case add:
            printf("add\n");
            break;
        case sub:
            printf("sub\n");
            break;
        case mul:
            printf("mul\n");
            break;
        case divide:
            printf("div\n");
            break;
        case mod:
            printf("mod\n");
            break;
        case rdint:
            printf("rdint\n");
            break;
        case wrint:
            printf("wrint\n");
            break;
        case rdchr:
            printf("rdchr\n");
            break;
        case wrchr:
            printf("wrchr\n");
            break;
        default:
            break;
    }
}

void print_memory(void) {
    for (int i = 0; i < pc; i++) {
        printf("%03d:\t", i);
        print_instruction(program_memory[i]);
    }
}

void register_instruction(Opcode opcode, int immediate) {
    uint32_t instruction = encode_instruction(opcode, immediate);
    program_memory[pc] = instruction;
    pc++;
}

#endif

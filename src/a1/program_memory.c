#ifndef _MEMORY_C
#define _MEMORY_C

#include <string.h>

#include "instructions.c"
#include "stack.c"

int pc = 4;

uint32_t program_memory[MAXITEMS] = {
    0x01000000,
    0x01000001,
    0x01000002,
    0x01000003,
    0x01fffff6
};

void print_memory() {
    printf("Printing memory\n");
    for (int i = pc; i >= 0; i--) {
        decode_instruction(program_memory[i]);
    }
}

void register_instruction(enum Opcode opcode, int immediate) {
    uint32_t instruction = encode_instruction(opcode, immediate);
    program_memory[pc] = instruction;
    pc++;
}

#endif

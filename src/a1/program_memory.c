#ifndef _MEMORY_C
#define _MEMORY_C

#include <string.h>

#include "instructions.c"
#include "stack.c"

int pc = 0;

uint32_t program_memory[MAXITEMS];

void print_memory() {
    for (int i = 0; i < pc; i++) {
        decode_instruction(program_memory[i]);
    }
}

void register_instruction(enum Opcode opcode, int immediate) {
    uint32_t instruction = encode_instruction(opcode, immediate);
    program_memory[pc] = instruction;
    pc++;
}

#endif

#ifndef _MEMORY_C
#define _MEMORY_C

#include <string.h>

#include "instructions.c"
#include "stack.c"

int pc = 0;

uint32_t program_memory[MAXITEMS];

void print_memory() {
    for (int i = 0; i < pc; i++) {
        Instruction instruction = decode_instruction(program_memory[i]);
        enum Opcode opcode = instruction.opcode;
        int immediate= instruction.immediate;
        printf("0x%08X -> Opcode [%d] Immediate [%d]\n", program_memory[i], opcode, immediate);
    }
}

void register_instruction(Opcode opcode, int immediate) {
    uint32_t instruction = encode_instruction(opcode, immediate);
    program_memory[pc] = instruction;
    pc++;
}

#endif

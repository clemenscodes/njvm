#ifndef _PROGRAM_MEMORY_H
#define _PROGRAM_MEMORY_H

#include "stack.h"
#include "instructions.h"

typedef struct ir {
    int pc;
    uint32_t *instructions;
} InstructionRegister;

extern InstructionRegister ir;
void initialize_ram(uint32_t instruction_count);
void print_memory(void);
void register_instruction(Opcode opcode, int immediate);
void free_instruction_register(void);

#endif

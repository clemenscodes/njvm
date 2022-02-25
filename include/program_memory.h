#ifndef _PROGRAM_MEMORY_H
#define _PROGRAM_MEMORY_H

#include "stack.h"
#include "instructions.h"
#include "opcode.h"

typedef struct InstructionRegister {
    int pc;
    uint32_t *data;
} InstructionRegister;

extern InstructionRegister ir;
void initialize_ram(uint32_t instruction_count);
void print_memory(void);
void register_instruction(Opcode opcode, int immediate);
void free_ir(void);

#endif

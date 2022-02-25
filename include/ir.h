#ifndef _PROGRAM_MEMORY_H
#define _PROGRAM_MEMORY_H

#include "stack.h"
#include "instruction.h"
#include "opcode.h"

typedef struct InstructionRegister {
    int pc;
    uint32_t *data;
    size_t size;
} InstructionRegister;

extern InstructionRegister ir;

void initialize_ir(size_t instruction_count);
void print_ir(void);
void register_instruction(Opcode opcode, int immediate);
void free_ir(void);

#endif

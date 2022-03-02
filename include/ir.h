#ifndef _IR_H
#define _IR_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"
#include "opcode.h"
#include "immediate.h"
#include "njvm.h"
#include "pc.h"
#include "bytecode.h"
#include "utils.h"


void initialize_ir(size_t instruction_count);
void register_instruction(Opcode opcode, Immediate immediate);
void free_ir(void);
void print_ir(void);
void print_instruction(ProgramCounter pc);

#endif

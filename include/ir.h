#ifndef _IR_H
#define _IR_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"
#include "njvm.h"
#include "opcode.h"
void initialize_ir(size_t instruction_count);
void print_ir(void);
void register_instruction(Opcode opcode, int immediate);
void free_ir(void);

#endif
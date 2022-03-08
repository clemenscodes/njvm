#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include <stdint.h>

#include "bytecode.h"
#include "immediate.h"
#include "ir.h"
#include "macros.h"
#include "njvm.h"
#include "opcode.h"

typedef struct {
    Opcode opcode;
    Immediate immediate;
} Instruction;

Instruction create_new_instruction(Opcode opcode, Immediate immediate);
Bytecode encode_instruction(Opcode opcode, Immediate immediate);
Instruction decode_instruction(Bytecode bytecode);

#endif

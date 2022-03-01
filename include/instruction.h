#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include <stdint.h>

#include "opcode.h"

#define IMMEDIATE(x) ((x)&0x00FFFFFF)
#define SIGN_EXTEND(i) ((i)&0x00800000 ? (i) | 0xFF000000 : (i))

typedef struct Instruction {
    Opcode opcode;
    int immediate;
} Instruction;

uint32_t encode_instruction(Opcode opcode, int immediate);
Instruction decode_instruction(uint32_t bytecode);

#endif

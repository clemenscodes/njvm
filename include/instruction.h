#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include <stdint.h>

#include "opcode.h"

#define IMMEDIATE(x) ((x)&0x00FFFFFF)
#define SIGN_EXTEND(i) ((i)&0x00800000 ? (i) | 0xFF000000 : (i))

typedef int Immediate;
typedef uint32_t Bytecode;

typedef struct Instruction {
    Opcode opcode;
    Immediate immediate;
} Instruction;

uint32_t encode_instruction(Opcode opcode, Immediate immediate);
Instruction decode_instruction(Bytecode bytecode);

#endif

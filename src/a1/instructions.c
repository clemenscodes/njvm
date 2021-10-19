#ifndef _INSTRUCTIONS_C
#define _INSTRUCTIONS_C

#include <stdint.h>
#include <string.h>

#define HALT 0
#define PUSHC 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define MOD 6
#define RDINT 7
#define WRINT 8
#define RDCHR 9
#define WRCHR 10

#define IMMEDIATE(x) ((x)&0x00FFFFFF)
#define SIGN_EXTEND(i) ((i)&0x00800000 ? (i) | 0xFF000000 : (i))

typedef enum Opcode {
    halt = HALT,
    pushc = PUSHC,
    add = ADD,
    sub = SUB,
    mul = MUL,
    divide = DIV,
    mod = MOD,
    rdint = RDINT,
    wrint = WRINT,
    rdchr = RDCHR,
    wrchr = WRCHR
} Opcode;

typedef struct Instruction {
    Opcode opcode;
    int immediate;
} Instruction;

uint32_t encode_instruction(Opcode opcode, int immediate) {
    return (opcode << 24) | IMMEDIATE(immediate);
}

Instruction decode_instruction(uint32_t bytecode) {
    Instruction instruction;
    instruction.opcode = bytecode >> 24;
    instruction.immediate = SIGN_EXTEND(IMMEDIATE(bytecode));
    return instruction;
}

#endif

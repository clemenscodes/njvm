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

enum Opcode {
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
};

typedef struct {
    enum Opcode opcode;
    int immediate;
} Instruction;

uint32_t encode_instruction(enum Opcode opcode, int immediate) {
    uint32_t instruction;
    instruction = (opcode << 24) | IMMEDIATE(immediate);
    return instruction;
}

Instruction decode_instruction(uint32_t instruction) {
    Instruction inst;
    enum Opcode opcode = instruction >> 24;
    int immediate = SIGN_EXTEND(IMMEDIATE(instruction));
    inst.opcode = opcode;
    inst.immediate = immediate;
    return inst;
}

#endif

#ifndef _INSTRUCTIONS_C
#define _INSTRUCTIONS_C

#include <stdint.h>

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

void print_pushc_instructions() {
    uint32_t instruction;
    int opcode;
    int immediate;
    for (int i = -4; i < 4; ++i) {
        instruction = (PUSHC << 24) | IMMEDIATE(i);
        opcode = instruction >> 24;
        immediate = SIGN_EXTEND(IMMEDIATE(instruction));
        printf("0x%08x -> Opcode [%d] Immediate [%d]\n", instruction, opcode, immediate);
    }
}

#endif

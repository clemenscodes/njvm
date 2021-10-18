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
    div = DIV,
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

uint32_t encode_instruction(Instruction instruction) {
    uint32_t inst;
    enum Opcode opcode = instruction.opcode;
    int immediate = instruction.immediate;
    inst = (opcode << 24) | IMMEDIATE(immediate);
    printf("0x%08x -> Opcode [%d] Immediate [%d]\n", instruction, opcode, immediate);
    return inst;
}

Instruction decode_instruction(uint32_t instruction) {
    Instruction inst;
    enum Opcode opcode = instruction >> 24;
    int immediate = SIGN_EXTEND(IMMEDIATE(instruction));
    strcpy(inst.opcode, opcode);
    strcpy(inst.immediate, immediate);
    return inst;
}

#endif

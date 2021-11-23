#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

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
#define PUSHG 11
#define POPG 12
#define ASF 13
#define RSF 14
#define PUSHL 15
#define POPL 16

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
    wrchr = WRCHR,
    pushg = PUSHG,
    popg = POPG,
    asf = ASF,
    rsf = RSF,
    pushl = PUSHL,
    popl = POPL,
} Opcode;

typedef struct Instruction {
    Opcode opcode;
    int immediate;
} Instruction;

extern int n1, n2;
extern char c;

uint32_t encode_instruction(Opcode opcode, int immediate);
Instruction decode_instruction(uint32_t bytecode);
void shutdown(void);
void halt_instruction(void);
void pushc_instruction(int immediate);
void add_instruction(void);
void sub_instruction(void);
void mul_instruction(void);
void div_instruction(void);
void mod_instruction(void);
void wrchr_instruction(void);
void rdchr_instruction(void);
void rdint_instruction(void);
void wrint_instruction(void);
void pushg_instruction(int immediate);
void popg_instruction(int immediate);
void asf_instruction(int immediate);
void rsf_instruction(void);
void pushl_instruction(int immediate);
void popl_instruction(int immediate);
#endif

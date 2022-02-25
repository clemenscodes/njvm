#ifndef _OPCODE_H
#define _OPCODE_H

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
#define JUMP 23
#define BRF 24
#define BRT 25

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
    jump = JUMP,
    brf = BRF,
    brt = BRT,
} Opcode;

#endif

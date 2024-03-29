#ifndef _OPCODE_H
#define _OPCODE_H

#include <stdio.h>
#include <stdlib.h>

#include "bytecode.h"

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
#define EQ 17
#define NE 18
#define LT 19
#define LE 20
#define GT 21
#define GE 22
#define JUMP 23
#define BRF 24
#define BRT 25
#define CALL 26
#define RET 27
#define DROP 28
#define PUSHR 29
#define POPR 30
#define DUP 31
#define NEW 32
#define GETF 33
#define PUTF 34
#define NEWA 35
#define GETFA 36
#define PUTFA 37
#define GETSZ 38
#define PUSHN 39
#define REFEQ 40
#define REFNE 41

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
    eq = EQ,
    ne = NE,
    lt = LT,
    le = LE,
    gt = GT,
    ge = GE,
    jump = JUMP,
    brf = BRF,
    brt = BRT,
    call = CALL,
    ret = RET,
    drop = DROP,
    pushr = PUSHR,
    popr = POPR,
    dup = DUP,
    new = NEW,
    getf = GETF,
    putf = PUTF,
    newa = NEWA,
    getfa = GETFA,
    putfa = PUTFA,
    getsz = GETSZ,
    pushn = PUSHN,
    refeq = REFEQ,
    refne = REFNE,
} Opcode;

Bytecode encode_opcode(Opcode opcode);
Opcode decode_opcode(Bytecode bytecode);

#endif

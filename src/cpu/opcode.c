#include "opcode.h"

Bytecode encode_opcode(Opcode opcode) {
    return opcode << 24;
}

Opcode decode_opcode(Bytecode bytecode) {
    Opcode opcode;
    int shifted_bytecode = bytecode >> 24;
    switch (shifted_bytecode) {
        case 0:
            opcode = halt;
            break;
        case 1:
            opcode = pushc;
            break;
        case 2:
            opcode = add;
            break;
        case 3:
            opcode = sub;
            break;
        case 4:
            opcode = mul;
            break;
        case 5:
            opcode = divide;
            break;
        case 6:
            opcode = mod;
            break;
        case 7:
            opcode = rdint;
            break;
        case 8:
            opcode = wrint;
            break;
        case 9:
            opcode = rdchr;
            break;
        case 10:
            opcode = wrchr;
            break;
        case 11:
            opcode = pushg;
            break;
        case 12:
            opcode = popg;
            break;
        case 13:
            opcode = asf;
            break;
        case 14:
            opcode = rsf;
            break;
        case 15:
            opcode = pushl;
            break;
        case 16:
            opcode = popl;
            break;
        case 17:
            opcode = eq;
            break;
        case 18:
            opcode = ne;
            break;
        case 19:
            opcode = lt;
            break;
        case 20:
            opcode = le;
            break;
        case 21:
            opcode = gt;
            break;
        case 22:
            opcode = ge;
            break;
        case 23:
            opcode = jump;
            break;
        case 24:
            opcode = brf;
            break;
        case 25:
            opcode = brt;
            break;
        case 26:
            opcode = call;
            break;
        case 27:
            opcode = ret;
            break;
        case 28:
            opcode = drop;
            break;
        case 29:
            opcode = pushr;
            break;
        case 30:
            opcode = popr;
            break;
        case 31:
            opcode = dup;
            break;
        default:
            opcode = halt;
            fprintf(stderr, "Unknown opcode %d\n", opcode);
            exit(1);
    }
}

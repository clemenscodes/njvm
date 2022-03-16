#include "immediate.h"

Immediate decode_immediate(Bytecode bytecode) {
    Immediate immediate = SIGN_EXTEND(IMMEDIATE(bytecode));
    return immediate;
}

Bytecode encode_immediate(Immediate immediate) {
    if (immediate >= MIN_IMMEDIATE && immediate <= MAX_IMMEDIATE) {
        Bytecode bytecode = SIGN_EXTEND(IMMEDIATE(immediate));
        return bytecode;
    } else {
        fprintf(stderr, "Error: immediate value out of range");
        exit(1);
    }
}

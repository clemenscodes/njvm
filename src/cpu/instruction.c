#include "instruction.h"

Bytecode encode_instruction(Opcode opcode, Immediate immediate) {
    return (opcode << 24) | IMMEDIATE(immediate);
}

Instruction decode_instruction(Bytecode bytecode) {
    Instruction instruction;
    instruction.opcode = bytecode >> 24;
    instruction.immediate = SIGN_EXTEND(IMMEDIATE(bytecode));
    return instruction;
}

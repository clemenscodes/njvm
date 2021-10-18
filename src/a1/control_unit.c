#ifndef _CONTROL_UNIT_C
#define _CONTROL_UNIT_C

#include "program_memory.c"

void execute(Instruction instruction) {
    enum Opcode opcode = instruction.opcode;
    int immediate = instruction.immediate;
    uint32_t bytecode = encode_instruction(opcode, immediate);  // Nur für Debugzwecke
    printf("Executing instruction [0x%08X] -> Opcode [%d] Immediate [%d]\n", bytecode, opcode, immediate);
    if (opcode == halt) {
        exit(0);
    }
}

void work() {
    for (int i = 0; i < pc; i++) {
        Instruction instruction = decode_instruction(program_memory[i]);
        execute(instruction);
    }
}

#endif

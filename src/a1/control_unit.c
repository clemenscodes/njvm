#ifndef _CONTROL_UNIT_C
#define _CONTROL_UNIT_C

#include "program_memory.c"

void init() {
    printf("Ninja Virtual Machine started\n");
}

void shutdown() {
    printf("Ninja Virtual Machine stopped\n");
    exit(0);
}

void execute(uint32_t bytecode) {
    Instruction instruction = decode_instruction(bytecode);
    Opcode opcode = instruction.opcode;
    int immediate = instruction.immediate;
    printf("Executing instruction [0x%08X] -> Opcode [%d] Immediate [%d]\n", bytecode, opcode, immediate);
    switch (opcode) {
        case halt:
            shutdown();
            break;
        case pushc:
            // pushc(immediate);
            break;
        case add:
            // add();
            break;
        case sub:
            // sub();
            break;
        case mul:
            // mul();
            break;
        case divide:
            // divide();
            break;
        case mod:
            // mod();
            break;
        case rdint:
            // rdint();
            break;
        case wrint:
            // wrint();
            break;
        case rdchr:
            // rdchr();
            break;
        case wrchr:
            // wrchr();
            break;
        default:
            shutdown();
    }
}

void work() {
    for (int i = 0; i < pc; i++) {
        execute(program_memory[i]);
    }
}

#endif

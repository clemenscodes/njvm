#ifndef _CONTROL_UNIT_C
#define _CONTROL_UNIT_C

#include "program_memory.c"
#include "stack.c"

void init(void) {
    printf("Ninja Virtual Machine started\n");
}

void shutdown(void) {
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
            push(immediate);
            break;
        case add:
            int n2 = pop();
            int n1 = pop();
            push(n1 + n2);
            break;
        case sub:
            int n2 = pop();
            int n1 = pop();
            push(n1 - n2);
            break;
        case mul:
            int n2 = pop();
            int n1 = pop();
            push(n1 * n2);
            break;
        case divide:
            int n2 = pop();
            int n1 = pop();
            push(n1 / n2);
            break;
        case mod:
            int n2 = pop();
            int n1 = pop();
            push(n1 % n2);
            break;
        case rdint:
            break;
        case wrint:
            break;
        case rdchr:
            break;
        case wrchr:
            break;
        default:
            shutdown();
    }
}

void work(void) {
    for (int i = 0; i < pc; i++) {
        execute(program_memory[i]);
    }
}

#endif

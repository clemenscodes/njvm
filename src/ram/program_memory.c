#include <stdio.h>
#include <string.h>
#include "../cpu/instructions.h"
#include "../stack/stack.h"
#include "program_memory.h"

int pc = 0;
uint32_t program_memory[MAXITEMS];

void print_memory(void) {
    for (int i = 0; i < pc; i++) {
        Instruction instruction = decode_instruction(program_memory[i]);
        Opcode opcode = instruction.opcode;
        int immediate = instruction.immediate;
        switch (opcode) {
            case halt:
                printf("%03d:\t", i);
                printf("halt\n");
                break;
            case pushc:
                printf("%03d:\tpushc\t%d\n", i, immediate);
                break;
            case add:
                printf("%03d:\t", i);
                printf("add\n");
                break;
            case sub:
                printf("%03d:\t", i);
                printf("sub\n");
                break;
            case mul:
                printf("%03d:\t", i);
                printf("mul\n");
                break;
            case divide:
                printf("%03d:\t", i);
                printf("div\n");
                break;
            case mod:
                printf("%03d:\t", i);
                printf("mod\n");
                break;
            case rdint:
                printf("%03d:\t", i);
                printf("rdint\n");
                break;
            case wrint:
                printf("%03d:\t", i);
                printf("wrint\n");
                break;
            case rdchr:
                printf("%03d:\t", i);
                printf("rdchr\n");
                break;
            case wrchr:
                printf("%03d:\t", i);
                printf("wrchr\n");
                break;
            default:
                break;
        }
    }
}

void register_instruction(Opcode opcode, int immediate) {
    uint32_t instruction = encode_instruction(opcode, immediate);
    program_memory[pc] = instruction;
    pc++;
}
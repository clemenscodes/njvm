#include "ir.h"

void initialize_ir(size_t instruction_count) {
    vm.ir.size = instruction_count;
    vm.ir.pc = 0;
    vm.ir.data = (uint32_t *)calloc(vm.ir.size, sizeof(uint32_t));
    if (!vm.ir.data) {
        perror("malloc(ir.program_memory)");
        exit(1);
    }
}

void register_instruction(Opcode opcode, int immediate) {
    uint32_t instruction = encode_instruction(opcode, immediate);
    vm.ir.data[vm.ir.pc] = instruction;
    vm.ir.pc++;
}

void free_ir(void) {
    free(vm.ir.data);
}

void print_ir(void) {
    for (int i = 0; i < vm.ir.size; i++) {
        Instruction instruction = decode_instruction(vm.ir.data[i]);
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
            case pushg:
                printf("%03d:\tpushg\t%d\n", i, immediate);
                break;
            case popg:
                printf("%03d:\tpopg\t%d\n", i, immediate);
                break;
            case asf:
                printf("%03d:\tasf\t%d\n", i, immediate);
                break;
            case rsf:
                printf("%03d:\trsf\n", i);
                break;
            case pushl:
                printf("%03d:\tpushl\t%d\n", i, immediate);
                break;
            case popl:
                printf("%03d:\tpopl\t%d\n", i, immediate);
                break;
            case brf:
                printf("%03d:\tbrf\t%d\n", i, immediate);
                break;
            case brt:
                printf("%03d:\tbrt\t%d\n", i, immediate);
                break;
            case jump:
                printf("%03d:\tjump\t%d\n", i, immediate);
                break;
            default:
                printf("Unknown opcode %d\n", opcode);
                break;
        }
    }
}

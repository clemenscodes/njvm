#include "ir.h"

void initialize_ir(size_t instruction_count) {
    vm.ir.size = instruction_count;
    vm.ir.pc = 0;
    vm.ir.data = calloc(vm.ir.size, sizeof(uint32_t));
    if (!vm.ir.data) {
        perror("malloc(ir.data)");
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
        print_instruction(i);
    }
}

void print_instruction(int pc) {
    Instruction instruction = decode_instruction(vm.ir.data[pc]);
    Opcode opcode = instruction.opcode;
    int immediate = instruction.immediate;
    switch (opcode) {
        case halt:
            printf("%03d:\t", pc);
            printf("halt\n");
            break;
        case pushc:
            printf("%03d:\tpushc\t%d\n", pc, immediate);
            break;
        case add:
            printf("%03d:\t", pc);
            printf("add\n");
            break;
        case sub:
            printf("%03d:\t", pc);
            printf("sub\n");
            break;
        case mul:
            printf("%03d:\t", pc);
            printf("mul\n");
            break;
        case divide:
            printf("%03d:\t", pc);
            printf("div\n");
            break;
        case mod:
            printf("%03d:\t", pc);
            printf("mod\n");
            break;
        case rdint:
            printf("%03d:\t", pc);
            printf("rdint\n");
            break;
        case wrint:
            printf("%03d:\t", pc);
            printf("wrint\n");
            break;
        case rdchr:
            printf("%03d:\t", pc);
            printf("rdchr\n");
            break;
        case wrchr:
            printf("%03d:\t", pc);
            printf("wrchr\n");
            break;
        case pushg:
            printf("%03d:\tpushg\t%d\n", pc, immediate);
            break;
        case popg:
            printf("%03d:\tpopg\t%d\n", pc, immediate);
            break;
        case asf:
            printf("%03d:\tasf\t%d\n", pc, immediate);
            break;
        case rsf:
            printf("%03d:\trsf\n", pc);
            break;
        case pushl:
            printf("%03d:\tpushl\t%d\n", pc, immediate);
            break;
        case popl:
            printf("%03d:\tpopl\t%d\n", pc, immediate);
            break;
        case eq:
            printf("%03d:\teq\n", pc);
            break;
        case ne:
            printf("%03d:\tne\n", pc);
            break;
        case lt:
            printf("%03d:\tlt\n", pc);
            break;
        case le:
            printf("%03d:\tle\n", pc);
            break;
        case gt:
            printf("%03d:\tgt\n", pc);
            break;
        case ge:
            printf("%03d:\tge\n", pc);
            break;
        case jump:
            printf("%03d:\tjump\t%d\n", pc, immediate);
            break;
        case brf:
            printf("%03d:\tbrf\t%d\n", pc, immediate);
            break;
        case brt:
            printf("%03d:\tbrt\t%d\n", pc, immediate);
            break;
        case call:
            printf("%03d:\tcall\t%d\n", pc, immediate);
            break;
        case ret:
            printf("%03d:\tret\n", pc);
            break;
        case drop:
            printf("%03d:\tdrop\t%d\n", pc, immediate);
            break;
        case pushr:
            printf("%03d:\tpushr\n", pc);
            break;
        case popr:
            printf("%03d:\tpopr\n", pc);
            break;
        case dup:
            printf("%03d:\tdup\n", pc);
            break;
        default:
            printf("Unknown opcode %d\n", opcode);
            break;
    }
}

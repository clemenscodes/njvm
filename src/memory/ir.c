#include "ir.h"

void initialize_ir(unsigned instruction_count) {
    vm.ir.size = instruction_count;
    vm.ir.data = malloc(vm.ir.size * sizeof(Bytecode));
    if (!vm.ir.data) {
        perror("calloc(vm.ir.data)");
    }
}

void register_instruction(Opcode opcode, Immediate immediate) {
    Bytecode instruction = encode_instruction(opcode, immediate);
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

void print_instruction(ProgramCounter pc) {
    Instruction instruction = decode_instruction(vm.ir.data[pc]);
    Opcode opcode = instruction.opcode;
    Immediate immediate = instruction.immediate;
    switch (opcode) {
        case halt:
            printf("%03d:\thalt\n", pc);
            break;
        case pushc:
            printf("%03d:\tpushc\t%d\n", pc, immediate);
            break;
        case add:
            printf("%03d:\tadd\n", pc);
            break;
        case sub:
            printf("%03d:\tsub\n", pc);
            break;
        case mul:
            printf("%03d:\tmul\n", pc);
            break;
        case divide:
            printf("%03d:\tdiv\n", pc);
            break;
        case mod:
            printf("%03d:\tmod\n", pc);
            break;
        case rdint:
            printf("%03d:\trdint\n", pc);
            break;
        case wrint:
            printf("%03d:\twrint\n", pc);
            break;
        case rdchr:
            printf("%03d:\trdchr\n", pc);
            break;
        case wrchr:
            printf("%03d:\twrchr\n", pc);
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
        case new:
            printf("%03d:\tnew\t%d\n", pc, immediate);
            break;
        case getf:
            printf("%03d:\tgetf\t%d\n", pc, immediate);
            break;
        case putf:
            printf("%03d:\tputf\t%d\n", pc, immediate);
            break;
        case newa:
            printf("%03d:\tnewa\n", pc);
            break;
        case getfa:
            printf("%03d:\tgetfa\n", pc);
            break;
        case putfa:
            printf("%03d:\tputfa\n", pc);
            break;
        case getsz:
            printf("%03d:\tgetsz\n", pc);
            break;
        case pushn:
            printf("%03d:\tpushn\n", pc);
            break;
        case refeq:
            printf("%03d:\trefeq\n", pc);
            break;
        case refne:
            printf("%03d:\trefne\n", pc);
            break;
        default:
            fprintf(stderr, "Unknown opcode %d\n", opcode);
            exit(1);
    }
}

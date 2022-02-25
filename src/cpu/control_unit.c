#include "control_unit.h"

void init(void) {
    printf("Ninja Virtual Machine started\n");
}

void execute_binary(char *arg) {
    read_file(arg);
    init();
    print_memory();
    work();
}

void work(void) {
    ir.pc = 0;
    while (true) {
        uint32_t instruction = ir.data[ir.pc];
        ir.pc++;
        execute_instruction(instruction);
        if (decode_instruction(instruction).opcode == HALT) break;
    }
}

void execute_instruction(uint32_t bytecode) {
    Instruction instruction = decode_instruction(bytecode);
    Opcode opcode = instruction.opcode;
    int immediate = instruction.immediate;
    switch (opcode) {
        case halt:
            halt_instruction();
        case pushc:
            pushc_instruction(immediate);
            break;
        case add:
            add_instruction();
            break;
        case sub:
            sub_instruction();
            break;
        case mul:
            mul_instruction();
            break;
        case divide:
            div_instruction();
            break;
        case mod:
            mod_instruction();
            break;
        case rdint:
            rdint_instruction();
            break;
        case wrint:
            wrint_instruction();
            break;
        case rdchr:
            rdchr_instruction();
            break;
        case wrchr:
            wrchr_instruction();
            break;
        case pushg:
            pushg_instruction(immediate);
            break;
        case popg:
            popg_instruction(immediate);
            break;
        case asf:
            asf_instruction(immediate);
            break;
        case rsf:
            rsf_instruction();
            break;
        case pushl:
            pushl_instruction(immediate);
            break;
        case popl:
            popl_instruction(immediate);
            break;
        case brf:
            brf_instruction(immediate);
            break;
        case brt:
            brt_instruction(immediate);
            break;
        case jump:
            jump_instruction(immediate);
            break;
        default:
            printf("Unknown opcode %d\n", opcode);
            halt_instruction();
    }
}

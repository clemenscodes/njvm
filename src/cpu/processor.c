#include "processor.h"

int a, b;
char c;

void init(void) {
    printf("Ninja Virtual Machine started\n");
}

void execute(char *arg) {
    read_file(arg);
    init();
    work();
}

void work(void) {
    while (1) {
        uint32_t instruction = vm.ir.data[vm.ir.pc];
        vm.ir.pc++;
        execute_instruction(instruction);
        if (decode_instruction(instruction).opcode == HALT) exit(0);
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
        case eq:
            eq_instruction();
            break;
        case ne:
            ne_instruction();
            break;
        case lt:
            lt_instruction();
            break;
        case le:
            le_instruction();
            break;
        case gt:
            gt_instruction();
            break;
        case ge:
            ge_instruction();
            break;
        case jump:
            jump_instruction(immediate);
            break;
        case brf:
            brf_instruction(immediate);
            break;
        case brt:
            brt_instruction(immediate);
            break;
        default:
            printf("Unknown opcode %d\n", opcode);
            halt_instruction();
    }
}

void halt_instruction(void) {
    free_sda();
    free_ir();
    printf("Ninja Virtual Machine stopped\n");
}

void pushc_instruction(int immediate) {
    push(immediate);
}

void add_instruction(void) {
    b = pop();
    a = pop();
    push(a + b);
}

void sub_instruction(void) {
    b = pop();
    a = pop();
    push(a - b);
}

void mul_instruction(void) {
    b = pop();
    a = pop();
    push(a * b);
}

void div_instruction(void) {
    b = pop();
    a = pop();
    if (b == 0) {
        printf("Division by zero error\n");
        exit(1);
    }
    push(a / b);
}

void mod_instruction(void) {
    b = pop();
    a = pop();
    if (b == 0) {
        printf("Division by zero error\n");
        exit(1);
    }
    push(a % b);
}

void wrchr_instruction(void) {
    c = pop();
    printf("%c", c);
}

void rdchr_instruction(void) {
    if (!scanf("%c", &c)) {
        printf("Error: failed to read character");
        exit(1);
    }
    push(c);
}

void rdint_instruction(void) {
    if (!scanf("%d", &b)) {
        printf("Error: failed to read integer");
        exit(1);
    }
    push(b);
}

void wrint_instruction(void) {
    printf("%d", pop());
}

void pushg_instruction(int immediate) {
    push_global(immediate);
}

void popg_instruction(int immediate) {
    pop_global(immediate);
}

void asf_instruction(int immediate) {
    push(vm.stack.fp);
    vm.stack.fp = vm.stack.sp;
    vm.stack.size += immediate;
    vm.stack.data = (int *)realloc(vm.stack.data, (vm.stack.size) * sizeof(int));
    vm.stack.sp += immediate;
    for (int i = vm.stack.fp; i < vm.stack.sp; i++) {
        vm.stack.data[i] = 0;
    }
}

void rsf_instruction(void) {
    vm.stack.size -= (vm.stack.sp - vm.stack.fp);
    vm.stack.data = (int *)realloc(vm.stack.data, (vm.stack.size) * sizeof(int));
    vm.stack.sp = vm.stack.fp;
    vm.stack.fp = pop();
}

void pushl_instruction(int immediate) {
    push(vm.stack.data[vm.stack.fp + immediate]);
}

void popl_instruction(int immediate) {
    vm.stack.data[vm.stack.fp + immediate] = vm.stack.data[vm.stack.sp - 1];
}

void eq_instruction(void) {
    b = pop();
    a = pop();
    if (a == b) {
        push(1);
    } else {
        push(0);
    }
}

void ne_instruction(void) {
    b = pop();
    a = pop();
    if (a != b) {
        push(1);
    } else {
        push(0);
    }
}
void lt_instruction(void) {
    b = pop();
    a = pop();
    if (a < b) {
        push(1);
    } else {
        push(0);
    }
}
void le_instruction(void) {
    b = pop();
    a = pop();
    if (a <= b) {
        push(1);
    } else {
        push(0);
    }
}
void gt_instruction(void) {
    b = pop();
    a = pop();
    if (a > b) {
        push(1);
    } else {
        push(0);
    }
}
void ge_instruction(void) {
    b = pop();
    a = pop();
    if (a >= b) {
        push(1);
    } else {
        push(0);
    }
}
void jump_instruction(int immediate) {
    vm.ir.pc = immediate;
}

void brf_instruction(int immediate) {
    if (pop() == 0) {
        jump_instruction(immediate);
    }
}

void brt_instruction(int immediate) {
    if (pop() == 1) {
        jump_instruction(immediate);
    }
}

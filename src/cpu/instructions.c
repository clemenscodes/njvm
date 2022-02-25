#include "instructions.h"

int a, b;
char c;

uint32_t encode_instruction(Opcode opcode, int immediate) {
    return (opcode << 24) | IMMEDIATE(immediate);
}

Instruction decode_instruction(uint32_t bytecode) {
    Instruction instruction;
    instruction.opcode = bytecode >> 24;
    instruction.immediate = SIGN_EXTEND(IMMEDIATE(bytecode));
    return instruction;
}

void halt_instruction(void) {
    free_sda();
    free_ir();
    printf("Ninja Virtual Machine stopped\n");
    exit(0);
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
    if(!scanf("%c", &c)) {
        printf("Error: failed to read character");
        exit(1);
    }
    push(c);
}

void rdint_instruction(void) {
    if(!scanf("%d", &b)) {
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
    push(fp);
    fp = sp;
    stack_size += immediate;
    stack = (int *)realloc(stack, (stack_size) * sizeof(int));
    sp += immediate;
    for (int i = fp; i < sp; i++) {
        stack[i] = 0;
    }
}

void rsf_instruction(void) {
    stack_size -= (sp - fp);
    stack = (int *)realloc(stack, (stack_size) * sizeof(int));
    sp = fp;
    fp = pop();
}

void pushl_instruction(int immediate) {
    push(stack[fp + immediate]);
}

void popl_instruction(int immediate) {
    stack[fp + immediate] = stack[sp - 1];
}

void brf_instruction(bool immediate) {
    if (!immediate) {
        jump_instruction(immediate);
    }
}

void brt_instruction(bool immediate) {
    if (immediate) {
        jump_instruction(immediate);
    }
}

void jump_instruction(int immediate) {
    ir.pc = immediate;
}

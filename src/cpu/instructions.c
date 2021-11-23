#include "instructions.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../memory/program_memory.h"
#include "../memory/stack.h"
#include "../memory/static_data_area.h"

int n1, n2;
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
    free_ram();
    printf("Ninja Virtual Machine stopped\n");
    exit(0);
}

void pushc_instruction(int immediate) {
    push(immediate);
}

void add_instruction(void) {
    n2 = pop();
    n1 = pop();
    push(n1 + n2);
}

void sub_instruction(void) {
    n2 = pop();
    n1 = pop();
    push(n1 - n2);
}

void mul_instruction(void) {
    n2 = pop();
    n1 = pop();
    push(n1 * n2);
}

void div_instruction(void) {
    n2 = pop();
    n1 = pop();
    if (n2 == 0) {
        printf("Division by zero error\n");
        exit(1);
    }
    push(n1 / n2);
}

void mod_instruction(void) {
    n2 = pop();
    n1 = pop();
    if (n2 == 0) {
        printf("Division by zero error\n");
        exit(1);
    }
    push(n1 % n2);
}

void wrchr_instruction(void) {
    c = pop();
    printf("%c", c);
}

void rdchr_instruction(void) {
    scanf("%c", &c);
    push(c);
}

void rdint_instruction(void) {
    scanf("%d", &n2);
    push(n2);
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
    pc = immediate;
}

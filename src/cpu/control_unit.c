#include "control_unit.h"

#include <stdio.h>
#include <stdlib.h>

#include "../ram/program_memory.h"
#include "../stack/stack.h"
#include "instructions.h"

void init(void) {
    printf("Ninja Virtual Machine started\n");
}

void shutdown(void) {
    printf("Ninja Virtual Machine stopped\n");
    exit(0);
}

void execute_binary(char *arg) {
    read_file(arg);
}

FILE *open_file(char *arg) {
    FILE *fp = fopen(arg, "r+");
    if (!fp) {
        printf("Error: cannot open code file '%s'\n", arg);
        exit(1);
    }
    return fp;
}

void read_file(char *arg) {
    FILE *fp = open_file(arg);
    char c;
    while ((c = fgetc(fp)) != EOF) {
        printf("%c", c);
    }
    printf("\n");
    fclose(fp);
}

void execute(uint32_t bytecode) {
    Instruction instruction = decode_instruction(bytecode);
    Opcode opcode = instruction.opcode;
    int immediate = instruction.immediate;
    int n2;
    int n1;
    char c;
    switch (opcode) {
        case halt:
            shutdown();
            break;
        case pushc:
            push(immediate);
            break;
        case add:
            n2 = pop();
            n1 = pop();
            push(n1 + n2);
            break;
        case sub:
            n2 = pop();
            n1 = pop();
            push(n1 - n2);
            break;
        case mul:
            n2 = pop();
            n1 = pop();
            push(n1 * n2);
            break;
        case divide:
            n2 = pop();
            n1 = pop();
            if (n2 == 0) {
                printf("Division by zero error\n");
                exit(1);
            }
            push(n1 / n2);
            break;
        case mod:
            n2 = pop();
            n1 = pop();
            if (n2 == 0) {
                printf("Division by zero error\n");
                exit(1);
            }
            push(n1 % n2);
            break;
        case rdint:
            scanf("%d", &n2);
            push(n2);
            break;
        case wrint:
            printf("%d", pop());
            break;
        case rdchr:
            scanf("%c", &c);
            push(c);
            break;
        case wrchr:
            c = pop();
            printf("%c", c);
            break;
        default:
            shutdown();
    }
}

void work(void) {
    init();
    for (int i = 0; i < pc; i++) {
        execute(program_memory[i]);
    }
}

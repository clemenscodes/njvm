#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int sp = 0;
size_t stack_size;
int *stack;

void initialize_stack(void) {
    stack_size = 1;
    stack = (int *)malloc(stack_size * sizeof(int));
}

void push(int immediate) {
    stack_size++;
    if (sp > stack_size) {
        printf("Stack overflow: Stack is full, not more than %ld items allowed\n", stack_size);
        exit(1);
    }
    stack = (int *)realloc(stack, stack_size*sizeof(int));
    stack[sp] = immediate;
    sp++;
}

int pop(void) {
    if ((sp == 0) && stack[sp] == 0) {
        printf("Stack underflow: popped from empty stack\n");
        exit(1);
    }
    sp--;
    int tmp = stack[sp];
    stack[sp] = 0;
    return tmp;
}

void free_stack() {
    free(stack);
}

void print_stack(void) {
    printf("\n\tStack\n");
    printf(".-------+-------.\n");
    for (int i = sp; i >= 0; i--) {
        if (i == sp) {
            printf("|sp->%3d|%7d|\n", i, stack[i]);
        } else {
            printf("|%7d|%7d|\n", i, stack[i]);
        }
    }
    printf("'-------+-------'\n\n");
}

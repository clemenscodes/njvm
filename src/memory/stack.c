#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

size_t stack_size = 0;
int sp = 0;
int fp = 0;
int *stack;

void push(int immediate) {
    if (sp > MAXITEMS) {
        printf("Stack overflow: Stack is full, not more than %d items allowed\n", MAXITEMS);
        exit(1);
    }
    stack_size++;
    stack = (int *)realloc(stack, (stack_size + 1) * sizeof(int));
    stack[sp] = immediate;
    sp++;
    stack[sp] = 0;
}

int pop(void) {
    if (!(sp || stack[sp])) {
        printf("Stack underflow: popped from empty stack\n");
        exit(1);
    }
    sp--;
    stack_size--;
    int tmp = stack[sp];
    stack = (int *)realloc(stack, stack_size * sizeof(int));
    return tmp;
}

void print_stack(void) {
    printf("\n\tStack\n");
    printf(".-------+-------.\n");
    for (int i = sp; i >= 0; i--) {
        if (i == sp) {
            printf("|sp->%3d|%7d|\n", i, 0);
        } else {
            printf("|%7d|%7d|\n", i, stack[i]);
        }
    }
    printf("'-------+-------'\n\n");
}

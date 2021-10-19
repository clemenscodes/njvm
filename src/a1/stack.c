#ifndef _STACK_C
#define _STACK_C
#include <stdio.h>
#include <stdlib.h>

#define MAXITEMS 100

int sp = 0;
int stack[MAXITEMS];

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

void push(int immediate) {
    stack[sp] = immediate;
    sp++;
}

int pop(void) {
    sp--;
    int tmp = stack[sp];
    stack[sp] = 0;
    return tmp;
}

#endif

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
    printf("- [%4s] -> pushing [%d] onto stack @sp [%d]\n", __func__, immediate, sp);
    stack[sp] = immediate;
    printf("- [%4s] -> inc stack pointer [%d -> ", __func__, sp);
    sp++;
    printf("%d]\n", sp);
}

int pop(void) {
    printf("- [%3s] -> dec stack pointer [%d -> ", __func__, sp);
    sp--;
    printf("%d]\n", sp);
    int tmp = stack[sp];
    printf("- [%3s] -> popping [%d] from stack @sp [%d]\n", __func__, tmp, sp);
    stack[sp] = 0;
    return tmp;
}

#endif

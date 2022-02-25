#include "stack.h"

Stack stack;

void initialize_stack(void) {
    stack.size = 0;
    stack.sp = 0;
    stack.fp = 0;
}

void push(int immediate) {
    stack.size++;
    stack.data = (int *)realloc(stack.data, (stack.size + 1) * sizeof(int));
    stack.data[stack.sp] = immediate;
    stack.sp++;
    stack.data[stack.sp] = 0;
}

int pop(void) {
    if (!(stack.sp || stack.data[stack.sp])) {
        printf("Stack underflow: popped from empty stack\n");
        exit(1);
    }
    stack.sp--;
    stack.size--;
    int tmp = stack.data[stack.sp];
    stack.data = (int *)realloc(stack.data, stack.size * sizeof(int));
    return tmp;
}

void print_stack(void) {
    printf("\n\tStack\n");
    printf(".-------+-------.\n");
    for (int i = stack.sp; i >= 0; i--) {
        if (i == stack.sp) {
            printf("|sp->%3d|%7d|\n", i, 0);
        } else {
            printf("|%7d|%7d|\n", i, stack.data[i]);
        }
    }
    printf("'-------+-------'\n\n");
}

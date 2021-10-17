#include <stdio.h>
#include <stdlib.h>

#define MAXITEMS 100

int sp = 0;
int stack[MAXITEMS];

void push(int x) {
    printf("- [%4s] -> pushing [%d] onto stack @sp [%d]\n", __func__, x, sp);
    stack[sp] = x;
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

void print_stack(void) {
    printf("\n\tStack\n");
    printf(".-------+-------.\n");
    for (int i = sp; i >= 0; i--) {
        if (i == sp) {
            printf("|sp->%3d| %6d |\n", i, stack[i]);
        } else {
            printf("|%7d|  %5d |\n", i, stack[i]);
        }
    }
    printf("'-------+-------'\n\n");
}

int main(int argc, char *argv[]) {
    print_stack();
    push(5);
    print_stack();
    push(3);
    print_stack();
    push(4);
    print_stack();
    push(7);
    print_stack();
    push(10);
    print_stack();
    pop();
    print_stack();
    pop();
    print_stack();
    pop();
    print_stack();
    push(7);
    print_stack();
    return 0;
}

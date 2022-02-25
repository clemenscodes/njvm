#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>

#define MAXITEMS 10000

extern int sp;
extern int fp;
extern int *stack;
extern size_t stack_size;

typedef int StackPointer;
typedef int FramePointer;

typedef struct stack {
    StackPointer sp;
    FramePointer fp;
    int *data;
} Stack;

void initialize_stack(void);
void push(int immediate);
int pop(void);
void free_stack(void);
void print_stack(void);

#endif

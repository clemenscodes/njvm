#ifndef _STACK_H
#define _STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef int StackPointer;
typedef int FramePointer;

typedef struct stack {
    StackPointer sp;
    FramePointer fp;
    size_t size;
    int *data;
} Stack;

extern Stack stack;

void initialize_stack(void);
void push(int immediate);
int pop(void);
void free_stack(void);
void print_stack(void);

#endif

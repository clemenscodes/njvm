#ifndef _NJVM_H
#define _NJVM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugger.h"
#include "ir.h"
#include "processor.h"
#include "sda.h"
#include "stack.h"
#include "utils.h"

typedef int Breakpoint;
typedef int ReturnValueRegister;
typedef int StackPointer;
typedef int FramePointer;

typedef struct stack {
    StackPointer sp;
    FramePointer fp;
    size_t size;
    int *data;
} Stack;

typedef struct ir {
    int pc;
    size_t size;
    uint32_t *data;
} InstructionRegister;

typedef struct sda {
    int *data;
    size_t size;
} StaticDataArea;

typedef struct njvm {
    Stack stack;
    StaticDataArea sda;
    InstructionRegister ir;
    Breakpoint bp;
    ReturnValueRegister rv;
} NinjaVM;

extern NinjaVM vm;

void print_usage(void);
void print_version(void);
void process_arg(char *arg, char *argv[]);
int check_arg(char *arg, char *argv[]);
void check_help(char *arg);
void check_version(char *arg);
void check_debug(char *arg, char *argv[]);

#endif

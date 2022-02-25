#ifndef _NJVM_H
#define _NJVM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ir.h"
#include "processor.h"
#include "sda.h"
#include "stack.h"
#include "utils.h"

typedef int Breakpoint;
typedef int ReturnValueRegister;
typedef int StackPointer;
typedef int FramePointer;

typedef struct {
    StackPointer sp;
    FramePointer fp;
    size_t size;
    int *data;
} Stack;

typedef struct {
    int pc;
    size_t size;
    uint32_t *data;
} InstructionRegister;

typedef struct {
    int *data;
    size_t size;
} StaticDataArea;

typedef struct {
    Stack stack;
    StaticDataArea sda;
    InstructionRegister ir;
    Breakpoint bp;
    ReturnValueRegister rv;
} NinjaVM;

extern NinjaVM vm;

#endif

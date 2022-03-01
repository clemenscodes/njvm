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

typedef int StackPointer;
typedef int FramePointer;
typedef int *ReturnValueRegister;
typedef int *Breakpoint;
typedef int Object;
typedef Object *ObjRef;

typedef struct Stack {
    StackPointer sp;
    FramePointer fp;
    size_t size;
    ObjRef data;
} Stack;

typedef struct InstructionRegister {
    int pc;
    size_t size;
    uint32_t *data;
} InstructionRegister;

typedef struct StaticDataArea {
    ObjRef data;
    size_t size;
} StaticDataArea;

typedef struct NinjaVM {
    Stack stack;
    StaticDataArea sda;
    InstructionRegister ir;
    Breakpoint bp;
    ReturnValueRegister rv;
} NinjaVM;

extern NinjaVM vm;

#endif

#ifndef _NJVM_H
#define _NJVM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugger.h"
#include "processor.h"
#include "utils.h"
#include "pc.h"

typedef int StackPointer;
typedef int FramePointer;
typedef int *ReturnValueRegister;
typedef int *Breakpoint;
typedef Immediate Object;
typedef Object *ObjRef;

typedef struct Stack {
    StackPointer sp;
    FramePointer fp;
    size_t size;
    ObjRef data;
} Stack;

typedef struct InstructionRegister {
    ProgramCounter pc;
    size_t size;
    Bytecode *data;
} InstructionRegister;

typedef struct StaticDataArea {
    size_t size;
    ObjRef data;
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

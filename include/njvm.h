#ifndef _NJVM_H
#define _NJVM_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugger.h"
#include "immediate.h"
#include "opcode.h"
#include "pc.h"
#include "processor.h"
#include "utils.h"
#include "objref.h"

typedef int StackPointer;
typedef int FramePointer;
typedef int *ReturnValueRegister;
typedef int *Breakpoint;

typedef struct StackSlot {
    bool is_obj_ref;
    union {
        ObjRef obj_ref;
        Immediate value;
    } slot;
} StackSlot;

typedef struct Stack {
    StackPointer sp;
    FramePointer fp;
    size_t size;
    Immediate *data;
} Stack;

typedef struct InstructionRegister {
    ProgramCounter pc;
    size_t size;
    Bytecode *data;
} InstructionRegister;

typedef struct StaticDataArea {
    size_t size;
    Immediate *data;
} StaticDataArea;

typedef struct NinjaVM {
    Stack stack;
    StaticDataArea sda;
    InstructionRegister ir;
    Breakpoint bp;
    ReturnValueRegister rv;
} NinjaVM;

extern NinjaVM vm;

int njvm(int argc, char *argv[]);

#endif

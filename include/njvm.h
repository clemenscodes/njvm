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
#include "stack.h"
#include "heap.h"
#include "../lib/build/include/bigint.h"

#define MAX_ITEMS 10000

typedef int StackPointer;
typedef int FramePointer;
typedef int *ReturnValueRegister;
typedef int *Breakpoint;

typedef union {
        ObjRef obj_ref;
        Immediate value;
} StackValue;

typedef struct StackSlot {
    bool is_obj_ref;
    StackValue u;
} StackSlot;

typedef struct Stack {
    unsigned int memory;
    StackPointer sp;
    FramePointer fp;
    size_t size;
    StackSlot *data;
} Stack;

typedef struct Heap {
    unsigned int memory;
    ObjRef *data;
} Heap;

typedef struct InstructionRegister {
    ProgramCounter pc;
    size_t size;
    Bytecode *data;
} InstructionRegister;

typedef struct StaticDataArea {
    size_t size;
    ObjRef *data;
} StaticDataArea;

typedef struct NinjaVM {
    Stack stack;
    StaticDataArea sda;
    Heap heap;
    InstructionRegister ir;
    Breakpoint bp;
    ObjRef rv;
} NinjaVM;

extern NinjaVM vm;

int njvm(int argc, char *argv[]);

#endif

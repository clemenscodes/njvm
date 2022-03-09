#ifndef _NJVM_H
#define _NJVM_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/build/include/bigint.h"
#include "debugger.h"
#include "heap.h"
#include "immediate.h"
#include "opcode.h"
#include "pc.h"
#include "processor.h"
#include "stack.h"
#include "utils.h"

typedef int StackPointer;
typedef int FramePointer;
typedef int *Breakpoint;

typedef union {
    ObjRef obj_ref;
    Immediate value;
} StackValue;

typedef struct {
    bool is_obj_ref;
    StackValue u;
} StackSlot;

typedef struct {
    size_t memory;
    size_t max_items;
    StackPointer sp;
    FramePointer fp;
    size_t size;
    StackSlot *data;
} Stack;

typedef struct {
    size_t size;
    ObjRef *data;
} StaticDataArea;

typedef struct {
    unsigned int memory;
    unsigned int bytes;
    unsigned int available;
    unsigned char *active;
    unsigned char *passive;
    unsigned char *next;
} Heap;

typedef struct {
    ProgramCounter pc;
    size_t size;
    Bytecode *data;
} InstructionRegister;

typedef struct {
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

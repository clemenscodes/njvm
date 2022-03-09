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

typedef struct {
    bool activated;
} Debugger;

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
    size_t memory;
    size_t bytes;
    size_t available;
    size_t used;
    size_t size;
    void *active;
    void *passive;
    unsigned char *next;
} Heap;

typedef struct {
    ProgramCounter pc;
    size_t size;
    Bytecode *data;
} InstructionRegister;

typedef struct {
    bool purge_flag;
    bool stats_flag;
    size_t copied_objects;
    size_t copied_bytes;
} GarbageCollector;

typedef struct {
    Stack stack;
    StaticDataArea sda;
    Heap heap;
    InstructionRegister ir;
    Breakpoint bp;
    ObjRef rv;
    GarbageCollector gc;
    Debugger debugger;
} NinjaVM;

extern NinjaVM vm;

int njvm(int argc, char *argv[]);

#endif

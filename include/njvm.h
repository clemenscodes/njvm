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

#define DEFAULT_HEAP_SIZE 8192
#define DEFAULT_STACK_SIZE 64
#define KiB 1024

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
    size_t size;
    size_t memory;
    size_t bytes;
    size_t max_items;
    StackPointer sp;
    FramePointer fp;
    StackSlot *data;
} Stack;

typedef struct {
    size_t size;
    ObjRef *data;
} StaticDataArea;

typedef struct {
    size_t size;
    size_t memory;
    size_t bytes;
    size_t available;
    size_t used;
    unsigned char *begin;
    unsigned char *active;
    unsigned char *passive;
    unsigned char *next;
} Heap;

typedef struct {
    size_t size;
    ProgramCounter pc;
    Bytecode *data;
} InstructionRegister;

typedef struct {
    bool purge_flag;
    bool stats_flag;
    size_t copied_objects;
    size_t copied_bytes;
} GarbageCollector;

typedef struct {
    InstructionRegister ir;
    ObjRef rv;
    Stack stack;
    StaticDataArea sda;
    Heap heap;
    GarbageCollector gc;
    Debugger debugger;
    Breakpoint bp;
} NinjaVM;

extern NinjaVM vm;

NinjaVM default_ir(NinjaVM vm);
NinjaVM default_rv(NinjaVM vm);
NinjaVM default_stack(NinjaVM vm);
NinjaVM default_sda(NinjaVM vm);
NinjaVM default_heap(NinjaVM vm);
NinjaVM default_gc(NinjaVM vm);
NinjaVM default_debugger(NinjaVM vm);
NinjaVM default_bp(NinjaVM vm);
NinjaVM default_vm(void);

int njvm(int argc, char *argv[]);

#endif

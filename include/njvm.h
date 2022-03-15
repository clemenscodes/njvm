#ifndef _NJVM_H
#define _NJVM_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/build/include/bigint.h"
#include "debugger.h"
#include "gc.h"
#include "heap.h"
#include "immediate.h"
#include "opcode.h"
#include "pc.h"
#include "processor.h"
#include "stack.h"
#include "utils.h"

#define NINJA_BINARY_FORMAT 0x46424a4e
#define NINJA_BINARY_VERSION 0x00000008
#define DEFAULT_HEAP_SIZE 8192
#define DEFAULT_STACK_SIZE 64
#define KiB 1024

typedef unsigned StackPointer;
typedef unsigned FramePointer;
typedef int *Breakpoint;
typedef ObjRef ReturnValueRegister;

typedef union {
    ObjRef obj_ref;
    Immediate value;
} StackValue;

typedef struct {
    bool is_obj_ref;
    StackValue u;
} StackSlot;

typedef struct {
    unsigned size;
    unsigned memory;
    unsigned bytes;
    unsigned max_items;
    StackPointer sp;
    FramePointer fp;
    StackSlot *data;
} Stack;

typedef struct {
    unsigned size;
    unsigned memory;
    unsigned bytes;
    unsigned available;
    unsigned used;
    unsigned char *begin;
    unsigned char *active;
    unsigned char *passive;
    unsigned char *next;
} Heap;

typedef struct {
    unsigned size;
    ObjRef *data;
} StaticDataArea;

typedef struct {
    unsigned size;
    ProgramCounter pc;
    Bytecode *data;
} InstructionRegister;

typedef struct {
    bool is_running;
    bool purge_flag;
    bool stats_flag;
    unsigned collections;
    unsigned copied_objects;
    unsigned copied_bytes;
    unsigned total_copied_objects;
    unsigned total_copied_bytes;
} GarbageCollector;

typedef struct {
    bool activated;
    Breakpoint bp;
} Debugger;

typedef struct {
    Stack stack;
    Heap heap;
    StaticDataArea sda;
    InstructionRegister ir;
    ReturnValueRegister rv;
    GarbageCollector gc;
    Debugger debugger;
} NinjaVM;

extern NinjaVM vm;

int njvm(int argc, char *argv[]);

NinjaVM default_vm(void);
NinjaVM default_stack(NinjaVM vm);
NinjaVM default_heap(NinjaVM vm);
NinjaVM default_sda(NinjaVM vm);
NinjaVM default_ir(NinjaVM vm);
NinjaVM default_rv(NinjaVM vm);
NinjaVM default_gc(NinjaVM vm);
NinjaVM default_debugger(NinjaVM vm);

#endif

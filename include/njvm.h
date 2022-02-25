#ifndef _NJVM_H
#define _NJVM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "program_memory.h"
#include "static_data_area.h"
#include "utils.h"

typedef int Breakpoint;
typedef int ReturnValueRegister;

typedef struct njvm {
    Stack stack;
    InstructionRegister ir;
    StaticDataArea sda;
    Breakpoint bp;
    ReturnValueRegister rv;
} NinjaVM;

#endif

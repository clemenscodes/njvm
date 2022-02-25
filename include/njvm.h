#ifndef _NJVM_H
#define _NJVM_H

#include "control_unit.h"
#include "program_memory.h"
#include "static_data_area.h"

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

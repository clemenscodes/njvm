#ifndef _DEBUGGER_H
#define _DEBUGGER_H

#include <stdio.h>

#include "njvm.h"
#include "opcode.h"
#include "processor.h"
#include "bytecode.h"
#include "instruction.h"
#include "utils.h"

void debug(char *bin);
void prompt(void);
void inspect(void);
void step(void);
void next(void);
void run(void);
void set_breakpoint(void);
void print_obj_ref(ObjRef obj_ref);
void print_memory_in_be_bytes(void *ptr, int bytes);
void print_memory_in_be_bits(void *ptr, int bytes);
void print_memory_in_le_bits(void *ptr, int bytes);
void print_obj_ref_in_be_bytes(ObjRef obj_ref);
void print_obj_ref_in_be_bits(ObjRef obj_ref);
void print_obj_ref_in_le_bits(ObjRef obj_ref);

#endif

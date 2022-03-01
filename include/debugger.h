#ifndef _DEBUGGER_H
#define _DEBUGGER_H

#include <stdio.h>

#include "njvm.h"
#include "utils.h"
#include "processor.h"

void debug(char *bin);
void inspect(void);
void step(void);
void next(void);
void run(void);
void set_breakpoint(void);
void print_next_instruction(void);
void debug_stack(void);
void debug_sda(void);
void debug_ir(void);
void prompt(void);

#endif

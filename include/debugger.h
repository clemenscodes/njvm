#ifndef _DEBUGGER_H
#define _DEBUGGER_H

#include <stdio.h>

#include "njvm.h"
#include "utils.h"
#include "processor.h"

void debug(char *bin);
void prompt(void);
void inspect(void);
void step(void);
void next(void);
void run(void);
void set_breakpoint(void);

#endif

#ifndef _SDA_H
#define _SDA_H

#include <stdint.h>

#include "njvm.h"
#include "stack.h"
#include "debugger.h"

void initialize_sda(void);
void push_global(Immediate immediate);
void pop_global(Immediate immediate);
void print_sda(void);

#endif

#ifndef _SDA_H
#define _SDA_H

#include <stdint.h>

#include "debugger.h"
#include "njvm.h"
#include "stack.h"

void initialize_sda(unsigned variable_count);
void push_global(Immediate immediate);
void pop_global(Immediate immediate);
void print_sda(void);
void free_sda(void);

#endif

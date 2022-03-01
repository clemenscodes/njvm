#ifndef _SDA_H
#define _SDA_H

#include <stdint.h>

#include "njvm.h"
#include "stack.h"

void initialize_sda(size_t variable_count);
void push_global(Immediate immediate);
void pop_global(Immediate immediate);
void free_sda(void);
void print_sda(void);

#endif

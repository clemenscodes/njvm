#ifndef _STATIC_DATA_AREA_H
#define _STATIC_DATA_AREA_H

#include <stdint.h>
#include "stack.h"

extern uint32_t *sda;
extern uint32_t size;

int push_global(int n);
void pop_global(int n);
void initialize_sda(uint32_t bytes);
void free_sda(void);

#endif

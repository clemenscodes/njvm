#ifndef _STATIC_DATA_AREA_H
#define _STATIC_DATA_AREA_H

#include "stack.h"

extern uint32_t sda[MAXITEMS];

int push_global(int n);
void pop_global(int n);

#endif

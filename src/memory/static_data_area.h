#ifndef _STATIC_DATA_AREA_H
#define _STATIC_DATA_AREA_H

#include "stack.h"

extern int static_data[MAXITEMS];

int push_global(int n);
void pop_global(int n);

#endif

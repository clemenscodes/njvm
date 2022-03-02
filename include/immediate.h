#ifndef _IMMEDIATE_H
#define _IMMEDIATE_H

#include <stdio.h>
#include <stdlib.h>

#include "bytecode.h"
#include "macros.h"

typedef int Immediate;

#define MIN_IMMEDIATE -8388608
#define MAX_IMMEDIATE 8388607

Immediate decode_immediate(Bytecode bytecode);
Bytecode encode_immediate(Immediate immediate);

#endif

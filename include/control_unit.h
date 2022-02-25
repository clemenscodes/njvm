#ifndef _CONTROL_UNIT_H
#define _CONTROL_UNIT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"
#include "program_memory.h"
#include "stack.h"
#include "static_data_area.h"
#include "utils.h"

void init(void);
void execute_binary(char *file_name);
void execute_instruction(uint32_t bytecode);
void work(void);

#endif

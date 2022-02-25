#ifndef _CONTROL_UNIT_H
#define _CONTROL_UNIT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "instruction.h"
#include "ir.h"
#include "stack.h"
#include "sda.h"
#include "utils.h"

extern int n1, n2;
extern char c;

void init(void);
void execute_binary(char *file_name);
void execute_instruction(uint32_t bytecode);
void work(void);
void shutdown(void);
void halt_instruction(void);
void pushc_instruction(int immediate);
void add_instruction(void);
void sub_instruction(void);
void mul_instruction(void);
void div_instruction(void);
void mod_instruction(void);
void wrchr_instruction(void);
void rdchr_instruction(void);
void rdint_instruction(void);
void wrint_instruction(void);
void pushg_instruction(int immediate);
void popg_instruction(int immediate);
void asf_instruction(int immediate);
void rsf_instruction(void);
void pushl_instruction(int immediate);
void brf_instruction(bool immediate);
void brt_instruction(bool immediate);
void jump_instruction(int immediate);
void popl_instruction(int immediate);

#endif

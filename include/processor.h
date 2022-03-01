#ifndef _PROCESSOR_H
#define _PROCESSOR_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"
#include "ir.h"
#include "njvm.h"
#include "sda.h"
#include "stack.h"
#include "utils.h"

void init(void);
void execute(char *file_name);
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
void popl_instruction(int immediate);
void eq_instruction(void);
void ne_instruction(void);
void lt_instruction(void);
void le_instruction(void);
void gt_instruction(void);
void ge_instruction(void);
void jump_instruction(int immediate);
void brf_instruction(int immediate);
void brt_instruction(int immediate);
void call_instruction(int immediate);
void ret_instruction(void);
void drop_instruction(int immediate);
void pushr_instruction(void);
void popr_instruction(void);
void dup_instruction(void);

#endif

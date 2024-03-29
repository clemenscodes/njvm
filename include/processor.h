#ifndef _PROCESSOR_H
#define _PROCESSOR_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lib/build/include/bigint.h"
#include "../lib/build/include/support.h"
#include "gc.h"
#include "heap.h"
#include "instruction.h"
#include "ir.h"
#include "njvm.h"
#include "opcode.h"
#include "sda.h"
#include "stack.h"
#include "utils.h"

void init(void);
void execute(void);
void execute_instruction(Bytecode bytecode);
void halt_instruction(void);
void pushc_instruction(Immediate immediate);
void add_instruction(void);
void sub_instruction(void);
void mul_instruction(void);
void div_instruction(void);
void mod_instruction(void);
void wrchr_instruction(void);
void rdchr_instruction(void);
void rdint_instruction(void);
void wrint_instruction(void);
void pushg_instruction(Immediate immediate);
void popg_instruction(Immediate immediate);
void asf_instruction(Immediate immediate);
void rsf_instruction(void);
void pushl_instruction(Immediate immediate);
void popl_instruction(Immediate immediate);
void eq_instruction(void);
void ne_instruction(void);
void lt_instruction(void);
void le_instruction(void);
void gt_instruction(void);
void ge_instruction(void);
void jump_instruction(Immediate immediate);
void brf_instruction(Immediate immediate);
void brt_instruction(Immediate immediate);
void call_instruction(Immediate immediate);
void ret_instruction(void);
void drop_instruction(Immediate immediate);
void pushr_instruction(void);
void popr_instruction(void);
void dup_instruction(void);
void new_instruction(Immediate immediate);
void getf_instruction(Immediate immediate);
void putf_instruction(Immediate immediate);
void newa_instruction(void);
void getfa_instruction(void);
void putfa_instruction(void);
void getsz_instruction(void);
void pushn_instruction(void);
void refeq_instruction(void);
void refne_instruction(void);

#endif

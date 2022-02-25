#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "program_memory.h"
#include "stack.h"
#include "static_data_area.h"
#include "opcode.h"

#define IMMEDIATE(x) ((x)&0x00FFFFFF)
#define SIGN_EXTEND(i) ((i)&0x00800000 ? (i) | 0xFF000000 : (i))

typedef struct Instruction {
    Opcode opcode;
    int immediate;
} Instruction;

extern int n1, n2;
extern char c;

uint32_t encode_instruction(Opcode opcode, int immediate);
Instruction decode_instruction(uint32_t bytecode);
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

#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lib/build/include/bigint.h"
#include "../lib/build/include/support.h"
#include "bytecode.h"
#include "heap.h"
#include "instruction.h"
#include "macros.h"
#include "njvm.h"

FILE *open_file(char *file_name);
void read_file(char *file_name);
void close_file(FILE *fp);
char *read_line(void);
void check_ninja_binary_format(FILE *fp, char *arg);
void check_ninja_version(FILE *fp, char *arg);
void read_instructions_into_ir(FILE *fp);
unsigned check_ninja_instruction_count(FILE *fp);
unsigned check_ninja_variable_count(FILE *fp);
Bytecode seek_file(FILE *fp, unsigned offset);
ObjRef new_composite_object(unsigned num_obj_refs);
unsigned get_obj_ref_bytes(ObjRef obj_ref);
unsigned get_obj_ref_size(ObjRef obj_ref);
void set_broken_heart(ObjRef obj_ref);
void set_forward_pointer(ObjRef obj_ref, unsigned forward_pointer);

#endif

#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"
#include "bytecode.h"
#include "macros.h"
#include "njvm.h"
#include "../lib/build/include/bigint.h"
#include "../lib/build/include/support.h"

#define NINJA_BINARY_FORMAT 0x46424a4e
#define NINJA_BINARY_VERSION 0x00000007

FILE *open_file(char *file_name);
void read_file(char *file_name);
void close_file(FILE *fp);
char *read_line(void);
void check_ninja_binary_format(FILE *fp, char *arg);
void check_ninja_version(FILE *fp, char *arg);
void read_instructions_into_ir(FILE *fp);
size_t check_ninja_instruction_count(FILE *fp);
size_t check_ninja_variable_count(FILE *fp);
Bytecode seek_file(FILE *fp, int offset);
void print_obj_ref(ObjRef obj_ref);
ObjRef new_composite_object(int num_obj_refs);

#endif
 
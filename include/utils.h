#ifndef _UTILS_H
#define _UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "instruction.h"
#include "njvm.h"

#define NINJA_BINARY_FORMAT 0x46424a4e
#define NINJA_BINARY_VERSION 0x00000004

FILE *open_file(char *file_name);
void read_file(char *file_name);
void close_file(FILE *fp);
void check_ninja_binary_format(FILE *fp, char *arg);
void check_ninja_version(FILE *fp, char *arg);
void read_instructions_into_ir(FILE *fp);
size_t check_ninja_instruction_count(FILE *fp);
size_t check_ninja_variable_count(FILE *fp);
Bytecode seek_file(FILE *fp, int offset);
char *read_line(void);
void fatal_error(char *error_message);

#endif
 
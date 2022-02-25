#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "sda.h"
#include "ir.h"
#include "processor.h"

#define NINJA_BINARY_FORMAT 0x46424a4e
#define NINJA_BINARY_VERSION 0x00000002

FILE *open_file(char *file_name);
void close(FILE *fp);
void read_file(char *file_name);
void check_ninja_binary_format(FILE *fp, char *arg);
void check_ninja_version(FILE *fp, char *arg);
void read_instructions_into_memory(FILE *fp);
uint32_t check_ninja_instruction_count(FILE *fp);
uint32_t check_ninja_variable_count(FILE *fp);

#endif 
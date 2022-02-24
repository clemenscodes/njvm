#ifndef _CONTROL_UNIT_H
#define _CONTROL_UNIT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NINJA_BINARY_FORMAT 0x46424a4e
#define NINJA_BINARY_VERSION 0x00000003

FILE *open_file(char *file_name);
void init(void);
void read_file(char *file_name);
void execute_binary(char *file_name);
void close(FILE *fp);
void execute_instruction(uint32_t bytecode);
void work(void);
void check_ninja_binary_format(FILE *fp, char *arg);
void check_ninja_version(FILE *fp, char *arg);
void read_instructions_into_memory(FILE *fp);
uint32_t check_ninja_instruction_count(FILE *fp);
uint32_t check_ninja_variable_count(FILE *fp);

#endif

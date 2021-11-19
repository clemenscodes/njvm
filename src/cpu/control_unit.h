#ifndef _CONTROL_UNIT_H
#define _CONTROL_UNIT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NINJA_BINARY_FORMAT 0x46424a4e;
#define NINJA_BINARY_VERSION 0x00000002

void init(void);
void shutdown(void);
void read_file(char *file_name);
FILE *open_file(char *file_name);
bool check_ninja_binary_format(FILE *fp);
void execute_binary(char *file_name);
void close(FILE *fp);
void execute(uint32_t bytecode, int i);
void work(void);
bool check_ninja_binary_format(FILE *fp);
bool check_ninja_version(FILE *fp);
int check_ninja_instruction_count(FILE *fp);
int check_ninja_variable_count(FILE *fp);

#endif

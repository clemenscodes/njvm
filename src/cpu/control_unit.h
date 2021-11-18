#ifndef _CONTROL_UNIT_H
#define _CONTROL_UNIT_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void init(void);
void shutdown(void);
void read_file(char *filename);
FILE *open_file(char *filename);
bool check_ninja_binary_format(FILE *fp);
void execute_binary(char *filename);
void execute(uint32_t bytecode);
void work(void);

#endif

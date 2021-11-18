#ifndef _CONTROL_UNIT_H
#define _CONTROL_UNIT_H

#include <stdint.h>

void init(void);
void shutdown(void);
void read_file(char *filename);
void execute_binary(char *filename);
void execute(uint32_t bytecode);
void work(void);

#endif

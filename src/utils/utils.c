#include "utils.h"

void read_file(char *arg) {
    FILE *fp = open_file(arg);
    check_ninja_binary_format(fp, arg);
    check_ninja_version(fp, arg);
    size_t variable_count = check_ninja_variable_count(fp);
    if (variable_count > 0) {
        initialize_sda(variable_count);
    }
    read_instructions_into_ir(fp);
    close_file(fp);
}

void read_instructions_into_ir(FILE *fp) {
    size_t instruction_count = check_ninja_instruction_count(fp);
    initialize_ir(instruction_count);
    fseek(fp, 16, SEEK_SET);
    size_t read_objects = fread(vm.ir.data, sizeof(uint32_t), instruction_count, fp);
    if (read_objects != instruction_count) {
        fprintf(stderr, "Error: Could only read [%lu] of [%ld] items.\n", read_objects, instruction_count);
        close_file(fp);
        exit(1);
    }
}

FILE *open_file(char *arg) {
    FILE *fp = fopen(arg, "r");
    if (!fp) {
        fprintf(stderr, "Error: cannot open code file '%s'\n", arg);
        exit(1);
    }
    return fp;
}

Bytecode seek_file(FILE *fp, int offset) {
    Bytecode buffer;
    fseek(fp, offset, SEEK_SET);
    if (!fread(&buffer, sizeof(uint32_t), 1, fp)) {
        perror("Error (fread)");
        exit(1);
    }
    return buffer;
}

void check_ninja_binary_format(FILE *fp, char *arg) {
    Bytecode buffer = seek_file(fp, 0);
    if (!(buffer == NINJA_BINARY_FORMAT)) {
        fprintf(stderr, "Error: file '%s' is not a Ninja binary\n", arg);
        close_file(fp);
        exit(1);
    }
}

void check_ninja_version(FILE *fp, char *arg) {
    Bytecode buffer = seek_file(fp, 4);
    if (!(buffer == NINJA_BINARY_VERSION)) {
        fprintf(stderr, "Error: file '%s' does not have the correct Ninja version\n", arg);
        close_file(fp);
        exit(1);
    }
}

size_t check_ninja_instruction_count(FILE *fp) {
    Bytecode buffer = seek_file(fp, 8);
    if (!buffer) {
        fprintf(stderr, "Error: no instructions\n");
        close_file(fp);
        exit(1);
    }
    return buffer;
}

size_t check_ninja_variable_count(FILE *fp) {
    Bytecode buffer = seek_file(fp, 12);
    return buffer;
}

void close_file(FILE *fp) {
    if (fclose(fp)) {
        perror("Error (fclose)");
        exit(1);
    }
}

char *read_line(void) {
    char *line = NULL;
    size_t len = 0;
    if (!getline(&line, &len, stdin)) {
        perror("(getline)");
        exit(1);
    }
    return line;
}

void fatal_error(char *error_message) {
    fprintf(stderr, "%s\n", error_message);
    exit(1);
}

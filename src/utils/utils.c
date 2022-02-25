#include "utils.h" 

void read_file(char *arg) {
    FILE *fp = open_file(arg);
    check_ninja_binary_format(fp, arg);
    check_ninja_version(fp, arg);
    int variable_count = check_ninja_variable_count(fp);
    if (variable_count > 0) {
        initialize_sda(variable_count);
    }
    read_instructions_into_memory(fp);
    close(fp);
}

void read_instructions_into_memory(FILE *fp) {
    uint32_t instruction_count = check_ninja_instruction_count(fp);
    initialize_ir(instruction_count);
    fseek(fp, 16, SEEK_SET);
    size_t read_objects = fread(vm.ir.data, sizeof(uint32_t), instruction_count, fp);
    if (read_objects != instruction_count) {
        printf("Error: Could only read [%lu] of [%d] items.\n", read_objects, instruction_count);
        close(fp);
        exit(1);
    }
    vm.ir.pc = instruction_count;
}

FILE *open_file(char *arg) {
    FILE *fp = fopen(arg, "r");
    if (!fp) {
        printf("Error: cannot open code file '%s'\n", arg);
        exit(1);
    }
    return fp;
}

uint32_t seek_file(FILE *fp, int offset) {
    uint32_t buffer;
    fseek(fp, offset, SEEK_SET);
    if (!fread(&buffer, sizeof(uint32_t), 1, fp)) {
        perror("Error (fread)");
        exit(1);
    }
    return buffer;
}

void check_ninja_binary_format(FILE *fp, char *arg) {
    uint32_t buffer = seek_file(fp, 0);
    if (!(buffer == NINJA_BINARY_FORMAT)) {
        printf("Error: file '%s' is not a Ninja binary\n", arg);
        close(fp);
        exit(1);
    }
}

void check_ninja_version(FILE *fp, char *arg) {
    uint32_t buffer = seek_file(fp, 4);
    if (!(buffer == NINJA_BINARY_VERSION)) {
        printf("Error: file '%s' does not have the correct Ninja version\n", arg);
        close(fp);
        exit(1);
    }
}

uint32_t check_ninja_instruction_count(FILE *fp) {
    uint32_t buffer = seek_file(fp, 8);
    if (!buffer) {
        printf("Error: no instructions\n");
        close(fp);
        exit(1);
    }
    return buffer;
}

uint32_t check_ninja_variable_count(FILE *fp) {
    uint32_t buffer = seek_file(fp, 12);
    return buffer;
}

void close(FILE *fp) {
    if (fclose(fp)) {
        perror("Error (fclose)");
        exit(1);
    }
}

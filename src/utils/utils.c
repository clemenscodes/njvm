#include "utils.h"

void read_file() {
    FILE *fp = open_file(vm.code_file);
    check_ninja_binary_format(fp);
    check_ninja_version(fp);
    unsigned variable_count = check_ninja_variable_count(fp);
    if (variable_count > 0) {
        vm.sda.size = variable_count;
    }
    read_instructions_into_ir(fp);
    close_file(fp);
}

void read_instructions_into_ir(FILE *fp) {
    unsigned instruction_count = check_ninja_instruction_count(fp);
    initialize_ir(instruction_count);
    fseek(fp, 16, SEEK_SET);
    unsigned read_objects =
        fread(vm.ir.data, sizeof(Bytecode), instruction_count, fp);
    if (read_objects != instruction_count) {
        fprintf(stderr, "Error: Could only read [%u] of [%u] items.\n",
                read_objects, instruction_count);
        close_file(fp);
        exit(1);
    }
}

FILE *open_file() {
    FILE *fp = fopen(vm.code_file, "r");
    if (!fp) {
        fprintf(stderr, "Error: cannot open code file '%s'\n", vm.code_file);
        exit(1);
    }
    return fp;
}

Bytecode seek_file(FILE *fp, unsigned offset) {
    Bytecode buffer;
    fseek(fp, offset, SEEK_SET);
    if (!fread(&buffer, sizeof(Bytecode), 1, fp)) {
        perror("Error (fread)");
        exit(1);
    }
    return buffer;
}

void check_ninja_binary_format(FILE *fp) {
    Bytecode buffer = seek_file(fp, 0);
    if (!(buffer == NINJA_BINARY_FORMAT)) {
        fprintf(stderr, "Error: file '%s' is not a Ninja binary\n", vm.code_file);
        close_file(fp);
        exit(1);
    }
}

void check_ninja_version(FILE *fp) {
    Bytecode buffer = seek_file(fp, 4);
    if (!(buffer == NINJA_BINARY_VERSION)) {
        fprintf(stderr,
                "Error: file '%s' does not have the correct Ninja version\n",
                vm.code_file);
        close_file(fp);
        exit(1);
    }
}

unsigned check_ninja_instruction_count(FILE *fp) {
    Bytecode buffer = seek_file(fp, 8);
    if (!buffer) {
        close_file(fp);
        fatalError("no instructions");
    }
    return buffer;
}

unsigned check_ninja_variable_count(FILE *fp) {
    return seek_file(fp, 12);
}

void close_file(FILE *fp) {
    if (fclose(fp)) {
        perror("fclose");
        exit(1);
    }
}

char *read_line(void) {
    char *line = NULL;
    size_t len = 0;
    if (!getline(&line, &len, stdin)) {
        perror("getline");
        exit(1);
    }
    return line;
}

ObjRef new_composite_object(unsigned num_obj_refs) {
    ObjRef obj_ref = alloc((sizeof(ObjRef) * num_obj_refs) + sizeof(unsigned));
    if (!obj_ref) {
        fatalError("failed to allocate memory for compound obj");
    }
    obj_ref->size = num_obj_refs | MSB;
    return obj_ref;
}

unsigned get_obj_ref_bytes(ObjRef obj_ref) {
    if (!obj_ref) {
        fatalError("failed to determine bytes for null object");
    }
    return IS_PRIMITIVE(obj_ref)
               ? obj_ref->size + sizeof(unsigned)
               : (GET_ELEMENT_COUNT(obj_ref) * sizeof(ObjRef)) + sizeof(int);
}

unsigned get_obj_ref_size(ObjRef obj_ref) {
    if (!obj_ref) {
        fatalError("failed to determine size for null object");
    }
    return IS_PRIMITIVE(obj_ref) ? obj_ref->size : GET_ELEMENT_COUNT(obj_ref);
}

void set_broken_heart(ObjRef obj_ref) {
    if (!obj_ref) {
        fatalError("cannot set broken heart flag on null object");
    }
    obj_ref->size |= BROKEN_HEART;
    if (!IS_COPIED(obj_ref)) {
        fatalError("failed setting broken heart flag");
    }
}

void set_forward_pointer(ObjRef obj_ref, unsigned forward_pointer) {
    if (!obj_ref) {
        fatalError("cannot set forward pointer on null object");
    }
    if (forward_pointer > FORWARD_PTR_MASK) {
        fatalError("address bigger than 2^30");
    }
    if (!IS_COPIED(obj_ref)) {
        fatalError("broken heart flag is not set, would corrupt the object");
    }
    obj_ref->size &= ~FORWARD_PTR_MASK;
    obj_ref->size |= forward_pointer;
}

ObjRef get_obj_ref_from_forward_pointer(ObjRef obj_ref) {
    if (!obj_ref) {
        fatalError("cannot get forward pointer from null object");
    }
    if (!IS_COPIED(obj_ref)) {
        fatalError("broken heart is not set");
    }
    unsigned forward_pointer = GET_FORWARD_PTR(obj_ref);
    unsigned char *p = vm.heap.active + forward_pointer;
    ObjRef decoded_obj_ref = (ObjRef)p;
    return decoded_obj_ref;
}

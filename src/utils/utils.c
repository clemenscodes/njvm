#include "utils.h"

void read_file(char *arg) {
    FILE *fp = open_file(arg);
    check_ninja_binary_format(fp, arg);
    check_ninja_version(fp, arg);
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
    unsigned read_objects = fread(vm.ir.data, sizeof(Bytecode), instruction_count, fp);
    if (read_objects != instruction_count) {
        fprintf(stderr, "Error: Could only read [%u] of [%u] items.\n", read_objects, instruction_count);
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

Bytecode seek_file(FILE *fp, unsigned offset) {
    Bytecode buffer;
    fseek(fp, offset, SEEK_SET);
    if (!fread(&buffer, sizeof(Bytecode), 1, fp)) {
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

unsigned check_ninja_instruction_count(FILE *fp) {
    Bytecode buffer = seek_file(fp, 8);
    if (!buffer) {
        close_file(fp);
        fatalError("Error: no instructions");
    }
    return buffer;
}

unsigned check_ninja_variable_count(FILE *fp) {
    return seek_file(fp, 12);
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

ObjRef new_composite_object(unsigned num_obj_refs) {
    ObjRef obj_ref = alloc((sizeof(ObjRef) * num_obj_refs) + sizeof(unsigned));
    if (!obj_ref) {
        fatalError("Failed to allocate memory for compound obj");
    }
    obj_ref->size = num_obj_refs | MSB;
    return obj_ref;
}

unsigned get_obj_ref_bytes(ObjRef obj_ref) {
    // if (!obj_ref || !*(ObjRef *)obj_ref) {
    //     return sizeof(ObjRef);
    // }
    return IS_PRIMITIVE(obj_ref) ? obj_ref->size + sizeof(unsigned) : (GET_ELEMENT_COUNT(obj_ref) * sizeof(ObjRef)) + sizeof(int);
}

unsigned get_obj_ref_size(ObjRef obj_ref) {
    // if (!obj_ref || !*(ObjRef *)obj_ref) {
    //     return sizeof(ObjRef);
    // }
    return IS_PRIMITIVE(obj_ref) ? obj_ref->size : (GET_ELEMENT_COUNT(obj_ref));
}

void set_broken_heart(ObjRef obj_ref) {
    if (!obj_ref || !*(ObjRef *)obj_ref) {
        return;
    }
    obj_ref->size |= BROKEN_HEART;
    if (!IS_COPIED(obj_ref)) {
        fatalError("Error: failed setting broken heart flag");
    }
}

void set_forward_pointer(ObjRef obj_ref, unsigned forward_pointer) {
    // if (!obj_ref || !*(ObjRef *)obj_ref) {
    //     return;
    // }
    if (forward_pointer > FORWARD_PTR_MASK) {
        fatalError("Error: address bigger than 2^30");
    }
    if (!IS_COPIED(obj_ref)) {
        fatalError("Error: broken heart flag is not set, would corrupt the object");
    }
    obj_ref->size &= ~FORWARD_PTR_MASK;
    obj_ref->size |= forward_pointer;
}

ObjRef get_obj_ref_from_forward_pointer(ObjRef obj_ref) {
    // if (!obj_ref || !*(ObjRef *)obj_ref) {
    //     return (ObjRef)NULL;
    // }
    if (!IS_COPIED(obj_ref)) {
        fatalError("Error: broken heart flag is not set, no valid forward pointer in object");
    }
    unsigned forward_pointer = GET_FORWARD_PTR(obj_ref);
    unsigned char *p = vm.heap.active + forward_pointer;
    ObjRef decoded_obj_ref = (ObjRef)p;
    return decoded_obj_ref;
}

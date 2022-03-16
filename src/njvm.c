#include "njvm.h"

NinjaVM vm;

int njvm(int argc, char *argv[]) {
    vm = default_vm();
    bool code_flag = false;
    char *code_file = NULL;
    for (int i = 1; i <= argc; i++) {
        if (i == argc) {
            if (!code_flag) {
                fatalError("no code file specified");
            }
            init(code_file);
        }
        if (!strcmp(argv[i], "--debug")) {
            vm.debugger.activated = true;
            continue;
        }
        if (!strcmp(argv[i], "--help")) {
            printf("usage: ./njvm [options] <code file>\n");
            printf("Options:\n");
            printf("  --stack <n>\t   set stack size to n KiB (default: 64)\n");
            printf("  --heap <n>\t   set heap size to n KiB (default: 8192)\n");
            printf("  --gcstats\t   show garbage collection stats\n");
            printf("  --gcpurge\t   purge old objects after collection\n");
            printf("  --debug\t   start virtual machine in debug mode\n");
            printf("  --version\t   show version and exit\n");
            printf("  --help\t   show this help and exit\n");
            exit(0);
        }
        if (!strcmp(argv[i], "--version")) {
            printf("Ninja Virtual Machine version %d (compiled %s, %s)\n",
                   NINJA_BINARY_VERSION, __DATE__, __TIME__);
            exit(0);
        }
        if (!strcmp(argv[i], "--stack")) {
            if (i >= argc - 1) {
                continue;
            }
            int memory = strtol(argv[++i], (char **)NULL, 10);
            if (memory <= 0) {
                continue;
            }
            initialize_stack(memory);
            continue;
        }
        if (!strcmp(argv[i], "--heap")) {
            if (i >= argc - 1) {
                continue;
            }
            int memory = strtol(argv[++i], (char **)NULL, 10);
            if (memory <= 0) {
                continue;
            }
            initialize_heap(memory);
            continue;
        }
        if (!strcmp(argv[i], "--gcstats")) {
            vm.gc.stats_flag = true;
            continue;
        }
        if (!strcmp(argv[i], "--gcpurge")) {
            vm.gc.purge_flag = true;
            continue;
        }
        if (!strncmp("-", argv[i], strlen("-"))) {
            printf("unknown command line argument '%s', try '%s --help'\n",
                   argv[i], argv[0]);
            exit(1);
        }
        if (code_flag) {
            fatalError("more than one code file specified");
        }
        code_file = argv[i];
        code_flag = true;
        if (i < argc - 1) {
            continue;
        }
        init(code_file);
    }
    return 0;
}

NinjaVM default_ir(NinjaVM vm) {
    vm.ir.size = vm.ir.pc = 0;
    vm.ir.data = NULL;
    return vm;
}

NinjaVM default_rv(NinjaVM vm) {
    vm.rv = NULL;
    return vm;
}

NinjaVM default_stack(NinjaVM vm) {
    vm.stack.size = vm.stack.sp = vm.stack.fp = 0;
    vm.stack.memory = DEFAULT_STACK_SIZE;
    vm.stack.bytes = vm.stack.memory * Ki;
    vm.stack.max_items = vm.stack.bytes / sizeof(StackSlot);
    vm.stack.data = malloc(vm.stack.bytes);
    if (!vm.stack.data && vm.stack.size) {
        perror("malloc(vm.stack.data)");
    }
    return vm;
}

NinjaVM default_sda(NinjaVM vm) {
    vm.sda.size = 0;
    vm.sda.data = NULL;
    return vm;
}

NinjaVM default_heap(NinjaVM vm) {
    vm.heap.size = vm.heap.used = 0;
    vm.heap.memory = DEFAULT_HEAP_SIZE;
    vm.heap.bytes = vm.heap.memory * Ki;
    vm.heap.available = vm.heap.bytes / 2;
    vm.heap.active = calloc(vm.heap.bytes, sizeof(unsigned char));
    if (!vm.heap.active) {
        perror("calloc(vm.heap.active)");
    }
    vm.heap.next = vm.heap.begin = vm.heap.active;
    vm.heap.passive = vm.heap.next + vm.heap.available;
    return vm;
}

NinjaVM default_gc(NinjaVM vm) {
    vm.gc.purge_flag = vm.gc.stats_flag = vm.gc.is_running = false;
    vm.gc.copied_objects = vm.gc.copied_bytes = 0;
    vm.gc.bytes_allocated = vm.gc.objects_allocated = 0;
    return vm;
}

NinjaVM default_debugger(NinjaVM vm) {
    vm.debugger.activated = false;
    vm.debugger.bp = NULL;
    return vm;
}

NinjaVM default_vm(void) {
    vm = default_ir(vm);
    vm = default_rv(vm);
    vm = default_stack(vm);
    vm = default_sda(vm);
    vm = default_heap(vm);
    vm = default_gc(vm);
    vm = default_debugger(vm);
    return vm;
}

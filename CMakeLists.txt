cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_C_COMPILER gcc)

set(CMAKE_C_STANDARD 99)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BIGINT_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/lib/build/lib/libbigint.a)

project(njvm C)

include(FetchContent)

FetchContent_Declare(
  cmocka
  GIT_REPOSITORY https://git.cryptomilk.org/projects/cmocka.git
  GIT_TAG        cmocka-1.1.5
  GIT_SHALLOW    1
)

set(WITH_STATIC_LIB ON CACHE BOOL "CMocka: Build with a static library" FORCE)
set(WITH_CMOCKERY_SUPPORT OFF CACHE BOOL "CMocka: Install a cmockery header" FORCE)
set(WITH_EXAMPLES OFF CACHE BOOL "CMocka: Build examples" FORCE)
set(UNIT_TESTING OFF CACHE BOOL "CMocka: Build with unit testing" FORCE)
set(PICKY_DEVELOPER OFF CACHE BOOL "CMocka: Build with picky developer flags" FORCE)

FetchContent_MakeAvailable(cmocka)

add_compile_options(-g -Wall -pedantic -fcommon)

include_directories(include)

set(SOURCES
    src/njvm.c
    src/cpu/instruction.c
    src/cpu/processor.c
    src/cpu/opcode.c
    src/cpu/immediate.c
    src/memory/gc.c
    src/memory/ir.c
    src/memory/stack.c
    src/memory/sda.c
    src/memory/heap.c
    src/utils/debugger.c
    src/utils/utils.c
    src/utils/support.c
)

set(TESTS
    tests/test.c
    tests/opcode_test.c
    tests/instruction_test.c
    tests/ir_test.c
    tests/stack_test.c
    tests/processor_test.c
    tests/sda_test.c
    tests/utils_test.c
    tests/heap_test.c
    tests/gc_test.c
    tests/macros_test.c
    tests/debugger_test.c
    tests/immediate_test.c
    tests/support_test.c
)

set(TEST_HEADERS
    tests/include/cmocka/cmocka.h
    tests/include/test.h
    tests/include/opcode_test.h
    tests/include/instruction_test.h
    tests/include/ir_test.h
    tests/include/stack_test.h
    tests/include/processor_test.h
    tests/include/sda_test.h
    tests/include/utils_test.h
    tests/include/heap_test.h
    tests/include/gc_test.h
    tests/include/macros_test.h
    tests/include/debugger_test.h
    tests/include/immediate_test.h
    tests/include/support_test.h
)

add_custom_target(libbigint COMMAND make WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(njvm_lib STATIC ${SOURCES})

add_library(bigint STATIC IMPORTED)

set_property(TARGET bigint APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)

set_target_properties(bigint PROPERTIES IMPORTED_LOCATION_NOCONFIG ${BIGINT_LIBRARY})

add_dependencies(bigint libbigint)

add_dependencies(njvm_lib bigint)

target_link_libraries(njvm_lib bigint)

add_executable(njvm src/main.c)

target_link_libraries(njvm njvm_lib)

enable_testing()

add_executable(tests ${TESTS} ${TEST_HEADERS})

target_link_libraries(tests PRIVATE njvm_lib cmocka-static)

add_test(UnitTests tests)

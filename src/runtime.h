#ifndef RUNTIME_H
#define RUNTIME_H

#include <stddef.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

typedef unsigned char Byte;
typedef _Bool Bool;
typedef uint8_t Integer8;
typedef uint32_t Integer32;
typedef uint64_t Integer64;
typedef double Float64;
typedef size_t Size;

typedef struct Value Value;

typedef enum {
    ERROR_OF_OF_MEMORY
} Error;

#include <kernel/memory.h>
#include <util/decode.h>
#include <builtin/value.h>

#endif

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

#include <builtin/case.h>
#include <builtin/do.h>
#include <builtin/float.h>
#include <builtin/identifier.h>
#include <builtin/integer.h>
#include <builtin/lamda.h>
#include <builtin/list.h>
#include <builtin/map.h>
#include <builtin/module.h>
#include <builtin/protocol.h>
#include <builtin/range.h>
#include <builtin/result.h>
#include <builtin/set.h>
#include <builtin/string.h>
#include <builtin/token.h>
#include <builtin/type.h>
#include <builtin/value.h>
#include <builtin/when.h>
#include <posix/memory.h>
#include <util/decode.h>

#endif

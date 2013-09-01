#ifndef API_H
#define API_H

#include <stddef.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0
#define VALUE void

typedef unsigned char Byte;
typedef _Bool Bool;
typedef uint8_t Integer8;
typedef uint32_t Integer32;
typedef uint64_t Integer64;
typedef double Float64;
typedef size_t Size;

typedef enum {
    ErrorNone,
    ErrorOutOfMemory,
    ErrorInvalidBytecodeVersion
} Error;

typedef VALUE *Kernel(VALUE **args, Integer8 count, Error *error);

#include "boolean.h"
#include "case.h"
#include "comprehension.h"
#include "case.h"
#include "decode.h"
#include "do.h"
#include "element.h"
#include "float.h"
#include "integer.h"
#include "lamda.h"
#include "list.h"
#include "map.h"
#include "member.h"
#include "memory.h"
#include "module.h"
#include "nil.h"
#include "protocol.h"
#include "range.h"
#include "result.h"
#include "runtime.h"
#include "set.h"
#include "string.h"
#include "token.h"
#include "type.h"
#include "variable.h"
#include "when.h"

#endif

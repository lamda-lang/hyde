#ifndef RUNTIME_H
#define RUNTIME_H

#include <stddef.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0
#define VALUE void

typedef unsigned char Byte;
typedef _Bool Bool;
typedef char Char;
typedef uint8_t Integer8;
typedef uint32_t Integer32;
typedef uint64_t Integer64;
typedef double Float64;
typedef size_t Size;
typedef int File;

typedef enum {
    ErrorNone,
    ErrorOutOfMemory,
    ErrorFileOpen,
    ErrorFileClose,
    ErrorFileRead,
    ErrorFileWrite
} Error;

#include "boolean.h"
#include "case.h"
#include "comprehension.h"
#include "case.h"
#include "decode.h"
#include "do.h"
#include "element.h"
#include "file.h"
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
#include "set.h"
#include "string.h"
#include "token.h"
#include "type.h"
#include "variable.h"
#include "when.h"

#endif

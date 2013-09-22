#ifndef RUNTIME_H
#define RUNTIME_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define ERROR(error) (*error != ERROR_NONE)

typedef unsigned char Byte;
typedef size_t Size;
typedef _Bool Bool;
typedef uint8_t Integer8;
typedef uint32_t Integer32;
typedef uint64_t Integer64;
typedef double Float64;

typedef struct Case Case;
typedef struct Do Do;
typedef struct Float Float;
typedef struct Identifier Identifier;
typedef struct Integer Integer;
typedef struct Lamda Lamda;
typedef struct List List;
typedef struct Map Map;
typedef struct Module Module;
typedef struct Protocol Protocol;
typedef struct Range Range;
typedef struct Result Result;
typedef struct Set Set;
typedef struct String String;
typedef struct Token Token;
typedef struct Type Type;
typedef struct Value Value;
typedef struct When When;

typedef enum {
    ERROR_NONE,
    ERROR_OF_OF_MEMORY,
    ERROR_PRINT
} Error;

#include "case.h"
#include "decode.h"
#include "do.h"
#include "encode.h"
#include "float.h"
#include "identifier.h"
#include "integer.h"
#include "lamda.h"
#include "list.h"
#include "map.h"
#include "memory.h"
#include "module.h"
#include "protocol.h"
#include "range.h"
#include "result.h"
#include "set.h"
#include "string.h"
#include "token.h"
#include "type.h"
#include "value.h"
#include "when.h"

#endif

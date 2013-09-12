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
typedef struct Boolean Boolean;
typedef struct Case Case;
typedef struct Comprehension Comprehension;
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
typedef struct When When;

typedef enum {
    ERROR_OF_OF_MEMORY
} Error;

typedef enum {
    MODEL_BOOLEAN,
    MODEL_CASE,
    MODEL_COMPREHENSION_LIST,
    MODEL_COMPREHENSION_MAP,
    MODEL_COMPREHENSION_SET,
    MODEL_DO,
    MODEL_FLOAT,
    MODEL_IDENTIFIER,
    MODEL_INTEGER,
    MODEL_LAMDA,
    MODEL_LIST,
    MODEL_MAP,
    MODEL_MODULE,
    MODEL_NIL,
    MODEL_PROTOCOL,
    MODEL_RANGE,
    MODEL_RESULT,
    MODEL_SET,
    MODEL_STRING,
    MODEL_TOKEN,
    MODEL_TYPE,
    MODEL_WHEN
} Model;

typedef Value *Decode(Byte **bytes);
typedef Value *Kernel(Value **args, Integer8 count);

#include <builtin/boolean.h>
#include <builtin/case.h>
#include <builtin/comprehension.h>
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
#include <kernel/memory.h>
#include <util/decode.h>

#endif

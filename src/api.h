#ifndef API_H
#define API_H

#include <stddef.h>
#include <stdint.h>

/* macros */
#define TRUE 1
#define FALSE 0

/* scalar types */
typedef unsigned char Byte;
typedef _Bool Bool;
typedef char Char;
typedef uint8_t Integer8;
typedef uint16_t Integer16;
typedef uint32_t Integer32;
typedef uint64_t Integer64;
typedef double Float64;
typedef size_t Size;
typedef int File;

/* opaque types */
typedef struct Boolean Boolean;
typedef struct Case Case;
typedef struct Comprehension Comprehension;
typedef struct Do Do;
typedef struct Float Float;
typedef struct Integer Integer;
typedef struct Lamda Lamda;
typedef struct List List;
typedef struct Map Map;
typedef struct Nil Nil;
typedef struct Protocol Protocol;
typedef struct Range Range;
typedef struct Result Result;
typedef struct Set Set;
typedef struct String String;
typedef struct Token Token;
typedef struct Type Type;
typedef struct Variable Variable;
typedef struct When When;
typedef struct Value Value;

/* function types */
typedef void *Decode(Byte **code, Value **error);
typedef void Dealloc(Value *value);
typedef Integer64 Hash(Value *value);
typedef Bool Equal(Value *value, Value *other);
typedef void Enumerate(Value *value, void (*callback)(Value *value));

#include "boolean.h"
#include "case.h"
#include "comprehension.h"
#include "bridge.h"
#include "case.h"
#include "decode.h"
#include "do.h"
#include "file.h"
#include "float.h"
#include "integer.h"
#include "lamda.h"
#include "list.h"
#include "map.h"
#include "memory.h"
#include "nil.h"
#include "process.h"
#include "protocol.h"
#include "range.h"
#include "result.h"
#include "runtime.h"
#include "set.h"
#include "string.h"
#include "token.h"
#include "type.h"
#include "value.h"
#include "variable.h"
#include "when.h"

#endif

#ifndef API_H
#define API_H

#include <stddef.h>
#include <stdint.h>

#define FALSE 0
#define TRUE 1

/* scalar types */
typedef _Bool Bool;
typedef unsigned char Byte;
typedef char Char;
typedef uint8_t Integer8;
typedef uint16_t Integer16;
typedef uint32_t Integer32;
typedef uint64_t Integer64;
typedef double Float64;
typedef size_t Size;
typedef uint8_t Value;

/* opaque types */
typedef struct Code Code;
typedef struct File File;
typedef struct Data Data;
typedef struct Boolean Boolean;
typedef struct Do Do;
typedef struct Float Float;
typedef struct Identifier Identifier;
typedef struct Integer Integer;
typedef struct Lamda Lamda;
typedef struct List List;
typedef struct Map Map;
typedef struct Module Module;
typedef struct Nil Nil;
typedef struct Range Range;
typedef struct Set Set;
typedef struct String String;

/* enum types */
typedef enum {
    ErrorOutOfMemory,
    ErrorInvalidType,
    ErrorArityMismatch,
    ErrorFileOpen,
    ErrorFileRead,
    ErrorFileWrite,
    ErrorFileClose,
    ErrorMainNotFound
} Error;

typedef enum {
    StatusSuccess = TRUE,
    StatusFailure = FALSE
} Status;

typedef enum {
    TypeNil = 0,
    TypeBoolean = 1,
    TypeInteger = 2,
    TypeFloat = 3,
    TypeIdentifier = 4,
    TypeString = 5,
    TypeSet = 6,
    TypeList = 7,
    TypeMap = 8,
    TypeRange = 9,
    TypeModule = 10,
    TypeDo = 11,
    TypeLamda = 12
} Type;

typedef enum {
    FlagGarbage = 1 << 4,
    FlagMark = 1 << 5
} Flag;

/* function types */
typedef void *Decode(Byte **code, Error *error);
typedef Value *Eval(void *data, Code *code, Value **context, Bool pure, Error *error);
typedef void Dealloc(Value *value);
typedef Integer64 Hash(Value *value);
typedef Bool Equal(Value *value, Value *other);
typedef void Enumerate(Value *value, void (*callback)(Value *value));

#include "arg.h"
#include "boolean.h"
#include "bridge.h"
#include "case.h"
#include "code.h"
#include "data.h"
#include "decode.h"
#include "do.h"
#include "error.h"
#include "file.h"
#include "float.h"
#include "identifier.h"
#include "identity.h"
#include "import.h"
#include "integer.h"
#include "lamda.h"
#include "list.h"
#include "map.h"
#include "memory.h"
#include "module.h"
#include "nil.h"
#include "process.h"
#include "range.h"
#include "result.h"
#include "runtime.h"
#include "set.h"
#include "string.h"
#include "value.h"
#include "when.h"

#endif

#ifndef API_H
#define API_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* scalar types */
typedef unsigned char Byte;
typedef char Char;
typedef uint8_t Integer8;
typedef uint16_t Integer16;
typedef uint32_t Integer32;
typedef uint64_t Integer64;
typedef size_t Size;
typedef uint8_t Value;
typedef uint8_t Error;
typedef double Float64;
typedef bool Status;
typedef uint8_t Type;
typedef uint8_t Flag;

/* opaque types */
typedef struct Code Code;
typedef struct File File;
typedef struct Stack Stack;
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

/* function types */
typedef void *Decode(Byte **code, Error *error);
typedef Value *Eval(void *data, Code *code, bool pure, Error *error);
typedef Value *Kernel(Value **values, Integer8 count, Error *error);
typedef void Dealloc(Value *value);
typedef Integer64 Hash(Value *value);
typedef bool Equal(Value *value, Value *other);
typedef void Enumerate(Value *value, void (*callback)(Value *value));
typedef void Fetch(Value *value, Value **values);

typedef union {
    Value *value;
    Integer32 index;
} Element;

/* enumerations */
enum {
    ErrorOutOfMemory,
    ErrorInvalidType,
    ErrorArityMismatch,
    ErrorFileOpen,
    ErrorFileRead,
    ErrorFileWrite,
    ErrorFileClose,
    ErrorMainNotFound
};

enum {
    StatusSuccess = true,
    StatusFailure = false
};

enum {
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
    TypeLamda = 12,
};

enum {
    FlagNone = 0,
    FlagGarbage = 1 << 4,
    FlagMark = 1 << 5,
    FlagAlpha = 1 << 6,
    FlagBeta = 1 << 7
};

#include "arg.h"
#include "boolean.h"
#include "bridge.h"
#include "code.h"
#include "data.h"
#include "decode.h"
#include "do.h"
#include "error.h"
#include "file.h"
#include "float.h"
#include "global.h"
#include "identifier.h"
#include "integer.h"
#include "kernel.h"
#include "lamda.h"
#include "list.h"
#include "map.h"
#include "memory.h"
#include "module.h"
#include "nil.h"
#include "process.h"
#include "range.h"
#include "runtime.h"
#include "set.h"
#include "stack.h"
#include "string.h"
#include "value.h"
#include "when.h"

#endif

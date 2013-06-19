#ifndef API_H
#define API_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef unsigned char Byte;

typedef char Char;

typedef uint8_t Integer8;

typedef uint16_t Integer16;

typedef uint32_t Integer32;

typedef uint64_t Integer64;

typedef uintmax_t Index;

typedef size_t Size;

typedef uint8_t Value;

typedef double Float64;

typedef uint8_t Error;
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

typedef bool Status;
enum {
    StatusSuccess = true,
    StatusFailure = false
};

typedef uint8_t Type;
enum {
    TypeBoolean = 0,
    TypeCase = 1,
    TypeDo = 2,
    TypeFloat = 3,
    TypeIdentifier = 4,
    TypeInteger = 5,
    TypeLamda = 6,
    TypeList = 7,
    TypeMap = 8,
    TypeModule = 9,
    TypeNil = 10,
    TypeRange = 11,
    TypeResult = 12,
    TypeSet = 13,
    TypeString = 14,
    TypeWhen = 15
};

typedef uint8_t Flag;
enum {
    FlagNone = 0,
    FlagGarbage = 1 << 4,
    FlagMark = 1 << 5,
    FlagAlpha = 1 << 6,
    FlagBeta = 1 << 7
};

typedef union {
    Value *value;
    Integer32 index;
} Element;

typedef struct File File;

typedef struct Data Data;

typedef struct Boolean Boolean;

typedef struct Case Case;

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

typedef struct Result Result;

typedef struct Set Set;

typedef struct String String;

typedef struct When When;

typedef Value *Instruction(Byte **code, Error *error);

typedef Value *Eval(Value *value, bool pure, Error *error);

typedef Value *Kernel(Value **values, Integer8 count, Error *error);

typedef void Dealloc(Value *value);

typedef Integer64 Hash(Value *value);

typedef void Enumerate(Value *value, void (*callback)(Value *value));

typedef void Fetch(Value *value, Value **values);

#include "arg.h"
#include "boolean.h"
#include "bridge.h"
#include "case.h"
#include "data.h"
#include "decode.h"
#include "do.h"
#include "error.h"
#include "execute.h"
#include "file.h"
#include "float.h"
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
#include "result.h"
#include "runtime.h"
#include "set.h"
#include "stack.h"
#include "string.h"
#include "value.h"
#include "when.h"

#endif

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
    ErrorFileClose
};

typedef bool Status;
enum {
    StatusSuccess = true,
    StatusFailure = false
};

typedef uint8_t Type;
enum {
    TypeBoolean = 0,
    TypeDo = 1,
    TypeFloat = 2,
    TypeIdentifier = 3,
    TypeInteger = 4,
    TypeLambda = 5,
    TypeList = 6,
    TypeMap = 7,
    TypeNil = 8,
    TypeRange = 9,
    TypeSet = 10,
    TypeString = 11
};

typedef uint8_t Flag;
enum {
    FlagNone = 0,
    FlagGarbage = 1 << 4,
    FlagMark = 1 << 5
};

typedef struct Args Args;

typedef struct File File;

typedef struct Stack Stack;

typedef struct Data Data;

typedef struct Boolean Boolean;

typedef struct Do Do;

typedef struct Float Float;

typedef struct Identifier Identifier;

typedef struct Integer Integer;

typedef struct Lambda Lambda;

typedef struct List List;

typedef struct Map Map;

typedef struct Nil Nil;

typedef struct Range Range;

typedef struct Set Set;

typedef struct String String;

typedef bool Kernel(Integer8 arity, Stack *stack);

typedef void Dealloc(Value *value);

typedef Integer64 Hash(Value *value);

typedef void Enumerate(Value *value, void (*block)(Value *value));

#include "boolean.h"
#include "data.h"
#include "decode.h"
#include "do.h"
#include "execute.h"
#include "file.h"
#include "float.h"
#include "identifier.h"
#include "integer.h"
#include "kernel.h"
#include "lambda.h"
#include "list.h"
#include "map.h"
#include "memory.h"
#include "nil.h"
#include "range.h"
#include "set.h"
#include "stack.h"
#include "string.h"
#include "value.h"

#endif

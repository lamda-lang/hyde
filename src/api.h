#ifndef API_H
#define API_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef unsigned char Byte;

typedef char Char;

typedef uint8_t Integer8Bit;

typedef uint16_t Integer16Bit;

typedef uint32_t Integer32Bit;

typedef uint64_t Integer64Bit;

typedef uintmax_t Index;

typedef size_t Size;

typedef uint8_t Value;

typedef uint8_t Exception;
enum {
  ExceptionOutOfMemory,
  ExceptionInvalidType
};

typedef bool Status;
enum {
  StatusSuccess = true,
  StatusFailure = false
};

typedef uint8_t Type;
enum {
  TypeBoolean = 0,
  TypeIdentifier = 1,
  TypeInteger = 2,
  TypeLambda = 3,
  TypeList = 4,
  TypeMap = 5,
  TypeNil = 6,
  TypeString = 7
};

typedef uint8_t Flag;
enum {
  FlagNone = 0,
  FlagGarbage = 1 << 4,
  FlagMark = 1 << 5
};

typedef struct File File;

typedef struct Stack Stack;

typedef struct Data Data;

typedef struct Boolean Boolean;

typedef struct Identifier Identifier;

typedef struct Integer Integer;

typedef struct Lambda Lambda;

typedef struct List List;

typedef struct Map Map;

typedef struct String String;

typedef struct Nil Nil;

typedef bool Kernel(Integer8Bit arity, Stack *stack);

typedef void Dealloc(Value *dealloc);

typedef Integer64Bit Hash(Value *value);

typedef void Enumerate(Value *value, void (*block)(Value *value));

#include "boolean.h"
#include "data.h"
#include "decode.h"
#include "exception.h"
#include "execute.h"
#include "file.h"
#include "identifier.h"
#include "integer.h"
#include "kernel.h"
#include "lambda.h"
#include "list.h"
#include "map.h"
#include "memory.h"
#include "nil.h"
#include "stack.h"
#include "string.h"
#include "value.h"

#endif

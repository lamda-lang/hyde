#ifndef RUNTIME_H
#define RUNTIME_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef unsigned char Byte;

typedef uint8_t Integer8Bit;

typedef uint16_t Integer16Bit;

typedef uint32_t Integer32Bit;

typedef uint64_t Integer64Bit;

typedef uintmax_t Index;

typedef size_t Size;

typedef uint8_t Value;

typedef enum {
  StatusSuccess = true,
  StatusFailure = false
} Status;

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
  FlagMark = 1 << 5,
  FlagAlpha = 1 << 6,
  FlagBeta = 1 << 7
};

typedef int File;
enum {
  FileStandartIn = STDIN_FILENO,
  FileStandartOut = STDOUT_FILENO,
  FileStandartError = STDERR_FILENO
};

typedef struct Stack Stack;

typedef struct Buffer Buffer;

typedef struct Identifier Identifier;

typedef struct Integer Integer;

typedef struct Lambda Lambda;

typedef struct List List;

typedef struct Map Map;

typedef struct String String;

typedef struct Nil Nil;

typedef struct Boolean Boolean;

typedef bool Kernel(Integer8Bit arity, Stack *stack);

typedef void Dealloc(Value *dealloc);

typedef Integer64Bit Hash(Value *value);

typedef void Enumerate(Value *value, void (*block)(Value *value));

#endif

#include "boolean.h"
#include "buffer.h"
#include "decode.h"
#include "execute.h"
#include "file.h"
#include "identifier.h"
#include "integer.h"
#include "kernel.h"
#include "lambda.h"
#include "list.h"
#include "log.h"
#include "map.h"
#include "memory.h"
#include "nil.h"
#include "stack.h"
#include "string.h"
#include "value.h"

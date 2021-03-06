#ifndef RUNTIME_H
#define RUNTIME_H

#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0
#define BOOL_SIZE 1
#define INTEGER_8_SIZE 1
#define INTEGER_16_SIZE 2
#define INTEGER_32_SIZE 4
#define INTEGER_64_SIZE 8
#define FLOAT_64_SIZE 8

typedef unsigned char Byte;
typedef size_t Size;
typedef _Bool Bool;
typedef uint8_t Integer8;
typedef uint16_t Integer16;
typedef uint32_t Integer32;
typedef uint64_t Integer64;
typedef double Float64;
typedef struct Binary Binary;
typedef struct Boolean Boolean;
typedef struct Case Case;
typedef struct Context Context;
typedef struct Do Do;
typedef struct Exception Exception;
typedef struct Float Float;
typedef struct Identifier Identifier;
typedef struct Integer Integer;
typedef struct Kernel Kernel;
typedef struct Lamda Lamda;
typedef struct List List;
typedef struct Map Map;
typedef struct Module Module;
typedef struct Nil Nil;
typedef struct Result Result;
typedef struct Set Set;
typedef struct Stack Stack;
typedef struct String String;
typedef struct Token Token;
typedef struct Value Value;
typedef struct When When;

#include "binary.h"
#include "boolean.h"
#include "case.h"
#include "context.h"
#include "do.h"
#include "exception.h"
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
#include "result.h"
#include "set.h"
#include "stack.h"
#include "string.h"
#include "token.h"
#include "value.h"
#include "when.h"

#endif

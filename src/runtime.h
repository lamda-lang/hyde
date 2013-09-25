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
#define ERROR(error) (*error != ERROR_NONE)

typedef unsigned char Byte;
typedef size_t Size;
typedef _Bool Bool;
typedef uint8_t Integer8;
typedef uint16_t Integer16;
typedef uint32_t Integer32;
typedef uint64_t Integer64;
typedef double Float64;
typedef int File;
typedef char Char;

typedef struct Binary Binary;
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
    ERROR_FILE_OPEN,
    ERROR_FILE_CLOSE,
    ERROR_FILE_READ,
    ERROR_FILE_WRITE,
    ERROR_FILE_STATUS
} Error;

enum {
    OPCODE_BINARY = 23,
    OPCODE_BOOLEAN_TRUE = 0,
    OPCODE_BOOLEAN_FALSE = 1,
    OPCODE_CASE = 2,
    OPCODE_DO = 6,
    OPCODE_FLOAT = 7,
    OPCODE_IDENTIFIER = 8,
    OPCODE_INTEGER = 9,
    OPCODE_LAMDA = 10,
    OPCODE_LIST = 11,
    OPCODE_MAP = 12,
    OPCODE_MODULE = 13,
    OPCODE_NIL = 14,
    OPCODE_PROTOCOL = 15,
    OPCODE_RANGE = 16,
    OPCODE_RESULT = 17,
    OPCODE_SET = 18,
    OPCODE_STRING = 19,
    OPCODE_TOKEN = 20,
    OPCODE_TYPE = 21,
    OPCODE_WHEN = 22
};

#include "binary.h"
#include "case.h"
#include "decode.h"
#include "do.h"
#include "encode.h"
#include "file.h"
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

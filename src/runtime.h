#ifndef RUNTIME_H
#define RUNTIME_H

#include <stddef.h>
#include <stdint.h>

/* macros */
#define TRUE 1
#define FALSE 0
#define VALUE Type

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

/* function types */
typedef VALUE *Decode(Byte **bytes, VALUE **error);
typedef Integer64 Hash(VALUE *value);
typedef Bool Equal(VALUE *value, VALUE *other);
VALUE *Kernel(VALUE **args, Integer8 count, VALUE **error);

/* global errors */
extern VALUE *RuntimeOutOfMemoryError;
extern VALUE *RuntimeFileOpenError;
extern VALUE *RuntimeFileReadError;
extern VALUE *RuntimeFileWriteError;
extern VALUE *RuntimeFileCloseError;
extern VALUE *RuntimeInvalidTypeError;
extern VALUE *RuntimeArityMismatchError;

/* global types */
extern Type *RuntimeBooleanType;
extern Type *RuntimeCaseType;
extern Type *RuntimeComprehensionType;
extern Type *RuntimeDoType;
extern Type *RuntimeFloatType;
extern Type *RuntimeIntegerType;
extern Type *RuntimeLamdaType;
extern Type *RuntimeListType;
extern Type *RuntimeMapType;
extern Type *RuntimeNilType;
extern Type *RuntimeProtocolType;
extern Type *RuntimeRangeType;
extern Type *RuntimeResultType;
extern Type *RuntimeSetType;
extern Type *RuntimeStringType;
extern Type *RuntimeTokenType;
extern Type *RuntimeTypeType;
extern Type *RuntimeVariableType;
extern Type *RuntimeWhenType;

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
#include "set.h"
#include "string.h"
#include "token.h"
#include "type.h"
#include "variable.h"
#include "when.h"

#endif

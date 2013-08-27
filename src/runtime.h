#ifndef RUNTIME_H
#define RUNTIME_H

#include <stddef.h>
#include <stdint.h>

/* macros */
#define TRUE 1
#define FALSE 0
#define VALUE void

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

/* function types */
typedef VALUE *Decode(Byte **bytes, VALUE **error);
typedef Integer64 Hash(VALUE *value);
typedef Bool Equal(VALUE *value, VALUE *other);
VALUE *Kernel(VALUE **args, Integer8 count, VALUE **error);

/* global error values */
extern VALUE *RuntimeOutOfMemoryError;
extern VALUE *RuntimeFileOpenError;
extern VALUE *RuntimeFileReadError;
extern VALUE *RuntimeFileWriteError;
extern VALUE *RuntimeFileCloseError;
extern VALUE *RuntimeInvalidTypeError;
extern VALUE *RuntimeArityMismatchError;

/* global type values */
extern VALUE *RuntimeBooleanType;
extern VALUE *RuntimeCaseType;
extern VALUE *RuntimeComprehensionType;
extern VALUE *RuntimeDoType;
extern VALUE *RuntimeFloatType;
extern VALUE *RuntimeIntegerType;
extern VALUE *RuntimeLamdaType;
extern VALUE *RuntimeListType;
extern VALUE *RuntimeMapType;
extern VALUE *RuntimeNilType;
extern VALUE *RuntimeProtocolType;
extern VALUE *RuntimeRangeType;
extern VALUE *RuntimeResultType;
extern VALUE *RuntimeSetType;
extern VALUE *RuntimeStringType;
extern VALUE *RuntimeTokenType;
extern VALUE *RuntimeTypeType;
extern VALUE *RuntimeVariableType;
extern VALUE *RuntimeWhenType;

#include "boolean.h"
#include "case.h"
#include "comprehension.h"
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

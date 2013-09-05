#ifndef API_H
#define API_H

#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* macro */
#define TRUE 1
#define FALSE 0
#define VALUE void

/* type */
typedef unsigned char Byte;
typedef _Bool Bool;
typedef uint8_t Integer8;
typedef uint32_t Integer32;
typedef uint64_t Integer64;
typedef double Float64;
typedef size_t Size;

typedef enum {
    ErrorNone,
    ErrorOutOfMemory,
    ErrorInvalidBytecodeVersion
} Error;

typedef enum {
    ConstantBooleanType,
    ConstantCaseType,
    ConstantComprehensionType,
    ConstantDoType,
    ConstantElementType,
    ConstantFloatType,
    ConstantIntegerType,
    ConstantLamdaType,
    ConstantListType,
    ConstantMapType,
    ConstantMemberType,
    ConstantModuleType,
    ConstantNilType,
    ConstantProtocolType,
    ConstantRangeType,
    ConstantResultType,
    ConstantSetType,
    ConstantStringType,
    ConstantTokenType,
    ConstantTypeType,
    ConstantVariableType,
    ConstantWhenType,
    ConstantNil,
    ConstantTrue,
    ConstantFalse
} Constant;

typedef VALUE *Kernel(VALUE **args, Integer8 count, Error *error);

#include "boolean.h"
#include "case.h"
#include "comprehension.h"
#include "decode.h"
#include "do.h"
#include "element.h"
#include "float.h"
#include "integer.h"
#include "lamda.h"
#include "list.h"
#include "map.h"
#include "member.h"
#include "memory.h"
#include "module.h"
#include "nil.h"
#include "protocol.h"
#include "range.h"
#include "result.h"
#include "runtime.h"
#include "set.h"
#include "string.h"
#include "thread.h"
#include "token.h"
#include "type.h"
#include "variable.h"
#include "when.h"

#endif

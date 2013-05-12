#ifndef RUNTIME
#define RUNTIME

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/** -brief The smallest addressable unit of memory. */
typedef unsigned char RTByte;

/** -brief An integer type capable of representing any member of the basic execution character set. */
typedef char RTChar;

/** -brief An 8-bit unsigned integer type. */
typedef uint8_t RTInteger8Bit;

/** -brief A 16-bit unsigned integer type. */
typedef uint16_t RTInteger16Bit;

/** -brief A 32-bit unsigned integer type. */
typedef uint32_t RTInteger32Bit;

/** -brief A 64-bit unsigned integer type. */
typedef uint64_t RTInteger64Bit;

/** -brief An unsigned integer type capable of representing any value of any unsigned integer type. */
typedef uintmax_t RTIndex;

/** -brief An unsigned integer type capable of representing the size of any memory object, in bytes. */
typedef size_t RTSize;

typedef uint8_t RTValue;

/** -brief An enumeration of types. */
typedef enum {
  RTTypeBoolean = 0,
  RTTypeIdentifier = 1,
  RTTypeInteger = 2,
  RTTypeLambda = 3,
  RTTypeList = 4,
  RTTypeMap = 5,
  RTTypeNil = 6,
  RTTypeString = 7
} RTType;

/** -brief An enumeration of flags. */
typedef enum {
  RTFlagMark = 1 << 0,
  RTFlagAlpha = 1 << 1,
} RTFlag;

typedef enum {
  RTErrorNone = 0,
  RTErrorOutOfMemory = 1,
  RTErrorInvalidType = 2,
  RTErrorInvalidOpcode = 3
} RTError;

typedef struct RTStack RTStack;

/** -brief An opaque data type that represents a primitive identifier. */
typedef struct RTIdentifier RTIdentifier;

/** -brief An opaque data type that represents a primitive integer. */
typedef struct RTInteger RTInteger;

/** -brief An opaque data type that represents a primitive lambda. */
typedef struct RTLambda RTLambda;

/** -brief An opaque data type that represents a primitive list. */
typedef struct RTList RTList;

/** -brief An opaque data type that represents a primitive map. */
typedef struct RTMap RTMap;

/** -brief An opaque data type that represents a primitive string. */
typedef struct RTString RTString;

typedef struct RTNil RTNil;

typedef struct RTBoolean RTBoolean;

typedef void RTBlock(RTValue *value);

#endif

#include "RTBoolean.h"
#include "RTCollect.h"
#include "RTDecode.h"
#include "RTEncode.h"
#include "RTExecute.h"
#include "RTIdentifier.h"
#include "RTInteger.h"
#include "RTLambda.h"
#include "RTList.h"
#include "RTMap.h"
#include "RTMemory.h"
#include "RTNil.h"
#include "RTStack.h"
#include "RTString.h"
#include "RTValue.h"

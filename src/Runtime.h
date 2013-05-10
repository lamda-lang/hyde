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
typedef uint8_t RTType;
enum {
  RTTypeBoolean = 0 << 0,
  RTTypeIdentifier = 1 << 0,
  RTTypeInteger = 2 << 0,
  RTTypeLambda = 3 << 0,
  RTTypeList = 4 << 0,
  RTTypeMap = 5 << 0,
  RTTypeNil = 6 << 0,
  RTTypeString = 7 << 0
};

/** -brief An enumeration of types. */
typedef uint8_t RTImplementation;
enum {
  RTImplementationAlpha = 0 << 4,
  RTImplementationBeta = 1 << 4,
  RTImplementationGamma = 2 << 4,
  RTImplementationDelta = 3 << 4,
};

/** -brief An enumeration of flags. */
typedef uint8_t RTFlag;
enum {
  RTFlagNone = 0,
  RTFlagMark = 1 << 6,
  RTFlagAlpha = 1 << 7
};

typedef enum {
  RTErrorNone = 0,
  RTErrorOutOfMemory = 1,
  RTErrorInvalidType = 2,
  RTErrorInvalidOpcode = 3
} RTError;

/** -brief An opaque data type that represents a value pool. */
typedef struct RTPool RTPool;

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
#include "RTPool.h"
#include "RTString.h"
#include "RTValue.h"

#ifndef RUNTIME
#define RUNTIME

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** -brief The size of an array with [length] elements of type [type], in bytes.
    -arg type The type of the elements.
    -arg length The element count of the array. */
#define SIZE_OF(type, length) (sizeof(type) * length)

/** -brief Prints an error message if [condition] is [FALSE].
    -arg condition A boolean condition. */
#define ASSERT(condition) if (!(condition)) fprintf(stderr, "%s:%i: ASSERT(%s) did fail\n", __FILE__, __LINE__, #condition)

/** -brief Prints an error and terminates the process if [condition] is [FALSE].
    -arg condition A boolean condition. */
#define REQUIRE(condition) if (!(condition)) (fprintf(stderr, "%s:%i: REQUIRE(%s) did fail\n", __FILE__, __LINE__, #condition), exit(EXIT_FAILURE))

/** -brief The smallest addressable unit of memory. */
typedef unsigned char RTByte;

/** -brief An integer type capable of representing any member of the basic execution character set. */
typedef char RTChar;

/** -brief An boolean type capable of representing [TRUE] and [FALSE]. */
typedef _Bool RTBool;

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

/** -brief The boolean values [TRUE] and [FALSE]. */
enum {
  TRUE = 1,
  FALSE = 0
};

/** -brief An opaque data type that represents a primitive value. */
typedef struct RTValue *RTValue;

/** -brief An opaque data type that represents a primitive identifier. */
typedef struct RTIdentifier *RTIdentifier;

/** -brief An opaque data type that represents a primitive integer. */
typedef struct RTInteger *RTInteger;

/** -brief An opaque data type that represents a primitive list. */
typedef struct RTList *RTList;

/** -brief An opaque data type that represents a primitive map. */
typedef struct RTMap *RTMap;

/** -brief An opaque data type that represents a primitive string. */
typedef struct RTString *RTString;

/** -brief A generic pointer type capable of storing a pointer to any primitive.. */
typedef union {
  RTIdentifier id;
  RTInteger integer;
  RTList list;
  RTMap map;
  RTString string;
} RTPrimitive;

#endif

#include "RTDecode.h"
#include "RTEncode.h"
#include "RTExecute.h"
#include "RTIdentifier.h"
#include "RTInteger.h"
#include "RTList.h"
#include "RTMap.h"
#include "RTMemory.h"
#include "RTOperation.h"
#include "RTString.h"
#include "RTValue.h"

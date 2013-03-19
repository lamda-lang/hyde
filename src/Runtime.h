/** @module Runtime
    @brief Inclusions, macros and types of the runtime. */

#ifndef RUNTIME
#define RUNTIME

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief The size of an array with @code{length} elements of type @code{type}.
    @arg type The type of the elements.
    @arg length The length of the array. */
#define SIZE_OF(type, length) (sizeof(type) * length)

/** @brief Prints an error if @code{condition} is @code{false}.
    @arg condition A boolean condition. */
#define ASSERT(condition) if (!(condition)) fprintf(stderr, "%s:%i: ASSERT(%s) did fail\n", __FILE__, __LINE__, #condition)

/** @brief Prints an error and terminates the process if @code{condition} is @code{false}.
    @arg condition A boolean condition. */
#define REQUIRE(condition) if (!(condition)) (fprintf(stderr, "%s:%i: REQUIRE(%s) did fail\n", __FILE__, __LINE__, #condition), exit(EXIT_FAILURE))

/** @brief The smallest addressable unit of memory. */
typedef unsigned char RTByte;

/** @brief An integer type capable of representing any member of the basic execution character set. */
typedef char RTChar;

/** @brief An integer type capable of representing @code{TRUE} and @{FALSE}. */
typedef _Bool RTBool;

/** @brief An 8-bit unsigned integer type. */
typedef uint8_t RTInteger8Bit;

/** @brief A 16-bit unsigned integer type. */
typedef uint16_t RTInteger16Bit;

/** @brief A 32-bit unsigned integer type. */
typedef uint32_t RTInteger32Bit;

/** @brief A 64-bit unsigned integer type. */
typedef uint64_t RTInteger64Bit;

/** @brief An unsigned integer type capable of representing any value of any unsigned integer type. */
typedef uintmax_t RTIndex;

/** @brief An unsigned integer type capable of representing the size of any buffer, in bytes. */
typedef size_t RTSize;

/** @brief The boolean values @code{TRUE} and @code{FALSE}. */
enum {
  TRUE = 1,
  FALSE = 0
};

/** @brief An enumeration of existing primitive types. */
typedef enum {
  IDENTIFIER = 0,
  LIST = 1,
  MODULE = 2,
  STRING = 3
} RTType;

/** @brief An opaque data type that represents a bytecode block. */
typedef struct RTBytecode *RTBytecode;

/** @brief An opaque data type that represents a bytecode interpreter. */
typedef struct RTInterpreter *RTInterpreter;

/** @brief An opaque data type that represents a primitive. */
typedef struct RTPrimitive *RTPrimitive;

/** @brief An opaque data type that represents an identifier. */
typedef struct RTIdentifier *RTIdentifier;

/** @brief An opaque data type that represents a list. */
typedef struct RTList *RTList;

/** @brief An opaque data type that represents a module. */
typedef struct RTModule *RTModule;

/** @brief An opaque data type that represents a string. */
typedef struct RTString *RTString;

/** */
typedef RTPrimitive (*RTCreate)(RTByte **instruction);

/** */
typedef void (*RTFetch)(RTByte **instruction, RTPrimitive *reg);

/** */
typedef void (*RTDealloc)(void *object);

/** */
typedef RTInteger32Bit (*RTHash)(void *object);

/** */
typedef RTBool (*RTEqual)(void *object, void *other);

#endif

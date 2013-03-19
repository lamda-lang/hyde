/** @module RTCreate */

#ifndef RT_CREATE
#define RT_CREATE

#include "Runtime.h"

/** @brief Creates a @code{RTIdentifier} object. */
RTPrimitive RTCreateIdentifier(RTByte **instruction);

/** @brief Creates a @code{RTString} object. */
RTPrimitive RTCreateString(RTByte **instruction);

/** @brief Creates a @code{RTList} object. */
RTPrimitive RTCreateList(RTByte **instruction);

/** @brief Creates a @code{RTModule} object. */
RTPrimitive RTCreateModule(RTByte **instruction);

#endif

/** @module RTFecth */

#ifndef RT_FETCH
#define RT_FETCH

#include "Runtime.h"

/** @brief Fetches the content of a @code{RTList} object. */
void RTFetchList(RTByte **instruction, RTPrimitive *reg);

/** @brief Fetches the content of a @code{RTModule} object. */
void RTFetchModule(RTByte **instruction, RTPrimitive *reg);

#endif

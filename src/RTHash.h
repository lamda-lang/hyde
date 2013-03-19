/** @module RTHash
    @brief API for creating hash values. */

#ifndef RT_HASH
#define RT_HASH

#include "Runtime.h"

/** @brief Calculates a hash value that is based on the content of @code{buffer}.
    @arg buffer The buffer on which the hash value is based.
    @arg size The size of @code{buffer} on which the hash value is based, in bytes.
    @return The hash value. */
RTInteger32Bit RTHashValue(void *buffer, RTSize size);

#endif

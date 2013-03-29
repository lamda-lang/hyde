#ifndef RT_MEMORY
#define RT_MEMORY

#include "Runtime.h"

/** @brief Allocates a memory buffer.
    @arg size The size of the memory buffer, in bytes.
    @return The memory buffer, or @code{NULL} if allocation fails. */
void *RTMemoryAlloc(RTSize size);

/** @brief Deallocates a memory buffer.
    @arg buffer The memory buffer or @code{NULL}. */
void RTMemoryDealloc(void *buffer);

/** @brief Copies @code{size} bytes from @code{source} to @code{target}.
    @warning @code{source} and @code{target} must not overlap.
    @arg source The buffer that is used as the source.
    @arg target The buffer that is used as the target.
    @arg size The size of @code{source} that will be copied, in bytes.
    @effect The content of @code{target} is overriden. */
void RTMemoryCopy(void *source, void *target, RTSize size);

/** @brief Compares @code{size} bytes of @code{buffer} and @code{other}.
    @arg buffer A buffer.
    @arg other Another buffer.
    @arg size The size of the buffers that will be compared, in bytes.
    @return @code{TRUE} if @code{size} bytes are equal, otherwise @code{FALSE}. */
RTBool RTMemoryCompare(void *buffer, void *other, RTSize size);

#endif

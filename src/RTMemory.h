#ifndef RT_MEMORY
#define RT_MEMORY

#include "Runtime.h"

/** -brief Allocates a memory buffer.
    -arg size The size of the memory buffer, in bytes.
    -return The memory buffer, or [NULL] if allocation fails. */
void *RTMemoryAlloc(RTSize size);

/** -brief Deallocates a memory buffer.
    -arg buffer The memory buffer or [NULL]. */
void RTMemoryDealloc(void *buffer);

/** -brief Copies [size] bytes from [source] to [target].
    -warning [source] and [target] must not overlap.
    -arg source The buffer that is used as the source.
    -arg target The buffer that is used as the target.
    -arg size The size of [source] to copy, in bytes.
    -effect [target] is overriden. */
void RTMemoryCopy(void *source, void *target, RTSize size);

/** -brief Compares [size] bytes of [buffer] and [other].
    -arg buffer A buffer.
    -arg other Another buffer.
    -arg size The size of the buffers to compare, in bytes.
    -return [TRUE] if [size] bytes are equal, otherwise [FALSE]. */
RTBool RTMemoryCompare(void *buffer, void *other, RTSize size);

#endif

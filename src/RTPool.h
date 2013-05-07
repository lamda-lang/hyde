#ifndef RT_POOL
#define RT_POOL

#include "Runtime.h"

/** -brief Creates an empty value pool.
    -return An empty [RTPool]. */
RTPool RTPoolCreate(void);

/** -brief Deallocates the memory occupied by [pool].
    -arg pool The pool to deallocate.
    -important The values contained by [pool] are not deallocated. */
void RTPoolDealloc(RTPool pool);

/** -brief Adds [value] to [pool].
    -arg pool The pool to which [value] is to be added.
    -arg value The value to add to [pool].
    -return [TRUE] if function succeeds, otherwise [FALSE].
    -effect [value] is deallocated if function fails.
    -effect [value] is part of [pool]. */
RTBool RTPoolAddValue(RTPool pool, RTValue value);

/** -brief Deallocates all values contained by [pool] that are not reachablefrom [root]. 
    -arg pool The pool to drain.
    -arg root The root of the remaining values.
    -effect The pool is empty. */
void RTPoolDrain(RTPool pool, RTValue root);

#endif

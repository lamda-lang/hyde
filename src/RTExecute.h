#ifndef RT_EXECUTE
#define RT_EXECUTE

#include "Runtime.h"

/** -brief Executes [code] and returns an [RTValue].
    -arg code The code to execute.
    -return The return value of [code]. */
RTValue RTExecuteBytecode(RTByte *code);

#endif

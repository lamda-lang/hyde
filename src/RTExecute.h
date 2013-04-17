#ifndef RT_EXECUTE
#define RT_EXECUTE

#include "Runtime.h"

/** -brief Executes [code] and returns an [RTValue].
    -arg code The code to execute.
    -arg arg The arguments to use.
    -arg count The number of arguments in [arg].
    -return The return value of [code]. */
RTValue RTExecuteCode(RTByte *code, RTValue *arg, RTInteger8Bit count);

#endif

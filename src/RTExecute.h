#ifndef RT_EXECUTE
#define RT_EXECUTE

#include "Runtime.h"

/** -brief Executes [code].
    -arg code The code to execute.
    -arg count The number of instructions in [code].
    -arg stack The stack to use.
    -effect [reg] is modified according to the code being executed.
    -effect All values created by executing [code] are part of [pool]. */
RTError RTExecuteCode(RTByte *code, RTInteger32Bit count, RTStack *stack);

#endif

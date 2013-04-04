#ifndef RT_OPERATION
#define RT_OPERATION

#include "Runtime.h"

/** -brief Executes a single instruction.
    -arg instruction The instruction to execute.
    -arg reg The register set.
    -return [TRUE] on success, otherwise [FALSE].
    -effect [reg] is overridden according to the instruction being executed. 
    -effect [*instruction] points one past the byte segment that contains the instruction. */
RTBool RTOperationExecute(RTByte **instruction, RTValue *reg);

#endif

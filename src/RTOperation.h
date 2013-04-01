#ifndef RT_OPERATION
#define RT_OPERATION

#include "Runtime.h"

/** @brief Executes a single instruction.
    @arg instruction The instruction to execute.
    @arg reg The register set.
    @arg index The next expression register index.
    @return @code{TRUE} on success, otherwise @code{FALSE}.
    @effect @code{reg} is modified according to the instruction being executed. 
    @effect @code{*instruction} points one past the byte segment that contains the instruction. */
RTBool RTOperationExecute(RTByte **instruction, RTValue *reg, RTInteger32Bit index);

#endif

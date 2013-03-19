/** @module RTExecute
    @brief API for executing instructions */

#ifndef RT_EXECUTE
#define RT_EXECUTE

#include "Runtime.h"

RTPrimitive RTExecuteBytecode(RTByte *code, RTPrimitive *reg);

#endif

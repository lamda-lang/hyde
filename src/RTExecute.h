/** @module RTExecute
    @brief API for executing instructions */

#ifndef RT_EXECUTE
#define RT_EXECUTE

#include "Runtime.h"

RTValue RTExecuteBytecode(RTByte *code, RTValue *reg);

#endif

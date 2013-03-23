#ifndef RT_EXECUTE
#define RT_EXECUTE

#include "Runtime.h"

/* @brief Executes @code{code} and returns an @code{RTValue}.
   @arg code The code to execute.
   @return The return value of @code{code}. */
RTValue RTExecuteBytecode(RTByte *code);

#endif

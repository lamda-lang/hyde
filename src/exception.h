#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "runtime.h"

Value *ExceptionWhenClause(Stack *stack);
Value *ExceptionCaseClause(Value *arg, Stack *stack);
Value *ExceptionIdentifierUnbound(Stack *stack);
Bool ExceptionEqual(Exception *exception, Exception *other);

#endif

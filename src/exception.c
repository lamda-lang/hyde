#include "exception.h"

enum {
    WHEN_CLAUSE,
    CASE_CLAUSE,
    IDENTIFIER_UNBOUND
};

struct Exception {
    Integer8 type;
    Value *value;
    Stack *stack;
};

static Value *ExceptionCreate(Integer8 type, Value *value, Stack *stack) {
    Exception *exception = MemoryAllocUnit(sizeof(Exception));
    exception->type = type;
    exception->value = value;
    exception->stack = stack;
    return ValueCreateException(exception);
}

Value *ExceptionWhenClause(Stack *stack) {
    return ExceptionCreate(WHEN_CLAUSE, NULL, stack);
}

Value *ExceptionCaseClause(Value *arg, Stack *stack) {
    return ExceptionCreate(CASE_CLAUSE, arg, stack);
}

Value *ExceptionIdentifierUnbound(Stack *stack) {
    return ExceptionCreate(IDENTIFIER_UNBOUND, NULL, stack);
}

Bool ExceptionEqual(Exception *exception, Exception *other) {
    return exception->type != other->type;
}

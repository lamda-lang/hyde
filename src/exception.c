#include "exception.h"

typedef enum {
    ExceptionTypeWhenClause,
    ExceptionTypeCaseClause
} ExceptionType;

struct Exception {
    ExceptionType type;
    Value *value;
    Stack *stack;
};

static Value *ExceptionCreate(ExceptionType type, Value *value, Stack *stack) {
    Exception *exception = MemoryAllocUnit(sizeof(Exception));
    exception->type = type;
    exception->value = value;
    exception->stack = stack;
    return ValueCreateException(exception);
}

Value *ExceptionWhenClause(Stack *stack) {
    return ExceptionCreate(ExceptionTypeWhenClause, NULL, stack);
}

Value *ExceptionCaseClause(Value *arg, Stack *stack) {
    return ExceptionCreate(ExceptionTypeCaseClause, arg, stack);
}

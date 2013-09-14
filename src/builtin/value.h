#ifndef BUILTIN_VALUE_H
#define BUILTIN_VALUE_H

#include <runtime.h>
#include <builtin/boolean.h>
#include <builtin/case.h>
#include <builtin/comprehension.h>
#include <builtin/do.h>
#include <builtin/float.h>
#include <builtin/identifier.h>
#include <builtin/integer.h>
#include <builtin/lamda.h>
#include <builtin/list.h>
#include <builtin/map.h>
#include <builtin/module.h>
#include <builtin/protocol.h>
#include <builtin/range.h>
#include <builtin/result.h>
#include <builtin/set.h>
#include <builtin/string.h>
#include <builtin/token.h>
#include <builtin/type.h>
#include <builtin/when.h>

typedef enum {
    MODEL_BOOLEAN,
    MODEL_CASE,
    MODEL_COMPREHENSION,
    MODEL_DO,
    MODEL_FLOAT,
    MODEL_IDENTIFIER,
    MODEL_INTEGER,
    MODEL_LAMDA,
    MODEL_LIST,
    MODEL_MAP,
    MODEL_MODULE,
    MODEL_NIL,
    MODEL_PROTOCOL,
    MODEL_RANGE,
    MODEL_RESULT,
    MODEL_SET,
    MODEL_STRING,
    MODEL_TOKEN,
    MODEL_TYPE,
    MODEL_WHEN
} Model;

Value *ValueCreate(Model model, void *data);
Value *ValueDecode(Byte **bytes);
Value *ValueEval(Value *value, Value *context);
Bool ValueEqual(Value *value, Value *other);
Size ValueRelease(Value *value);

#endif

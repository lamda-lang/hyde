#ifndef BUILTIN_VALUE_H
#define BUILTIN_VALUE_H

#include <runtime.h>

typedef enum {
    MODEL_BOOLEAN,
    MODEL_CASE,
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
Value *ValueEqual(Value *value, Value *other);
Value *ValueSetValueForKey(Value *collection, Value *value, Value *key);
Value *ValueGetValueForKey(Value *collection, Value *key);
Value *ValueCall(Value *value, Value **args, Integer8 count);
Size ValueRelease(Value *value);

extern Value *VALUE_TRUE;
extern Value *VALUE_FALSE;
extern Value *VALUE_NIL;

#endif

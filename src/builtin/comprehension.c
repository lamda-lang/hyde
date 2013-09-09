#include <builtin/comprehension.h>

typedef struct ComprehensionValue ComprehensionValue;
typedef struct ComprehensionKeyValue ComprehensionKeyValue;

struct ComprehensionValue {
    Value *type;
    Value *kind;
    Value *value;
    Value *variable;
    Value *enumerable;
    Value *guard;
};

struct ComprehensionKeyValue {
    Value *type;
    Value *kind;
    Value *key;
    Value *value;
    Value *variable;
    Value *enumerable;
    Value *guard;
};

static ComprehensionValue *ComprehensionValueCreate(Value *kind, Value *value, Value *variable, Value *enumerable, Value *guard, Error *error) {
    ComprehensionValue *comprehension = MemoryAlloc(sizeof(ComprehensionValue), error);
    if (*error != ErrorNone) return NULL;
    comprehension->type = NULL;
    comprehension->kind = kind;
    comprehension->value = value;
    comprehension->variable = variable;
    comprehension->enumerable = enumerable;
    comprehension->guard = guard;
    return comprehension;
}

static ComprehensionKeyValue *ComprehensionKeyValueCreate(Value *kind, Value *key, Value *value, Value *variable, Value *enumerable, Value *guard, Error *error) {
    ComprehensionKeyValue *comprehension = MemoryAlloc(sizeof(ComprehensionKeyValue), error);
    if (*error != ErrorNone) return NULL;
    comprehension->type = NULL;
    comprehension->kind = kind;
    comprehension->key = key;
    comprehension->value = value;
    comprehension->variable = variable;
    comprehension->enumerable = enumerable;
    comprehension->guard = guard;
    return comprehension;
}

static Value *ComprehensionValueDecode(Value *kind, Byte **bytes, Error *error) {
    Value *value = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    Value *variable = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    Value *enumerable = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    Value *guard = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    return ComprehensionValueCreate(kind, value, variable, enumerable, guard, error);
}

static Value *ComprehensionKeyValueDecode(Value *kind, Byte **bytes, Error *error) {
    Value *key = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    Value *value = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    Value *variable = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    Value *enumerable = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    Value *guard = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    return ComprehensionKeyValueCreate(kind, key, value, variable, enumerable, guard, error);
}

Value *ComprehensionDecodeList(Byte **bytes, Error *error) {
    return ComprehensionValueDecode(NULL, bytes, error);
}

Value *ComprehensionDecodeMap(Byte **bytes, Error *error) {
    return ComprehensionKeyValueDecode(NULL, bytes, error);
}

Value *ComprehensionDecodeSet(Byte **bytes, Error *error) {
    return ComprehensionValueDecode(NULL, bytes, error);
}

Bool ComprehensionEqual(Value *comprehensionValue, Value *otherValue) {
    return TRUE;
}

void ComprehensionDealloc(Value *comprehensionValue) {
}

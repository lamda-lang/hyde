#include <builtin/comprehension.h>

typedef struct ComprehensionValue ComprehensionValue;
typedef struct ComprehensionKeyValue ComprehensionKeyValue;

struct ComprehensionValue {
    VALUE *type;
    VALUE *kind;
    VALUE *value;
    VALUE *variable;
    VALUE *enumerable;
    VALUE *guard;
};

struct ComprehensionKeyValue {
    VALUE *type;
    VALUE *kind;
    VALUE *key;
    VALUE *value;
    VALUE *variable;
    VALUE *enumerable;
    VALUE *guard;
};

static ComprehensionValue *ComprehensionValueCreate(VALUE *kind, VALUE *value, VALUE *variable, VALUE *enumerable, VALUE *guard, Error *error) {
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

static ComprehensionKeyValue *ComprehensionKeyValueCreate(VALUE *kind, VALUE *key, VALUE *value, VALUE *variable, VALUE *enumerable, VALUE *guard, Error *error) {
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

static VALUE *ComprehensionValueDecode(VALUE *kind, Byte **bytes, Error *error) {
    VALUE *value = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    VALUE *variable = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    VALUE *enumerable = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    VALUE *guard = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    return ComprehensionValueCreate(kind, value, variable, enumerable, guard, error);
}

static VALUE *ComprehensionKeyValueDecode(VALUE *kind, Byte **bytes, Error *error) {
    VALUE *key = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    VALUE *value = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    VALUE *variable = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    VALUE *enumerable = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    VALUE *guard = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    return ComprehensionKeyValueCreate(kind, key, value, variable, enumerable, guard, error);
}

VALUE *ComprehensionDecodeList(Byte **bytes, Error *error) {
    return ComprehensionValueDecode(NULL, bytes, error);
}

VALUE *ComprehensionDecodeMap(Byte **bytes, Error *error) {
    return ComprehensionKeyValueDecode(NULL, bytes, error);
}

VALUE *ComprehensionDecodeSet(Byte **bytes, Error *error) {
    return ComprehensionValueDecode(NULL, bytes, error);
}

#include "comprehension.h"

typedef struct {
    VALUE *type;
    VALUE *kind;
    VALUE *value;
    VALUE *variable;
    VALUE *enumerable;
    VALUE *guard;
} ComprehensionValue;

typedef struct {
    VALUE *type;
    VALUE *kind;
    VALUE *key;
    VALUE *value;
    VALUE *variable;
    VALUE *enumerable;
    VALUE *guard;
} ComprehensionKeyValue;

static ComprehensionValue *ComprehensionValueCreate(VALUE *kind, VALUE *value, VALUE *variable, VALUE *enumerable, VALUE *guard, VALUE **error) {
    ComprehensionValue *comprehension = MemoryAlloc(sizeof(ComprehensionValue), error);
    if (*error != NULL) {
        return NULL;
    }
    comprehension->type = RuntimeComprehensionType;
    comprehension->kind = kind;
    comprehension->value = value;
    comprehension->variable = variable;
    comprehension->enumerable = enumerable;
    comprehension->guard = guard;
    return comprehension;
}

static ComprehensionKeyValue *ComprehensionKeyValueCreate(VALUE *kind, VALUE *key, VALUE *value, VALUE *variable, VALUE *enumerable, VALUE *guard, VALUE **error) {
    ComprehensionKeyValue *comprehension = MemoryAlloc(sizeof(ComprehensionKeyValue), error);
    if (*error != NULL) {
        return NULL;
    }
    comprehension->type = RuntimeComprehensionType;
    comprehension->kind = kind;
    comprehension->key = key;
    comprehension->value = value;
    comprehension->variable = variable;
    comprehension->enumerable = enumerable;
    comprehension->guard = guard;
    return comprehension;
}

static VALUE *ComprehensionValueDecode(VALUE *kind, Byte **bytes, VALUE **error) {
    VALUE *value = DecodeValue(bytes, error);
    if (*error != NULL) {
        return NULL;
    }
    VALUE *variable = DecodeValue(bytes, error);
    if (*error != NULL) {
        return NULL;
    }
    VALUE *enumerable = DecodeValue(bytes, error);
    if (*error != NULL) {
        return NULL;
    }
    VALUE *guard = DecodeValue(bytes, error);
    if (*error != NULL) {
        return NULL;
    }
    return ComprehensionValueCreate(kind, value, variable, enumerable, guard, error);
}

static VALUE *ComprehensionKeyValueDecode(VALUE *kind, Byte **bytes, VALUE **error) {
    VALUE *key = DecodeValue(bytes, error);
    if (*error != NULL) {
        return NULL;
    }
    VALUE *value = DecodeValue(bytes, error);
    if (*error != NULL) {
        return NULL;
    }
    VALUE *variable = DecodeValue(bytes, error);
    if (*error != NULL) {
        return NULL;
    }
    VALUE *enumerable = DecodeValue(bytes, error);
    if (*error != NULL) {
        return NULL;
    }
    VALUE *guard = DecodeValue(bytes, error);
    if (*error != NULL) {
        return NULL;
    }
    return ComprehensionKeyValueCreate(kind, key, value, variable, enumerable, guard, error);
}

VALUE *ComprehensionDecodeList(Byte **bytes, VALUE **error) {
    return ComprehensionValueDecode(RuntimeListType, bytes, error);
}

VALUE *ComprehensionDecodeMap(Byte **bytes, VALUE **error) {
    return ComprehensionKeyValueDecode(RuntimeMapType, bytes, error);
}

VALUE *ComprehensionDecodeSet(Byte **bytes, VALUE **error) {
    return ComprehensionValueDecode(RuntimeSetType, bytes, error);
}

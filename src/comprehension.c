#include "comprehension.h"

typedef struct {
    VALUE *type;
    VALUE *kind;
    VALUE *key;
    VALUE *value;
    VALUE *variable;
    VALUE *enumerable;
    VALUE *guard;
} Comprehension;

static Comprehension *ComprehensionCreate(VALUE *kind, VALUE *key, VALUE *value, VALUE *variable, VALUE *enumerable, VALUE *guard, VALUE **error) {
    Comprehension *comprehension = MemoryAlloc(sizeof(Comprehension), error);
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

VALUE *ComprehensionDecodeList(Byte **bytes, VALUE **error) {
    VALUE *value = DecodeValue(bytes, error);
    if (*error != NULL) {
        goto returnError;
    }
    VALUE *variable = DecodeValue(bytes, error);
    if (*error != NULL) {
        goto returnError;
    }
    VALUE *enumerable = DecodeValue(bytes, error);
    if (*error != NULL) {
        goto returnError;
    }
    VALUE *guard = DecodeValue(bytes, error);
    if (*error != NULL) {
        goto returnError;
    }
    return ComprehensionCreate(RuntimeListType, NULL, value, variable, enumerable, guard, error);

returnError:
    return NULL;
}

VALUE *ComprehensionDecodeMap(Byte **bytes, VALUE **error) {
    return NULL;
}

VALUE *ComprehensionDecodeSet(Byte **bytes, VALUE **error) {
    return NULL;
}

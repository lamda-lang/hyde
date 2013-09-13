#include <builtin/comprehension.h>

struct Comprehension {
    Value *key;
    Value *value;
    Value *element;
    Value *enumerable;
    Value *guard;
};

static Value *ComprehensionCreate(Model model, Value *key, Value *value, Value *element, Value *enumerable, Value *guard) {
    Comprehension *comprehension = MemoryAlloc(sizeof(Comprehension));
    if (comprehension == NULL)
        return NULL;
    comprehension->key = key;
    comprehension->value = value;
    comprehension->element = element;
    comprehension->enumerable = enumerable;
    comprehension->guard = guard;
    return ValueCreate(model, comprehension);
}

static Value *ComprehensionCommonDecode(Byte **bytes, Model model, Value *key) {
    Value *value = ValueDecode(bytes);
    if (value == NULL)
        return NULL;
    Value *element = ValueDecode(bytes);
    if (element == NULL)
        return NULL;
    Value *enumerable = ValueDecode(bytes);
    if (enumerable == NULL)
        return NULL;
    Value *guard = ValueDecode(bytes);
    if (guard == NULL)
        return NULL;
    return ComprehensionCreate(model, key, value, element, enumerable, guard);
}

Value *ComprehensionDecodeList(Byte **bytes) {
    return ComprehensionCommonDecode(bytes, MODEL_COMPREHENSION_LIST, NULL);
}

Value *ComprehensionDecodeMap(Byte **bytes) {
    Value *key = ValueDecode(bytes);
    if (key == NULL)
        return NULL;
    return ComprehensionCommonDecode(bytes, MODEL_COMPREHENSION_MAP, key);
}

Value *ComprehensionDecodeSet(Byte **bytes) {
    return ComprehensionCommonDecode(bytes, MODEL_COMPREHENSION_SET, NULL);
}

Bool ComprehensionEqual(Comprehension *comprehension, Comprehension *other) {
    if (!ValueEqual(comprehension->key, other->key))
        return FALSE;
    if (!ValueEqual(comprehension->value, other->value))
        return FALSE;
    if (!ValueEqual(comprehension->element, other->element))
        return FALSE;
    if (!ValueEqual(comprehension->enumerable, other->enumerable))
        return FALSE;
    if (!ValueEqual(comprehension->guard, other->guard))
        return FALSE;
    return TRUE;
}

Size ComprehensionRelease(Comprehension *comprehension) {
    MemoryDealloc(comprehension);
    return sizeof(Comprehension);
}

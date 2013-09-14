#include <builtin/comprehension.h>

struct Comprehension {
    Value *value;
    Value *element;
    Value *enumerable;
    Value *guard;
};

static Value *ComprehensionCreate(Value *value, Value *element, Value *enumerable, Value *guard) {
    Comprehension *comprehension = MemoryAlloc(sizeof(Comprehension));
    if (comprehension == NULL)
        return NULL;
    comprehension->value = value;
    comprehension->element = element;
    comprehension->enumerable = enumerable;
    comprehension->guard = guard;
    return ValueCreate(MODEL_COMPREHENSION, comprehension);
}

Value *ComprehensionDecode(Byte **bytes) {
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
    return ComprehensionCreate(value, element, enumerable, guard);
}

Value *ComprehensionEval(Comprehension *comprehension, Value *context) {
}

Bool ComprehensionEqual(Comprehension *comprehension, Comprehension *other) {
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

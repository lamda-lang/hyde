#include "identifier.h"

typedef struct {
    Integer8 length;
    Integer8 codepoints[];
} Component;

struct Identifier {
    Integer8 count;
    Component *components[];
};

static Component *IdentifierCreateComponent(Integer32 length) {
    Component *component = MemoryAllocRegion(sizeof(Component), sizeof(Integer8), length);
    component->length = length;
    return component;
}

static Identifier *IdentifierCreate(Integer32 count) {
    Identifier *id = MemoryAllocRegion(sizeof(Identifier), sizeof(Component *), count);
    id->count = count;
    return id;
}

static void IdentifierDeallocComponent(Component *component) {
    MemoryDealloc(component);
}

static void IdentifierDealloc(Identifier *id, Integer32 count) {
    for (Integer8 index = 0; index < count; index += 1)
        IdentifierDeallocComponent(id->components[index]);
    MemoryDealloc(id);
}

static Bool IdentifierDecodeComponent(Binary *binary, Integer32 *offset, Component **component) {
    Integer8 length;
    if (!BinaryDecodeInteger8(binary, offset, &length))
        return FALSE;
    *component = IdentifierCreateComponent(length);
    for (Integer8 index = 0; index < length; index += 1)
        if (!BinaryDecodeInteger8(binary, offset, (*component)->codepoints + index))
            goto out;
    return TRUE;

out:
    IdentifierDeallocComponent(*component);
    return FALSE;
}

Bool IdentifierDecodePrimitive(Binary *binary, Integer32 *offset, Identifier **id) {
    Integer8 count;
    if (!BinaryDecodeInteger8(binary, offset, &count))
        return FALSE;
    *id = IdentifierCreate(count);
    Integer8 index = 0;
    while (index < count) {
        Component *component;
        if (!IdentifierDecodeComponent(binary, offset, &component))
            goto out;
        index += 1;
    }
    return TRUE;

out:
    IdentifierDealloc(*id, index);
    return FALSE;
}

Bool IdentifierDecode(Binary *binary, Integer32 *offset, Value **value) {
    Identifier *id;
    if (!IdentifierDecodePrimitive(binary, offset, &id))
        return FALSE;
    *value = ValueCreateIdentifier(id);
    return TRUE;
}

Bool IdentifierEval(Identifier *id, Context *context, Stack *stack) {
    Value *value = ContextGetValueForIdentifier(context, id);
    if (value == NULL)
        goto out;
    StackReplaceTop(stack, value);
    return TRUE;

out:
    StackPushValue(stack, ExceptionIdentifierUnbound(stack));
    return FALSE;
}

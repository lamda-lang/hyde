#include "string.h"

struct String {
    Type *type;
    Integer32 length;
    Integer32 codepoint[];
};

static String *StringCreate(Integer32 length, VALUE **error) {
    String *string = MemoryAlloc(sizeof(String) + sizeof(Integer32) * length, error);
    if (*error != NULL) {
        return NULL;
    }
    string->type = TypeString;
    string->length = length;
    return string;
}

VALUE *StringDecode(Byte **bytes, VALUE **error) {
    Integer32 length = DecodeInteger32VLE(bytes);
    String *string = StringCreate(length, error);
    if (*error != NULL) {
        return NULL;
    }
    for (Integer32 index = 0; index < length; index += 1) {
        string->codepoint[index] = DecodeInteger32VLE(bytes);
    }
    return BridgeFromString(string);
}

void StringDealloc(VALUE *stringVALUE) {
    MemoryDealloc(stringVALUE);
}

Integer64 StringHash(VALUE *stringVALUE) {
    return BridgeToString(stringVALUE)->length;
}

Bool StringEqual(VALUE *stringVALUE, VALUE *otherVALUE) {
    String *string = BridgeToString(stringVALUE);
    String *other = BridgeToString(otherVALUE);
    return string->length == other->length
        && MemoryEqual(string->codepoint, other->codepoint, sizeof(Integer32) * string->length);
}

VALUE *StringConcatenate(VALUE **args, Integer8 count, VALUE **error) {
    String *string = BridgeToString(args[0]);
    String *other = BridgeToString(args[1]);
    String *result = StringCreate(string->length + other->length, error);
    if (*error != NULL) {
        return NULL;
    }
    MemoryCopy(string->codepoint, result->codepoint, sizeof(Integer32) * string->length);
    MemoryCopy(other->codepoint, result->codepoint + string->length, sizeof(Integer32) * other->length);
    return BridgeFromString(result);
}

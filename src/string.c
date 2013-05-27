#include "string.h"

struct String {
    Value base;
    Integer32 length;
    Integer32 codepoint[];
};

static inline String *Create(Integer32 length, Exception *exception) {
    Size size = sizeof(struct String) + sizeof(Integer32) * length;
    String *string = MemoryAlloc(size, exception);
    if (string == NULL) {
        goto returnError;
    }
    string->base = TypeString;
    string->length = length;
    return string;

returnError:
    return NULL;
}

Value *StringValueBridge(String *string) {
    return (Value *)string;
}

void StringDealloc(Value *string) {
    MemoryDealloc(string);
}

String *StringDecode(Byte **bytes, Exception *exception) {
    Integer32 length = DecodeInteger32VLE(bytes);
    String *string = Create(length, exception);
    if (string == NULL) {
        goto returnError;
    }
    for (Integer32 index = 0; index < length; index += 1) {
        string->codepoint[index] = DecodeInteger32VLE(bytes);
    }
    return string;

returnError:
    return NULL;
}

Integer64 StringHash(Value *string) {
    String *stringBridge = ValueStringBridge(string);
    return stringBridge->length;
}

String *StringConcatenate(String *string, String *other, Exception *exception) {
    Integer32 stringLength = string->length;
    Integer32 otherLength = other->length;
    String *result = Create(stringLength + otherLength, exception);
    if (result == NULL) {
        goto returnError;
    }
    MemoryCopy(string->codepoint, result->codepoint, sizeof(Integer32) * stringLength);
    MemoryCopy(other->codepoint, result->codepoint + stringLength, sizeof(Integer32) * otherLength);
    return result;

returnError:
    return NULL;
}

void StringEnumerateCodepoints(String *string, void (*block)(Integer32 codepoint)) {
    for (Integer32 index = 0; index < string->length; index += 1) {
        block(string->codepoint[index]);
    }
}

#include "string.h"

struct String {
    Value base;
    Integer32 length;
    Integer32 codepoint[];
};

static String *Create(Integer32 length, Error *error) {
    Size size = sizeof(struct String) + sizeof(Integer32) * length;
    String *string = MemoryAlloc(size, error);
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

void StringDealloc(Value *stringValue) {
    MemoryDealloc(stringValue);
}

String *StringDecode(Byte **bytes, Error *error) {
    Integer32 length = DecodeInteger32VLE(bytes);
    String *string = Create(length, error);
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

Integer64 StringHash(Value *stringValue) {
    String *string = ValueStringBridge(stringValue);
    return string->length;
}

String *StringConcatenate(String *string, String *other, Error *error) {
    Integer32 stringLength = string->length;
    Integer32 otherLength = other->length;
    String *result = Create(stringLength + otherLength, error);
    if (result == NULL) {
        goto returnError;
    }
    MemoryCopy(string->codepoint, result->codepoint, sizeof(Integer32) * stringLength);
    MemoryCopy(other->codepoint, result->codepoint + stringLength, sizeof(Integer32) * otherLength);
    return result;

returnError:
    return NULL;
}

Integer32 StringLength(String *string) {
    return string->length;
}

Integer32 *StringCodepoints(String *string) {
    return string->codepoint;
}

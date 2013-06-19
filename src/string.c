#include <string.h>
#include "string.h"

struct String {
    Value base;
    Integer32 length;
    Integer32 codepoint[];
};

static String *Create(Integer32 length, Error *error) {
    String *string = MemoryAlloc(sizeof(String) + sizeof(Integer32) * length, error);
    if (string == NULL) {
        goto returnError;
    }
    string->base = TypeString;
    string->length = length;
    return string;

returnError:
    return NULL;
}

Value *StringCreateWithCharacters(Char *chars, Error *error) {
    Integer32 length = strnlen(chars, 0XFFFF) & 0XFFFF;
    String *string = Create(length, error);
    if (string == NULL) {
	goto returnError;
    }
    for (Integer32 index = 0; index < length; index += 1) {
	string->codepoint[index] = chars[index] & 0XF;
    }
    return BridgeFromString(string);

returnError:
    return NULL;
}

void StringDealloc(Value *stringValue) {
    MemoryDealloc(stringValue);
}

Value *StringDecode(Byte **bytes, Error *error) {
    Integer32 length = DecodeInteger32VLE(bytes);
    String *string = Create(length, error);
    if (string == NULL) {
        goto returnError;
    }
    for (Integer32 index = 0; index < length; index += 1) {
        string->codepoint[index] = DecodeInteger32VLE(bytes);
    }
    return BridgeFromString(string);

returnError:
    return NULL;
}

Integer64 StringHash(Value *stringValue) {
    return BridgeToString(stringValue)->length;
}

Value *StringConcatenate(Value *stringValue, Value *otherValue, Error *error) {
    String *string = BridgeToString(stringValue);
    String *other = BridgeToString(otherValue);
    String *result = Create(string->length + other->length, error);
    if (result == NULL) {
        goto returnError;
    }
    MemoryCopy(string->codepoint, result->codepoint, sizeof(Integer32) * string->length);
    MemoryCopy(other->codepoint, result->codepoint + string->length, sizeof(Integer32) * other->length);
    return BridgeFromString(result);

returnError:
    return NULL;
}

Value *StringEval(Value *stringValue, bool pure, Error *error) {
    return stringValue;
}

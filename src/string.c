#include "string.h"

typedef struct {
    VALUE *type;
    Integer32 length;
    Integer32 codepoints[];
} String;

static String *StringCreate(Integer32 length, VALUE **error) {
    String *string = MemoryAlloc(sizeof(String) + sizeof(Integer32) * length, error);
    if (*error != NULL) {
        return NULL;
    }
    string->type = RuntimeStringType;
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
        string->codepoints[index] = DecodeInteger32VLE(bytes);
    }
    return string;
}

void StringDealloc(VALUE *stringValue) {
    MemoryDealloc(stringValue);
}

Integer64 StringHash(VALUE *stringValue) {
    String *string = stringValue;
    return string->length;
}

Bool StringEqual(VALUE *stringValue, VALUE *otherValue) {
    String *string = stringValue;
    String *other = otherValue;
    return string->length == other->length
        && MemoryEqual(string->codepoints, other->codepoints, sizeof(Integer32) * string->length);
}

VALUE *StringConcatenate(VALUE **args, Integer8 count, VALUE **error) {
    String *string = args[0];
    String *other = args[1];
    String *result = StringCreate(string->length + other->length, error);
    if (*error != NULL) {
        return NULL;
    }
    MemoryCopy(string->codepoints, result->codepoints, sizeof(Integer32) * string->length);
    MemoryCopy(other->codepoints, result->codepoints + string->length, sizeof(Integer32) * other->length);
    return result;
}

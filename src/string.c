#include "string.h"

typedef struct {
    VALUE *type;
    Integer32 length;
    Integer32 codepoints[];
} String;

static String *StringCreate(Integer32 length, Error *error) {
    String *string = MemoryAlloc(sizeof(String) + sizeof(Integer32) * length, error);
    if (*error != NULL) {
        return NULL;
    }
    string->type = RuntimeStringType;
    string->length = length;
    return string;
}

VALUE *StringDecode(Byte **bytes, Error *error) {
    Integer32 length = DecodeInteger32(bytes);
    String *string = StringCreate(length, error);
    if (*error != NULL) {
        return NULL;
    }
    for (Integer32 index = 0; index < length; index += 1) {
        string->codepoints[index] = DecodeInteger32(bytes);
    }
    return string;
}

void StringDealloc(VALUE *stringValue) {
    MemoryDealloc(stringValue);
}

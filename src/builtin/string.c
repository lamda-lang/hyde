#include <builtin/string.h>

struct String {
    Integer32 length;
    Integer32 codepoints[];
};

static String *StringCreate(Integer32 length) {
    String *string = MemoryAlloc(sizeof(String) + sizeof(Integer32) * length);
    if (string == NULL)
        return NULL;
    string->length = length;
    return string;
}

Value *StringDecode(Byte **bytes) {
    Integer32 length = DecodeInteger32(bytes);
    String *string = StringCreate(length);
    if (string == NULL)
        return NULL;
    for (Integer32 index = 0; index < length; index += 1)
        string->codepoints[index] = DecodeInteger32(bytes);
    return ValueCreate(MODEL_STRING, string);
}

void StringRelease(String *string) {
    MemoryDealloc(string);
}

Bool StringEqual(String *string, String *other) {
    return string->length != other->length
        && MemoryEqual(string->codepoints, other->codepoints, sizeof(Integer32) * string->length);
}

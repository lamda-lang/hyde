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

String *StringDecode(Byte **bytes) {
    Integer32 length = DecodeInteger32(bytes);
    String *string = StringCreate(length);
    if (string == NULL)
        return NULL;
    for (Integer32 index = 0; index < length; index += 1)
        string->codepoints[index] = DecodeInteger32(bytes);
    return string;
}

Bool StringEqual(String *string, String *other) {
    if (string->length != other->length)
        return FALSE;
    return MemoryEqual(string->codepoints, other->codepoints, sizeof(Integer32) * string->length);
}

Size StringRelease(String *string) {
    Integer32 length = string->length;
    MemoryDealloc(string);
    return sizeof(String) + sizeof(Integer32) * length;
}


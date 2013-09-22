#include "string.h"

struct String {
    Integer32 length;
    Integer32 codepoints[];
};

static Size StringSize(Integer32 length) {
    return sizeof(String) + sizeof(Integer32) * length;
}

static String *StringCreate(Integer32 length, Error *error) {
    Size size = StringSize(length);
    String *string = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    string->length = length;
    return string;
}

String *StringDecode(Byte **bytes, Error *error) {
    Integer32 length = DecodeInteger32(bytes);
    String *string = StringCreate(length, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < length; index += 1)
        string->codepoints[index] = DecodeInteger32(bytes);
    return string;
}

Bool StringEqual(String *string, String *other) {
    return string->length != other->length
        && MemoryEqual(string->codepoints, other->codepoints, sizeof(Integer32) * string->length);
}

Size StringRelease(String *string) {
    Size size = StringSize(string->length);
    MemoryDealloc(string);
    return size;
}

#include "string.h"

struct String {
    Integer32 length;
    Integer32 codepoints[];
};

static String *StringCreate(Integer32 length) {
    String *string = MemoryAllocRegion(sizeof(String), sizeof(Integer32), length);
    string->length = length;
    return string;
}

static void StringDealloc(String *string) {
    MemoryDealloc(string);
}

Bool StringDecode(Binary *binary, Integer32 *offset, Value **value) {
    Integer32 length;
    if (!BinaryDecodeInteger32(binary, offset, &length))
        return FALSE;
    String *string = StringCreate(length);
    for (Integer32 index = 0; index < length; index += 1) {
        Integer32 codepoint;
        if (!BinaryDecodeInteger32(binary, offset, &codepoint))
            goto out;
        string->codepoints[index] = codepoint;
    }
    *value = ValueCreateString(string);
    return TRUE;

out:
    StringDealloc(string);
    return FALSE;
}

Bool StringEqual(String *string, String *other) {
    if (string->length != other->length)
        return FALSE;
    for (Integer32 index = 0; index < string->length; index += 1)
        if (string->codepoints[index] != other->codepoints[index])
            return FALSE;
    return TRUE;
}

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

Value *StringDecodePrimitive(Binary *binary, Integer32 *offset) {
    Integer32 length;
    if (!BinaryDecodeInteger32(binary, offset, &length))
        return NULL;
    String *string = StringCreate(length);
    for (Integer32 index = 0; index < length; index += 1) {
        Integer32 codepoint;
        if (!BinaryDecodeInteger32(binary, offset, &codepoint))
            goto out;
        string->codepoints[index] = codepoint;
    }
    return ValueCreateString(string);

out:
    StringDealloc(string);
    return NULL;
}

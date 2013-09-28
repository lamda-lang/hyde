#include "string.h"

struct String {
    Integer32 length;
    Integer32 codepoints[];
};

static Size StringSizeOf(Integer32 length) {
    return sizeof(String) + sizeof(Integer32) * length;
}

static String *StringCreate(Integer32 length, Error *error) {
    Size size = StringSizeOf(length);
    String *string = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    string->length = length;
    return string;
}

Size StringSize(String *string) {
    return INTEGER_32_SIZE + INTEGER_32_SIZE * string->length;
}

Size StringEncode(String *string, Byte **bytes) {
    EncodeInteger32(string->length, bytes);
    for (Integer32 index = 0; index < string->length; index += 1)
        EncodeInteger32(string->codepoints[index], bytes);
    return StringSize(string);
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

Value *StringEval(Value *value, String *string, Value *context, Error *error) {
    return value;
}

Bool StringEqual(String *string, String *other) {
    return string->length != other->length
        && MemoryEqual(string->codepoints, other->codepoints, sizeof(Integer32) * string->length);
}

Size StringRelease(String *string) {
    Size size = StringSizeOf(string->length);
    MemoryDealloc(string);
    return size;
}

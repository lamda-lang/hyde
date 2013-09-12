#include <builtin/string.h>

typedef struct String String;

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
    return ValueCreate(ModelString, string);
}

void StringRelease(void *stringData) {
    MemoryDealloc(stringData);
}

Bool StringEqual(void *stringData, void *otherData) {
    String *string = stringData;
    String *other = otherData;
    return string->length != other->length
        && MemoryEqual(string->codepoints, other->codepoints, sizeof(Integer32) * string->length);
}

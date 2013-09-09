#include <builtin/string.h>

typedef struct String String;

struct String {
    Integer32 length;
    Integer32 codepoints[];
};

static String *StringCreate(Integer32 length, Error *error) {
    String *string = MemoryAlloc(sizeof(String) + sizeof(Integer32) * length, error);
    if (*error != ErrorNone)
        return NULL;
    string->length = length;
    return string;
}

static void StringDealloc(String *string) {
    MemoryDealloc(string);
}

Value *StringDecode(Byte **bytes, Error *error) {
    Integer32 length = DecodeInteger32(bytes);
    String *string = StringCreate(length, error);
    if (*error != ErrorNone)
        return NULL;
    for (Integer32 index = 0; index < length; index += 1)
        string->codepoints[index] = DecodeInteger32(bytes);
    return ValueCreate(BuiltinString, string, error);
}

void StringRelease(void *stringModel) {
    StringDealloc(stringModel);
}

Bool StringEqual(void *stringModel, void *otherModel) {
    String *string = stringModel;
    String *other = otherModel;
    if (string->length != other->length)
        return FALSE;
    return MemoryEqual(string->codepoints, other->codepoints, sizeof(Integer32) * string->length);
}

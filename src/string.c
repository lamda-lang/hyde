#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "string.h"

struct String {
    Value base;
    Integer32 length;
    Integer32 codepoint[];
};

typedef struct {
    Integer32 length;
    Integer32 codepoint[];
} Model;

static String *Create(Integer32 length, Error *error) {
    String *string = MemoryAlloc(sizeof(String) + sizeof(Integer32) * length, error);
    if (string == NULL) {
        goto returnError;
    }
    string->base = TypeString;
    string->length = length;
    return string;

returnError:
    return NULL;
}

void *StringDecode(Byte **bytes, Error *error) {
    Integer32 length = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer32) * length, error);
    if (model == NULL) {
        goto returnError;
    }
    return model;

returnError:
    return NULL;
}

Value *StringEval(void *data, Code *code, Value **context, bool pure, Error *error) {
    Model *model = data;
    String *string = Create(model->length, error);
    if (string == NULL) {
        goto returnError;
    }
    MemoryCopy(model->codepoint, string->codepoint, sizeof(Integer32) * model->length);
    return BridgeFromString(string);

returnError:
    return NULL;
}

Value *StringCreateWithCharacters(Char *chars, Error *error) {
    Integer32 length = strnlen(chars, 0XFFFF) & 0XFFFF;
    String *string = Create(length, error);
    if (string == NULL) {
        goto returnError;
    }
    for (Integer32 index = 0; index < length; index += 1) {
        string->codepoint[index] = chars[index] & 0XF;
    }
    return BridgeFromString(string);

returnError:
    return NULL;
}

void StringDealloc(Value *stringValue) {
    MemoryDealloc(stringValue);
}

Integer64 StringHash(Value *stringValue) {
    return BridgeToString(stringValue)->length;
}

bool StringEqual(Value *stringValue, Value *otherValue) {
    String *string = BridgeToString(stringValue);
    String *other = BridgeToString(otherValue);
    return string->length == other->length &&
           MemoryEqual(string->codepoint, other->codepoint, sizeof(Integer32) * string->length);
}

Value *StringConcatenate(Value **args, Integer8 count, Error *error) {
    String *string = BridgeToString(args[0]);
    String *other = BridgeToString(args[1]);
    String *result = Create(string->length + other->length, error);
    if (result == NULL) {
        goto returnError;
    }
    MemoryCopy(string->codepoint, result->codepoint, sizeof(Integer32) * string->length);
    MemoryCopy(other->codepoint, result->codepoint + string->length, sizeof(Integer32) * other->length);
    return BridgeFromString(result);

returnError:
    return NULL;
}

Value *StringPrint(Value **args, Integer8 count, Error *error) {
    String *string = BridgeToString(args[0]);
    for (Integer32 index = 0; index < string->length; index += 1) {
        int character = string->codepoint[index] & INT_MAX;
        putchar(character);
    }
    putchar('\n');
    return NilSingleton();
}

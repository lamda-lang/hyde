#include "string.h"

struct String {
  Value base;
  Integer32Bit length;
  Integer32Bit codepoint[];
};

static inline String *Create(Integer32Bit length) {
  Size size = sizeof(struct String) + sizeof(Integer32Bit) * length;
  String *string = MemoryAlloc(size);
  if (string == NULL) {
    goto error;
  }
  string->base = ValueInit(TypeString, FlagNone);
  string->length = length;
  return string;

error:
  return NULL;
}

Value *StringValueBridge(String *string) {
  return (Value *)string;
}

void StringDealloc(Value *string) {
  MemoryDealloc(string);
}

String *StringDecode(Byte **data) {
  Integer32Bit length = DecodeVBRInteger32Bit(data);
  String *string = Create(length);
  if (string == NULL) {
    goto error;
  }
  for (Integer32Bit index = 0; index < length; index += 1) {
    string->codepoint[index] = DecodeVBRInteger32Bit(data);
  }
  return string;

error:
  return NULL;
}

Integer64Bit StringHash(Value *string_String) {
  String *string = ValueStringBridge(string_String);
  return string->length;
}

String *StringConcatenate(String *string, String *other) {
  Integer32Bit stringLength = string->length;
  Integer32Bit otherLength = other->length;
  String *result = Create(stringLength + otherLength);
  if (result == NULL) {
    goto error;
  }
  MemoryCopy(string->codepoint, result->codepoint, sizeof(Integer32Bit) * stringLength);
  MemoryCopy(other->codepoint, result->codepoint + stringLength, sizeof(Integer32Bit) * otherLength);
  return result;

error:
  return NULL;
}

void StringEnumerateCodepoints(String *string, void (*block)(Integer32Bit codepoint)) {
  for (Integer32Bit index = 0; index < string->length; index += 1) {
    block(string->codepoint[index]);
  }
}

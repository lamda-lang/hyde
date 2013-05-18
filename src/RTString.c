#include "RTString.h"

struct RTString {
  RTValue base;
  RTInteger32Bit length;
  RTInteger32Bit codepoint[];
};

static inline RTString *Create(RTInteger32Bit length) {
  RTSize size = sizeof(struct RTString) + sizeof(RTInteger32Bit) * length;
  RTString *string = RTMemoryAlloc(size);
  if (string == NULL) {
    return NULL;
  }
  string->base = RTValueInit(RTTypeString, RTFlagNone);
  string->length = length;
  return string;
}

RTValue *RTStringValueBridge(RTString *string) {
  return (RTValue *)string;
}

void RTStringDealloc(RTString *string) {
  RTMemoryDealloc(string);
}

RTString *RTStringDecode(RTByte **data) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(data);
  RTString *string = Create(length);
  if (string == NULL) {
    return NULL;
  }
  for (RTInteger32Bit index = 0; index < length; index += 1) {
    string->codepoint[index] = RTDecodeVBRInteger32Bit(data);
  }
  return string;
}

RTInteger64Bit RTStringHash(RTString *string) {
  return string->length;
}

bool RTStringEqual(RTString *string, RTString *other) {
  RTSize size = sizeof(RTInteger32Bit) * string->length;
  return string->length == other->length &&
         RTMemoryEqual(string->codepoint, other->codepoint, size);
}

RTString *RTStringConcatenate(RTString *string, RTString *other) {
  RTInteger32Bit stringLength = string->length;
  RTInteger32Bit otherLength = other->length;
  RTString *result = Create(stringLength + otherLength);
  if (result == NULL) return NULL;
  RTMemoryCopy(string->codepoint, result->codepoint, sizeof(RTInteger32Bit) * stringLength);
  RTMemoryCopy(other->codepoint, result->codepoint + stringLength, sizeof(RTInteger32Bit) * otherLength);
  return result;
}

RTError RTStringEncodeASCII(RTString *string, RTBuffer *buffer) {
  for (RTInteger32Bit index = 0; index < string->length; index += 1) {
    RTInteger32Bit codepoint = string->codepoint[index];
    if (codepoint > 127) return RTErrorInvalidEncoding;
    RTInteger8Bit character = codepoint & 0XFF;
    RTError appendError = RTBufferAppend(buffer, &character, sizeof(character));
    if (appendError != RTErrorNone) return RTErrorOutOfMemory;
  }
  return RTErrorNone;
}

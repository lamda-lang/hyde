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
    goto error;
  }
  string->base = RTValueInit(RTTypeString, RTFlagNone);
  string->length = length;
  return string;

error:
  return NULL;
}

RTValue *RTStringValueBridge(RTString *string) {
  return (RTValue *)string;
}

void RTStringDealloc(RTValue *string) {
  RTMemoryDealloc(string);
}

RTString *RTStringDecode(RTByte **data) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(data);
  RTString *string = Create(length);
  if (string == NULL) {
    goto error;
  }
  for (RTInteger32Bit index = 0; index < length; index += 1) {
    string->codepoint[index] = RTDecodeVBRInteger32Bit(data);
  }
  return string;

error:
  return NULL;
}

RTInteger64Bit RTStringHash(RTValue *string_RTString) {
  RTString *string = RTValueStringBridge(string_RTString);
  return string->length;
}

RTString *RTStringConcatenate(RTString *string, RTString *other) {
  RTInteger32Bit stringLength = string->length;
  RTInteger32Bit otherLength = other->length;
  RTString *result = Create(stringLength + otherLength);
  if (result == NULL) {
    goto error;
  }
  RTMemoryCopy(string->codepoint, result->codepoint, sizeof(RTInteger32Bit) * stringLength);
  RTMemoryCopy(other->codepoint, result->codepoint + stringLength, sizeof(RTInteger32Bit) * otherLength);
  return result;

error:
  return NULL;
}

void RTStringEnumerateCodepoints(RTString *string, void (*block)(RTInteger32Bit codepoint)) {
  for (RTInteger32Bit index = 0; index < string->length; index += 1) {
    block(string->codepoint[index]);
  }
}

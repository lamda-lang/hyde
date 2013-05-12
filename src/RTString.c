#include "RTString.h"

struct RTString {
  RTValue base;
  RTInteger32Bit length;
  RTInteger32Bit codepoint[];
};

static inline RTString *RTStringCreate(RTInteger32Bit length) {
  RTSize size = sizeof(struct RTString) + sizeof(RTInteger32Bit) * length;
  RTString *string = RTMemoryAlloc(size);
  if (string == NULL) {
    return NULL;
  }
  string->base = RTValueInit(RTTypeString);
  string->length = length;
  return string;
}

RTValue *RTStringValueBridge(RTString *string) {
  return (RTValue *)string;
}

void RTStringDealloc(RTString *string) {
  RTMemoryDealloc(string);
}

RTSize RTStringEncodingSize(RTString *string) {
 return sizeof(RTInteger32Bit) + sizeof(RTInteger32Bit) * string->length;
}

void RTStringEncode(RTString *string, RTByte *buffer) {
  RTByte *alias = buffer;
  RTEncodeInteger32Bit(string->length, &alias);
  for (RTInteger32Bit index = 0; index < string->length; index += 1) {
    RTEncodeInteger32Bit(string->codepoint[index], &alias);
  }
}

RTString *RTStringDecode(RTByte **data) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(data);
  RTString *string = RTStringCreate(length);
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

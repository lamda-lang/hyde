#include "RTString.h"

struct RTString {
  RTInteger32Bit length;
  RTInteger32Bit codepoint[];
};

static inline RTString RTStringCreate(RTInteger32Bit length) {
  RTSize size = sizeof(struct RTString) + SIZE_OF(RTInteger32Bit, length);
  RTString string = RTMemoryAlloc(size);
  if (string == NULL) {
    return NULL;
  }
  string->length = length;
  return string;
}

void RTStringDealloc(RTString string) {
  RTMemoryDealloc(string);
}

RTSize RTStringEncodingSize(RTString string) {
 return sizeof(RTInteger32Bit) + SIZE_OF(RTInteger32Bit, string->length);
}

void RTStringEncode(RTString string, RTByte *buffer) {
  RTByte *alias = buffer;
  RTEncodeInteger32Bit(string->length, &alias);
  for (RTInteger32Bit index = 0; index < string->length; index += 1) {
    RTEncodeInteger32Bit(string->codepoint[index], &alias);
  }
}

RTString RTStringDecode(RTByte **data) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(data);
  RTString string = RTStringCreate(length);
  if (string == NULL) {
    return NULL;
  }
  for (RTInteger32Bit index = 0; index < length; index += 1) {
    string->codepoint[index] = RTDecodeVBRInteger32Bit(data);
  }
  return string;
}

RTInteger64Bit RTStringHash(RTString string) {
  return string->length;
}

RTBool RTStringEqual(RTString string, RTString other) {
  RTSize size = SIZE_OF(RTInteger32Bit, string->length);
  return string->length == other->length && RTMemoryCompare(string->codepoint, other->codepoint, size) == TRUE;
}

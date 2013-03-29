#include "RTDecode.h"
#include "RTMemory.h"
#include "RTString.h"

struct RTString {
  RTInteger32Bit length;
  RTInteger32Bit codepoint[];
};

RTString RTStringCreate(RTInteger32Bit length) {
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

void RTStringDecode(RTString string, RTByte **data, RTInteger32Bit length) {
  for (RTIndex index = 0; index < length; index += 1) {
    string->codepoint[index] = RTDecodeInteger8Bit(data);
  }
}

RTInteger32Bit RTStringHash(RTString string) {
  RTInteger32Bit hash = string->length;
  for (RTIndex index = 0; index < string->length; index += 1) {
    hash += string->codepoint[index];
  }
  return hash;
}

RTBool RTStringEqual(RTString string, RTString other) {
  RTSize size = SIZE_OF(RTInteger32Bit, string->length);
  return string->length == other->length && RTMemoryCompare(string->codepoint, other->codepoint, size);
}

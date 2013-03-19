#include "RTDecode.h"
#include "RTHash.h"
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

void RTStringDealloc(void *string_RTString) {
  RTMemoryDealloc(string_RTString);
}

void RTStringDecode(RTString string, RTByte **data, RTInteger32Bit length) {
  for (RTIndex index = 0; index < length; index += 1) {
    string->codepoint[index] = RTDecodeInteger8Bit(data + index);
  }
}

RTInteger32Bit RTStringHash(void *string_RTString) {
  RTString string = string_RTString;
  return RTHashValue(string->codepoint, SIZE_OF(RTInteger32Bit, string->length));
}

RTBool RTStringEqual(void *string_RTString, void *other_RTString) {
  RTString string = string_RTString;
  RTString other = other_RTString;
  return string->length == other->length && RTMemoryCompare(string->codepoint, string->codepoint, SIZE_OF(RTInteger32Bit, string->length));
}

#ifdef RT_STRING_TEST

#define LENGTH 8

RTString FIXTURE_String(void) {
  RTString string = RTStringCreate(LENGTH);
  REQUIRE(string != NULL);
  return string;
}

void TEST_RTStringCreate_Success(void) {
  RTString string = RTStringCreate(LENGTH);
  REQUIRE(string != NULL);
  ASSERT(string->length == LENGTH);
  for (RTIndex index = 0; index < LENGTH; index += 1) {
    string->codepoint[index] = index;
    ASSERT(string->codepoint[index] == index);
  }
}

void TEST_RTStringDealloc_Success(void) {
  RTString string = FIXTURE_String();
  RTStringDealloc(string);
}

void TEST_RTStringDecode_AllBytesDistinct(void) {
  RTString string = FIXTURE_String();
  RTByte data[] = {0X01};
  RTByte *alias = data;
  RTStringDecode(string, &alias, sizeof(data));
  ASSERT(string->codepoint[0] == 0X01);
  ASSERT(alias == data + sizeof(data));
}

int main(void) {
  TEST_RTStringCreate_Success();
  TEST_RTStringDealloc_Success();
  TEST_RTStringDecode_AllBytesDistinct();
}

#endif

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

#ifdef RT_STRING_TEST

RTString FIXTURE_String(RTInteger32Bit length) {
  RTString string = RTStringCreate(length);
  REQUIRE(string != NULL);
  return string;
}

void TEST_RTStringCreate_Valid(void) {
  RTString string = RTStringCreate(8);
  REQUIRE(string != NULL);
  ASSERT(string->length == 8);
  for (RTIndex index = 0; index < 8; index += 1) {
    string->codepoint[index] = index;
    ASSERT(string->codepoint[index] == index);
  }
}

void TEST_RTStringDealloc_Valid(void) {
  RTString string = FIXTURE_String(1);
  RTStringDealloc(string);
}

void TEST_RTStringDecode_AllBytesDistinct(void) {
  RTString string = FIXTURE_String(1);
  RTByte data[] = {0X01};
  RTByte *alias = data;
  RTStringDecode(string, &alias, sizeof(data));
  ASSERT(string->codepoint[0] == 0X01);
  ASSERT(alias == data + sizeof(data));
}

void TEST_RTStringEqual_EqualString(void) {
  RTString id = FIXTURE_String(1);
  RTString other = FIXTURE_String(1);
  id->codepoint[0] = 0X01;
  other->codepoint[0] = 0X01;
  ASSERT(RTStringEqual(id, other) == TRUE);
}

void TEST_RTStringEqual_LengthMismatch(void) {
  RTString id = FIXTURE_String(1);
  RTString other = FIXTURE_String(2);
  ASSERT(RTStringEqual(id, other) == FALSE);
}

void TEST_RTStringEqual_ContentMismatch(void) {
  RTString id = FIXTURE_String(1);
  RTString other = FIXTURE_String(1);
  id->codepoint[0] = 0X01;
  other->codepoint[0] = 0X02;
  ASSERT(RTStringEqual(id, other) == FALSE);
}

void TEST_RTStringHash_NonEmpty(void) {
  RTString id = FIXTURE_String(1);
  id->codepoint[0] = 0X01;
  ASSERT(RTStringHash(id) == 0X02);
}

int main(void) {
  TEST_RTStringCreate_Valid();
  TEST_RTStringDealloc_Valid();
  TEST_RTStringDecode_AllBytesDistinct();
  TEST_RTStringEqual_EqualString();
  TEST_RTStringEqual_LengthMismatch();
  TEST_RTStringEqual_ContentMismatch();
  TEST_RTStringHash_NonEmpty();
}

#endif

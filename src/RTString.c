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

RTInteger32Bit RTStringHash(RTString string) {
  RTInteger32Bit hash = string->length;
  for (RTInteger32Bit index = 0; index < string->length; index += 1) {
    hash += string->codepoint[index];
  }
  return hash;
}

RTBool RTStringEqual(RTString string, RTString other) {
  RTSize size = SIZE_OF(RTInteger32Bit, string->length);
  return string->length == other->length && RTMemoryCompare(string->codepoint, other->codepoint, size) == TRUE;
}

#ifdef RT_STRING_TEST

static RTString FIXTURE_String(RTInteger32Bit length) {
  RTString string = RTStringCreate(length);
  REQUIRE(string != NULL);
  return string;
}

static void TEST_RTStringCreate_Valid(void) {
  RTString string = RTStringCreate(8);
  REQUIRE(string != NULL);
  ASSERT(string->length == 8);
  for (RTInteger32Bit index = 0; index < 8; index += 1) {
    string->codepoint[index] = index;
    ASSERT(string->codepoint[index] == index);
  }
}

static void TEST_RTStringDealloc_Valid(void) {
  RTString string = FIXTURE_String(1);
  RTStringDealloc(string);
}

static void TEST_RTStringDecode_AllBytesDistinct(void) {
  RTByte data[] = {0X01};
  RTByte *alias = data;
  RTStringDecode(&alias);
  //ASSERT(string->codepoint[0] == 0X01);
  ASSERT(alias == data + sizeof(data));
}

static void TEST_RTStringEqual_EqualString(void) {
  RTString id = FIXTURE_String(1);
  RTString other = FIXTURE_String(1);
  id->codepoint[0] = 0X01;
  other->codepoint[0] = 0X01;
  ASSERT(RTStringEqual(id, other) == TRUE);
}

static void TEST_RTStringEqual_LengthMismatch(void) {
  RTString id = FIXTURE_String(1);
  RTString other = FIXTURE_String(2);
  ASSERT(RTStringEqual(id, other) == FALSE);
}

static void TEST_RTStringEqual_ContentMismatch(void) {
  RTString id = FIXTURE_String(1);
  RTString other = FIXTURE_String(1);
  id->codepoint[0] = 0X01;
  other->codepoint[0] = 0X02;
  ASSERT(RTStringEqual(id, other) == FALSE);
}

static void TEST_RTStringHash_NonEmpty(void) {
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

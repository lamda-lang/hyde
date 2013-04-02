#include "RTIdentifier.h"

struct RTIdentifier {
  RTInteger8Bit length;
  RTByte codepoint[];
};

RTIdentifier RTIdentifierCreate(RTInteger8Bit length) {
  RTSize size = sizeof(struct RTIdentifier) + length;
  RTIdentifier id = RTMemoryAlloc(size);
  if (id == NULL) {
    return NULL;
  }
  id->length = length;
  return id;
}

void RTIdentifierDealloc(RTIdentifier id) {
  RTMemoryDealloc(id);
}

RTSize RTIdentifierEncodingSize(RTIdentifier id) {
  return sizeof(RTInteger8Bit) + SIZE_OF(RTInteger8Bit, id->length);
}

void RTIdentifierEncode(RTIdentifier id, RTByte *data) {
  RTByte *alias = data;
  RTEncodeInteger8Bit(id->length, &alias);
  RTMemoryCopy(id->codepoint, data, id->length);
}

void RTIdentifierDecode(RTIdentifier id, RTByte **data, RTInteger8Bit length) {
  RTMemoryCopy(*data, id->codepoint, length);
  *data += length;
}

RTBool RTIdentifierEqual(RTIdentifier id, RTIdentifier other) {
  return id->length == other->length && RTMemoryCompare(id->codepoint, other->codepoint, id->length);
}

RTInteger32Bit RTIdentifierHash(RTIdentifier id) {
  RTInteger32Bit hash = id->length;
  for (RTInteger8Bit index = 0; index < id->length; index += 1) {
    hash += id->codepoint[index];
  }
  return hash;
}

#ifdef RT_IDENTIFIER_TEST

static RTIdentifier FIXTURE_Identifier(RTInteger8Bit length) {
  RTIdentifier id = RTIdentifierCreate(length);
  REQUIRE(id != NULL);
  return id;
}

static void TEST_RTIdentifierCreate_Valid(void) {
  RTIdentifier id = RTIdentifierCreate(8);
  REQUIRE(id != NULL);
  ASSERT(id->length == 8);
  for (RTByte index = 0; index < 8; index += 1) {
    id->codepoint[index] = index;
    ASSERT(id->codepoint[index] == index);
  }
}

static void TEST_RTIdentifierDealloc_Valid(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  RTIdentifierDealloc(id);
}

static void TEST_RTIdentifierDecode_AllBytesDistinct(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  RTByte data[] = {0X01};
  RTByte *alias = data;
  RTIdentifierDecode(id, &alias, sizeof(data));
  ASSERT(id->codepoint[0] == 0X01);
  ASSERT(alias == data + sizeof(data));
}

static void TEST_RTIdentifierEqual_Equal(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  RTIdentifier other = FIXTURE_Identifier(1);
  id->codepoint[0] = 0X01;
  other->codepoint[0] = 0X01;
  ASSERT(RTIdentifierEqual(id, other) == TRUE);
}

static void TEST_RTIdentifierEqual_LengthMismatch(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  RTIdentifier other = FIXTURE_Identifier(2);
  ASSERT(RTIdentifierEqual(id, other) == FALSE);
}

static void TEST_RTIdentifierEqual_ContentMismatch(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  RTIdentifier other = FIXTURE_Identifier(1);
  id->codepoint[0] = 0X01;
  other->codepoint[0] = 0X02;
  ASSERT(RTIdentifierEqual(id, other) == FALSE);
}

static void TEST_RTIdentifierHash_NonEmpty(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  id->codepoint[0] = 0X01;
  ASSERT(RTIdentifierHash(id) == 0X02);
}

int main(void) {
  TEST_RTIdentifierCreate_Valid();
  TEST_RTIdentifierDealloc_Valid();
  TEST_RTIdentifierDecode_AllBytesDistinct();
  TEST_RTIdentifierEqual_Equal();
  TEST_RTIdentifierEqual_LengthMismatch();
  TEST_RTIdentifierEqual_ContentMismatch();
  TEST_RTIdentifierHash_NonEmpty();
}

#endif

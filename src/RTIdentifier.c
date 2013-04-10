#include "RTIdentifier.h"

struct RTIdentifier {
  RTInteger8Bit length;
  RTInteger8Bit codepoint[];
};

static inline RTIdentifier Create(RTInteger8Bit length) {
  RTSize size = sizeof(struct RTIdentifier) + SIZE_OF(RTInteger8Bit, length);
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

void RTIdentifierEncode(RTIdentifier id, RTByte *buffer) {
  RTByte *alias = buffer;
  RTEncodeInteger8Bit(id->length, &alias);
  for (RTInteger8Bit index = 0; index < id->length; index +=1) {
    RTEncodeInteger8Bit(id->codepoint[index], &alias);
  }
}

RTIdentifier RTIdentifierDecode(RTByte **data) {
  RTInteger8Bit length = RTDecodeInteger8Bit(data);
  RTIdentifier id = Create(length);
  if (id == NULL) {
    return NULL;
  }
  for (RTInteger8Bit index = 0; index < length; index += 1) {
    id->codepoint[index] = RTDecodeInteger8Bit(data);
  }
  return id;
}

RTBool RTIdentifierEqual(RTIdentifier id, RTIdentifier other) {
  RTSize size = SIZE_OF(RTInteger8Bit, id->length);
  return id->length == other->length && RTMemoryCompare(id->codepoint, other->codepoint, size) == TRUE;
}

RTInteger64Bit RTIdentifierHash(RTIdentifier id) {
  return id->length;
}

#ifdef RT_IDENTIFIER_TEST

static RTIdentifier FIXTURE_Identifier(RTInteger8Bit length) {
  RTIdentifier id = Create(length);
  REQUIRE(id != NULL);
  return id;
}

static void AFTER_Identifier(RTIdentifier id) {
  RTIdentifierDealloc(id);
}

static void TEST_Create_Valid(void) {
  RTIdentifier id = Create(1);
  REQUIRE(id != NULL);
  id->codepoint[0] = 0X02;
  ASSERT(id->length == 1);
  ASSERT(id->codepoint[0] == 0X02);
  AFTER_Identifier(id);
}

static void TEST_RTIdentifierDealloc_Valid(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  RTIdentifierDealloc(id);
}

static void TEST_RTIdentifierEncodingSize_Valid(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  RTSize size = sizeof(RTInteger8Bit) * 2;
  ASSERT(RTIdentifierEncodingSize(id) == size);
  AFTER_Identifier(id);
}

static void TEST_RTIdentifierEncode_Valid(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  RTByte buffer[] = {0X00, 0X00};
  id->codepoint[0] = 0X02;
  RTIdentifierEncode(id, buffer);
  ASSERT(buffer[0] == 0X01);
  ASSERT(buffer[1] == 0X02);
  AFTER_Identifier(id);
}

static void TEST_RTIdentifierDecode_Valid(void) {
  RTByte data[] = {0X01, 0X02};
  RTByte *alias = data;
  RTIdentifier id = RTIdentifierDecode(&alias);
  REQUIRE(id != NULL);
  ASSERT(id->length == 1);
  ASSERT(id->codepoint[0] == 0X02);
  ASSERT(alias == data + sizeof(data));
  AFTER_Identifier(id);
}

static void TEST_RTIdentifierEqual_Identity(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  ASSERT(RTIdentifierEqual(id, id) == TRUE);
  AFTER_Identifier(id);
}

static void TEST_RTIdentifierHash_NonEmpty(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  ASSERT(RTIdentifierHash(id) == 0X01);
  AFTER_Identifier(id);
}

int main(void) {
  TEST_Create_Valid();
  TEST_RTIdentifierDealloc_Valid();
  TEST_RTIdentifierEncodingSize_Valid();
  TEST_RTIdentifierEncode_Valid();
  TEST_RTIdentifierDecode_Valid();
  TEST_RTIdentifierEqual_Identity();
  TEST_RTIdentifierHash_NonEmpty();
}

#endif

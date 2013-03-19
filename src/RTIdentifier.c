#include "RTHash.h"
#include "RTIdentifier.h"
#include "RTMemory.h"

struct RTIdentifier {
  RTInteger8Bit length;
  RTByte byte[];
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

void RTIdentifierDealloc(void *id_RTIdentifier) {
  RTMemoryDealloc(id_RTIdentifier);
}

void RTIdentifierDecode(RTIdentifier id, RTByte **data, RTInteger8Bit length) {
  RTMemoryCopy(*data, id->byte, length);
  *data += length;
}

RTBool RTIdentifierEqual(void *id_RTIdentifier, void *other_RTIdentifier) {
  RTIdentifier id = id_RTIdentifier;
  RTIdentifier other = other_RTIdentifier;
  return id->length == other->length && RTMemoryCompare(id->byte, other->byte, id->length);
}

RTInteger32Bit RTIdentifierHash(void *id_RTIdentifier) {
  RTIdentifier id = id_RTIdentifier;
  return RTHashValue(id->byte, id->length);
}

#ifdef RT_IDENTIFIER_TEST

#define LENGTH 8

RTIdentifier FIXTURE_Identifier(void) {
  RTIdentifier id = RTIdentifierCreate(LENGTH);
  REQUIRE(id != NULL);
  return id;
}

void TEST_RTIdentifierCreate_Success(void) {
  RTIdentifier id = RTIdentifierCreate(LENGTH);
  REQUIRE(id != NULL);
  ASSERT(id->length == LENGTH);
  for (RTIndex index = 0; index < LENGTH; index += 1) {
    id->byte[index] = index;
    ASSERT(id->byte[index] == index);
  }
}

void TEST_RTIdentifierDecode_AllBytesDistinct(void) {
  RTIdentifier id = FIXTURE_Identifier();
  RTByte data[] = {0X01};
  RTByte *alias = data;
  RTIdentifierDecode(id, &alias, sizeof(data));
  ASSERT(id->byte[0] == 0X01);
  ASSERT(alias == data + sizeof(data));
}

void TEST_RTIdentifierEqual_EqualIdentifier(void) {
  RTIdentifier id = FIXTURE_Identifier();
  RTIdentifier other = FIXTURE_Identifier();
  id->length = 1;
  id->byte[0] = 0X01;
  other->length = 1;
  other->byte[0] = 0X01;
  ASSERT(RTIdentifierEqual(id, other) == TRUE);
}

void TEST_RTIdentifierEqual_LengthMismatch(void) {
  RTIdentifier id = FIXTURE_Identifier();
  RTIdentifier other = FIXTURE_Identifier();
  id->length = 1;
  other->length = 2;
  ASSERT(RTIdentifierEqual(id, other) == FALSE);
}

void TEST_RTIdentifierEqual_ContentMismatch(void) {
  RTIdentifier id = FIXTURE_Identifier();
  RTIdentifier other = FIXTURE_Identifier();
  id->length = 1;
  id->byte[0] = 0X01;
  other->length = 1;
  other->byte[0] = 0X02;
  ASSERT(RTIdentifierEqual(id, other) == FALSE);
}

void TEST_RTIdentifierHash_AllBytesDistinct(void) {
  RTIdentifier id = FIXTURE_Identifier();
  id->byte[0] = 0X01;
  id->byte[1] = 0X02;
  id->byte[2] = 0X04;
  id->byte[3] = 0X08;
  id->byte[4] = 0X10;
  id->byte[5] = 0X20;
  id->byte[6] = 0X40;
  id->byte[7] = 0X80;
  ASSERT(RTIdentifierHash(id) == 0XFF);
}

int main(void) {
  TEST_RTIdentifierCreate_Success();
  TEST_RTIdentifierDecode_AllBytesDistinct();
  TEST_RTIdentifierEqual_EqualIdentifier();
  TEST_RTIdentifierEqual_LengthMismatch();
  TEST_RTIdentifierEqual_ContentMismatch();
  TEST_RTIdentifierHash_AllBytesDistinct();
}

#endif

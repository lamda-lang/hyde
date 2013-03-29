#include "RTIdentifier.c"

RTIdentifier FIXTURE_Identifier(RTInteger8Bit length) {
  RTIdentifier id = RTIdentifierCreate(length);
  REQUIRE(id != NULL);
  return id;
}

void TEST_RTIdentifierCreate_Valid(void) {
  RTIdentifier id = RTIdentifierCreate(8);
  REQUIRE(id != NULL);
  ASSERT(id->length == 8);
  for (RTIndex index = 0; index < 8; index += 1) {
    id->codepoint[index] = index;
    ASSERT(id->codepoint[index] == index);
  }
}

void TEST_RTIdentifierDealloc_Valid(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  RTIdentifierDealloc(id);
}

void TEST_RTIdentifierDecode_AllBytesDistinct(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  RTByte data[] = {0X01};
  RTByte *alias = data;
  RTIdentifierDecode(id, &alias, sizeof(data));
  ASSERT(id->codepoint[0] == 0X01);
  ASSERT(alias == data + sizeof(data));
}

void TEST_RTIdentifierEqual_Equal(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  RTIdentifier other = FIXTURE_Identifier(1);
  id->codepoint[0] = 0X01;
  other->codepoint[0] = 0X01;
  ASSERT(RTIdentifierEqual(id, other) == TRUE);
}

void TEST_RTIdentifierEqual_LengthMismatch(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  RTIdentifier other = FIXTURE_Identifier(2);
  ASSERT(RTIdentifierEqual(id, other) == FALSE);
}

void TEST_RTIdentifierEqual_ContentMismatch(void) {
  RTIdentifier id = FIXTURE_Identifier(1);
  RTIdentifier other = FIXTURE_Identifier(1);
  id->codepoint[0] = 0X01;
  other->codepoint[0] = 0X02;
  ASSERT(RTIdentifierEqual(id, other) == FALSE);
}

void TEST_RTIdentifierHash_NonEmpty(void) {
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

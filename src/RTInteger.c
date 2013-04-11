#include "RTInteger.h"

struct RTInteger {
  RTInteger32Bit count;
  RTInteger64Bit value[];
};

static inline RTInteger Create(RTInteger32Bit count) {
  RTSize size = sizeof(struct RTInteger) + SIZE_OF(RTInteger64Bit, count);
  RTInteger integer = RTMemoryAlloc(size);
  if (integer == NULL) {
    return NULL;
  }
  integer->count = count;
  return integer;
}

void RTIntegerDealloc(RTInteger integer) {
  RTMemoryDealloc(integer);
}

RTSize RTIntegerEncodingSize(RTInteger integer) {
  return sizeof(RTInteger32Bit) + SIZE_OF(RTInteger64Bit, integer->count);
}

void RTIntegerEncode(RTInteger integer, RTByte *buffer) {
  RTByte *alias = buffer;
  RTEncodeInteger32Bit(integer->count, &alias);
  for (RTInteger32Bit index = 0; index < integer->count; index += 1) {
    RTEncodeInteger64Bit(integer->value[index], &alias);
  }
}

RTInteger RTIntegerDecode(RTByte **data) {
  RTInteger32Bit count = RTDecodeInteger32Bit(data);
  RTInteger integer = Create(count);
  if (integer == NULL) {
    return NULL;
  }
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    integer->value[index] = RTDecodeInteger64Bit(data);
  }
  return integer;
}

RTBool RTIntegerEqual(RTInteger integer, RTInteger other) {
  RTSize size = SIZE_OF(RTInteger64Bit, integer->count);
  return integer->count == other->count && RTMemoryCompare(integer->value, other->value, size);
}

RTInteger64Bit RTIntegerHash(RTInteger integer) {
  return integer->value[0];
}

RTInteger RTIntegerSum(RTInteger integer, RTInteger other) {
  RTInteger result = Create(1);
  if (result == NULL) {
    return NULL;
  }
  result->value[0] = integer->value[0] + other->value[0];
  return result;
}

#ifdef RT_INTEGER_TEST

static RTInteger FIXTURE_Integer(RTInteger64Bit value) {
  RTInteger integer = Create(1);
  REQUIRE(integer != NULL);
  integer->value[0] = value;
  return integer;
}

static void AFTER_Integer(RTInteger integer) {
  RTIntegerDealloc(integer);
}

static void TEST_Create_Valid(void) {
  RTInteger integer = FIXTURE_Integer(2);
  REQUIRE(integer != NULL);
  ASSERT(integer->count == 1);
  ASSERT(integer->value[0] == 2);
}

static void TEST_RTIntegerDealloc_Valid(void) {
  RTInteger integer = FIXTURE_Integer(0);
  RTIntegerDealloc(integer);
}

static void TEST_RTIntegerEncodingSize_Valid(void) {
  RTInteger integer = FIXTURE_Integer(0);
  RTSize size = sizeof(RTInteger32Bit) + sizeof(RTInteger64Bit);
  ASSERT(RTIntegerEncodingSize(integer) == size);
  AFTER_Integer(integer);
}

static void TEST_RTIntegerEncode_Valid(void) {
  RTInteger integer = FIXTURE_Integer(2);
  RTByte buffer[] = {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00};
  RTIntegerEncode(integer, buffer);
  ASSERT(buffer[0] == 0X01);
  ASSERT(buffer[1] == 0X00);
  ASSERT(buffer[2] == 0X00);
  ASSERT(buffer[3] == 0X00);
  ASSERT(buffer[4] == 0X02);
  ASSERT(buffer[5] == 0X00);
  ASSERT(buffer[6] == 0X00);
  ASSERT(buffer[7] == 0X00);
  ASSERT(buffer[8] == 0X00);
  ASSERT(buffer[9] == 0X00);
  ASSERT(buffer[10] == 0X00);
  ASSERT(buffer[11] == 0X00);
  AFTER_Integer(integer);
}

static void TEST_RTIntegerDecode_Valid(void) {
  RTByte data[] = {0X01, 0X00, 0X00, 0X00, 0X02, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00};
  RTByte *alias = data;
  RTInteger integer = RTIntegerDecode(&alias);
  ASSERT(integer->count == 1);
  ASSERT(integer->value[0] == 2);
  ASSERT(alias == data + sizeof(data));
  AFTER_Integer(integer);
}

static void TEST_RTIntegerEqual_Identity(void) {
  RTInteger integer = FIXTURE_Integer(2);
  ASSERT(RTIntegerEqual(integer, integer) == TRUE);
  AFTER_Integer(integer);
}

static void TEST_RTIntegerHash_Valid(void) {
  RTInteger integer = FIXTURE_Integer(2);
  ASSERT(RTIntegerHash(integer) == 2);
  AFTER_Integer(integer);
}

static void TEST_RTIntegerSum_Valid(void) {
  RTInteger integer = FIXTURE_Integer(2);
  RTInteger other = FIXTURE_Integer(3);
  RTInteger sum = RTIntegerSum(integer, other);
  ASSERT(sum->count == 1);
  ASSERT(sum->value[0] == 5);
  AFTER_Integer(integer);
  AFTER_Integer(other);
}

int main(void) {
  TEST_Create_Valid(); 
  TEST_RTIntegerDealloc_Valid();
  TEST_RTIntegerEncodingSize_Valid();
  TEST_RTIntegerEncode_Valid();
  TEST_RTIntegerDecode_Valid();
  TEST_RTIntegerEqual_Identity();
  TEST_RTIntegerHash_Valid();
  TEST_RTIntegerSum_Valid();
}

#endif

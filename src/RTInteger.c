#include "RTInteger.h"

struct RTInteger {
  RTInteger32Bit count;
  RTInteger64Bit value[];
};

static inline RTInteger RTIntegerCreate(RTInteger32Bit count) {
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
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(data);
  RTInteger integer = RTIntegerCreate(count);
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

RTInteger32Bit RTIntegerHash(RTInteger integer) {
  RTInteger32Bit hash = integer->count;
  for (RTInteger32Bit index = 0; index < integer->count; index += 1) {
    hash += integer->value[index];
  }
  return hash;
}

RTInteger RTIntegerSum(RTInteger integer, RTInteger other) {
  integer = NULL;
  other = NULL;
  return NULL;
}

#ifdef RT_INTEGER_TEST

int main(void) {

}

#endif

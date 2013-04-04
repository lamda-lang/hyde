#include "RTInteger.h"

struct RTInteger {
  RTInteger64Bit value;
};

void RTIntegerDealloc(RTInteger integer) {
  RTMemoryDealloc(integer);
}

RTSize RTIntegerEncodingSize(RTInteger integer) {
  return sizeof(RTInteger32Bit) + SIZE_OF(integer->value, 1);
}

void RTIntegerEncode(RTInteger integer, RTByte *buffer) {
  RTByte *alias = buffer;
  RTEncodeInteger32Bit(1, &alias);
  RTEncodeInteger64Bit(integer->value, &alias);
}

RTInteger RTIntegerCreate64Bit(RTInteger64Bit value) {
  RTInteger integer = RTMemoryAlloc(sizeof(struct RTInteger));
  if (integer == NULL) {
    return NULL;
  }
  integer->value = value;
  return integer;
}

RTBool RTIntegerEqual(RTInteger integer, RTInteger other) {
  return integer->value == other->value;
}

RTInteger64Bit RTIntegerHash(RTInteger integer) {
  return integer->value;
}

RTInteger RTIntegerSum(RTInteger integer, RTInteger other) {
  RTInteger64Bit sum = integer->value + other->value;
  return RTIntegerCreate64Bit(sum);
}

#ifdef RT_INTEGER_TEST

int main(void) {

}

#endif

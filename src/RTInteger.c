#include "RTInteger.h"

struct RTInteger {
  RTInteger32Bit count;
  RTBool positive;
  RTInteger32Bit value[];
};

static inline RTInteger Create(RTInteger32Bit count) {
  RTSize size = sizeof(struct RTInteger) + sizeof(RTInteger32Bit) * count;
  RTInteger integer = RTMemoryAlloc(size);
  if (integer == NULL) {
    return NULL;
  }
  integer->count = count;
  integer->positive = TRUE;
  return integer;
}

static inline RTInteger Expand(RTInteger integer, RTInteger32Bit count) {
  RTSize size = sizeof(struct RTInteger) + sizeof(RTInteger32Bit) * (integer->count + count);
  RTInteger new = RTMemoryRealloc(integer, size);
  if (new == NULL) {
    RTMemoryDealloc(integer);
    return NULL;
  }
  new->count += count;
  return new;
}

void RTIntegerDealloc(RTInteger integer) {
  RTMemoryDealloc(integer);
}

RTSize RTIntegerEncodingSize(RTInteger integer) {
  return sizeof(RTInteger32Bit) + sizeof(RTInteger32Bit) * integer->count;
}

void RTIntegerEncode(RTInteger integer, RTByte *buffer) {
  RTByte *alias = buffer;
  RTEncodeInteger32Bit(integer->count, &alias);
  for (RTInteger32Bit index = 0; index < integer->count; index += 1) {
    RTEncodeInteger32Bit(integer->value[index], &alias);
  }
}

RTInteger RTIntegerDecode(RTByte **data) {
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(data);
  RTInteger integer = Create(count);
  if (integer == NULL) {
    return NULL;
  }
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    integer->value[index] = RTDecodeInteger32Bit(data);
  }
  return integer;
}

RTBool RTIntegerEqual(RTInteger integer, RTInteger other) {
  RTSize size = sizeof(RTInteger32Bit) * integer->count;
  return integer->count == other->count && RTMemoryCompare(integer->value, other->value, size);
}

RTInteger64Bit RTIntegerHash(RTInteger integer) {
  return integer->value[0];
}

RTInteger RTIntegerSum(RTInteger integer, RTInteger other) {
  RTInteger longer = integer;
  RTInteger shorter = other;
  if (other->count > integer->count) {
    longer = other;
    shorter = integer;
  }
  RTInteger new = Create(longer->count);
  if (new == NULL) {
    return NULL;
  }
  RTInteger32Bit carry = 0;
  for (RTInteger32Bit index = 0; index < longer->count; index += 1) {
    RTInteger64Bit longerValue = longer->value[index];
    RTInteger64Bit shorterValue = (index < shorter->count ? shorter->value[index] : 0);
    RTInteger64Bit sum = longerValue + shorterValue + carry;
    new->value[index] = sum & 0X00000000FFFFFFFF;
    carry = sum >> 32;
  }
  if (carry != 0) {
    new = Expand(new, 1);
    if (new == NULL) {
      return NULL;
    }
    new->value[longer->count] = carry;
  }
  return new;
}

#include "RTInteger.h"

enum {
  RTFlagPositive = RTFlagAlpha
};

struct RTInteger {
  RTValue base;
  RTInteger32Bit count;
  RTInteger32Bit value[];
};

static inline RTSize Size(RTInteger32Bit count) {
  return sizeof(RTInteger) + sizeof(RTInteger32Bit) * count;
}

static inline RTInteger *Create(RTInteger32Bit count) {
  RTSize size = Size(count);
  RTInteger *integer = RTMemoryAlloc(size);
  if (integer == NULL) {
    return NULL;
  }
  integer->base = RTValueInit(RTTypeInteger, RTFlagPositive);
  integer->count = count;
  return integer;
}

static inline RTInteger *Carry(RTInteger *integer, RTInteger32Bit carry) {
  if (carry == 0) {
    return integer;
  }
  RTSize size = Size(integer->count + 1);
  RTInteger *new = RTMemoryRealloc(integer, size);
  if (new == NULL) {
    RTMemoryDealloc(integer);
    return NULL;
  }
  new->value[new->count] = carry;
  new->count += 1;
  return new;
}

RTValue *RTIntegerValueBridge(RTInteger *integer) {
  return (RTValue *)integer;
}

void RTIntegerDealloc(RTInteger *integer) {
  RTMemoryDealloc(integer);
}

RTSize RTIntegerEncodingSize(RTInteger *integer) {
  return sizeof(RTInteger32Bit) + sizeof(RTInteger32Bit) * integer->count;
}

void RTIntegerEncode(RTInteger *integer, RTByte *buffer) {
  RTByte *alias = buffer;
  RTEncodeInteger32Bit(integer->count, &alias);
  for (RTInteger32Bit index = 0; index < integer->count; index += 1) {
    RTEncodeInteger32Bit(integer->value[index], &alias);
  }
}

RTInteger *RTIntegerDecode(RTByte **data) {
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(data);
  RTInteger *integer = Create(count);
  if (integer == NULL) {
    return NULL;
  }
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    integer->value[index] = RTDecodeInteger32Bit(data);
  }
  return integer;
}

bool RTIntegerEqual(RTInteger *integer, RTInteger *other) {
  RTSize size = sizeof(RTInteger32Bit) * integer->count;
  return integer->count == other->count &&
  /* missing */
         RTMemoryEqual(integer->value, other->value, size);
}

RTInteger64Bit RTIntegerHash(RTInteger *integer) {
  return integer->value[0];
}

RTInteger *RTIntegerSum(RTInteger *integer, RTInteger *other) {
  RTInteger *longer = integer;
  RTInteger *shorter = other;
  if (other->count > integer->count) {
    longer = other;
    shorter = integer;
  }
  RTInteger *new = Create(longer->count);
  if (new == NULL) {
    return NULL;
  }
  RTInteger32Bit carry = 0;
  for (RTInteger32Bit index = 0; index < longer->count; index += 1) {
    RTInteger64Bit longerValue = longer->value[index];
    RTInteger64Bit shorterValue = (index < shorter->count ? shorter->value[index] : 0);
    RTInteger64Bit result = longerValue + shorterValue + carry;
    new->value[index] = result & 0X00000000FFFFFFFF;
    carry = result >> 32;
  }
  return Carry(new, carry);
}

#include "RTInteger.h"

typedef _Bool RTSign;

enum {
  POSITIVE = 1,
  NEGATIVE = 0
};

struct RTInteger {
  RTInteger32Bit count;
  RTSign sign;
  RTInteger32Bit value[];
};

typedef RTInteger64Bit (*RTCalculation)(RTInteger32Bit value, RTInteger32Bit other);

static inline RTSize Size(RTInteger32Bit count) {
  return sizeof(struct RTInteger) + sizeof(RTInteger32Bit) * count;
}

static inline RTInteger Create(RTInteger32Bit count) {
  RTSize size = Size(count);
  RTInteger integer = RTMemoryAlloc(size);
  if (integer == NULL) {
    return NULL;
  }
  integer->count = count;
  integer->sign = POSITIVE;
  return integer;
}

static inline RTInteger Carry(RTInteger integer, RTInteger32Bit carry) {
  if (carry == 0) {
    return integer;
  }
  RTSize size = Size(integer->count + 1);
  RTInteger new = RTMemoryRealloc(integer, size);
  if (new == NULL) {
    RTMemoryDealloc(integer);
    return NULL;
  }
  new->value[new->count] = carry;
  new->count += 1;
  return new;
}

static inline RTInteger Result(RTInteger integer, RTInteger other, RTCalculation calc) {
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
    RTInteger32Bit longerValue = longer->value[index];
    RTInteger32Bit shorterValue = (index < shorter->count ? shorter->value[index] : 0);
    RTInteger64Bit result = calc(longerValue, shorterValue) + carry;
    new->value[index] = result & 0X00000000FFFFFFFF;
    carry = result >> 32;
  }
  return Carry(new, carry);
}

static inline RTInteger64Bit Sum(RTInteger32Bit value, RTInteger32Bit other) {
  RTInteger64Bit value64Bit = value;
  RTInteger64Bit other64Bit = other;
  return value64Bit + other64Bit;
}

static inline RTInteger64Bit Product(RTInteger32Bit value, RTInteger32Bit other) {
  RTInteger64Bit value64Bit = value;
  RTInteger64Bit other64Bit = other;
  return value64Bit * other64Bit;
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
  return Result(integer, other, Sum);
}

RTInteger RTIntegerProduct(RTInteger integer, RTInteger other) {
  RTInteger result = Result(integer, other, Product);
  result->sign = integer->sign == other->sign ? POSITIVE : NEGATIVE;
  return result;
}

RTInteger RTIntegerNegation(RTInteger integer) {
  RTSize size = Size(integer->count);
  RTInteger copy = RTMemoryAlloc(size);
  if (copy == NULL) {
    return NULL;
  }
  RTMemoryCopy(integer, copy, size);
  copy->sign = integer->sign == POSITIVE ? NEGATIVE : POSITIVE;
  return copy;
}

#include "RTInteger.h"

#define RTFlagPositive RTFlagAlpha

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
    goto error;
  }
  integer->base = RTValueInit(RTTypeInteger, RTFlagPositive);
  integer->count = count;
  return integer;

error:
  return NULL;
}

static inline RTInteger *Carry(RTInteger *integer, RTInteger32Bit carry) {
  if (carry == 0) {
    return integer;
  }
  RTSize size = Size(integer->count + 1);
  RTInteger *new = RTMemoryRealloc(integer, size);
  if (new == NULL) {
    goto error;
  }
  new->value[new->count] = carry;
  new->count += 1;
  return new;

error:
  RTMemoryDealloc(integer);
  return NULL;
}

RTValue *RTIntegerValueBridge(RTInteger *integer) {
  return (RTValue *)integer;
}

void RTIntegerDealloc(RTValue *integer) {
  RTMemoryDealloc(integer);
}

RTInteger *RTIntegerDecode(RTByte **data) {
  RTInteger32Bit count = RTDecodeVBRInteger32Bit(data);
  RTInteger *integer = Create(count);
  if (integer == NULL) {
    goto error;
  } 
  for (RTInteger32Bit index = 0; index < count; index += 1) {
    integer->value[index] = RTDecodeInteger32Bit(data);
  }
  return integer;

error:
  return NULL;
}

RTInteger64Bit RTIntegerHash(RTValue *integer_RTInteger) {
  RTInteger *integer = RTValueIntegerBridge(integer_RTInteger);
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
    goto error;
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

error:
  return NULL;
}

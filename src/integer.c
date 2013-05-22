#include "integer.h"

#define FlagPositive FlagAlpha

struct Integer {
  Value base;
  Integer32Bit count;
  Integer32Bit value[];
};

static inline Size IntegerSize(Integer32Bit count) {
  return sizeof(Integer) + sizeof(Integer32Bit) * count;
}

static inline Integer *Create(Integer32Bit count) {
  Size size = IntegerSize(count);
  Integer *integer = MemoryAlloc(size);
  if (integer == NULL) {
    goto error;
  }
  integer->base = ValueInit(TypeInteger, FlagPositive);
  integer->count = count;
  return integer;

error:
  return NULL;
}

static inline Integer *Carry(Integer *integer, Integer32Bit carry) {
  if (carry == 0) {
    return integer;
  }
  Size size = IntegerSize(integer->count + 1);
  Integer *new = MemoryRealloc(integer, size);
  if (new == NULL) {
    goto error;
  }
  new->value[new->count] = carry;
  new->count += 1;
  return new;

error:
  MemoryDealloc(integer);
  return NULL;
}

Value *IntegerValueBridge(Integer *integer) {
  return (Value *)integer;
}

void IntegerDealloc(Value *integer) {
  MemoryDealloc(integer);
}

Integer *IntegerDecode(Byte **data) {
  Integer32Bit count = DecodeVBRInteger32Bit(data);
  Integer *integer = Create(count);
  if (integer == NULL) {
    goto error;
  } 
  for (Integer32Bit index = 0; index < count; index += 1) {
    integer->value[index] = DecodeInteger32Bit(data);
  }
  return integer;

error:
  return NULL;
}

Integer64Bit IntegerHash(Value *integer_Integer) {
  Integer *integer = ValueIntegerBridge(integer_Integer);
  return integer->value[0];
}

Integer *IntegerSum(Integer *integer, Integer *other) {
  Integer *longer = integer;
  Integer *shorter = other;
  if (other->count > integer->count) {
    longer = other;
    shorter = integer;
  }
  Integer *new = Create(longer->count);
  if (new == NULL) {
    goto error;
  }
  Integer32Bit carry = 0;
  for (Integer32Bit index = 0; index < longer->count; index += 1) {
    Integer64Bit longerValue = longer->value[index];
    Integer64Bit shorterValue = (index < shorter->count ? shorter->value[index] : 0);
    Integer64Bit result = longerValue + shorterValue + carry;
    new->value[index] = result & 0X00000000FFFFFFFF;
    carry = result >> 32;
  }
  return Carry(new, carry);

error:
  return NULL;
}

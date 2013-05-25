#include "value.h"

typedef struct {
  Dealloc *dealloc;
  Hash *hash;
  Enumerate *enumerate;
} Class;

Class class[] = {
  [TypeBoolean] = {
    .dealloc = BooleanDealloc,
    .hash = BooleanHash
  },
  [TypeIdentifier] = {
    .dealloc = IdentifierDealloc,
    .hash = IdentifierHash
  },
  [TypeInteger] = {
    .dealloc = IntegerDealloc,
    .hash = IntegerHash
  },
  [TypeLambda] = {
    .dealloc = LambdaDealloc,
    .hash = LambdaHash,
    .enumerate = LambdaEnumerate
  },
  [TypeList] = {
    .dealloc = ListDealloc,
    .hash = ListHash,
    .enumerate = ListEnumerate
  },
  [TypeMap] = {
    .dealloc = MapDealloc,
    .hash = MapHash,
    .enumerate = MapEnumerate
  },
  [TypeNil] = {
    .dealloc = NilDealloc,
    .hash = NilHash
  },
  [TypeString] = {
    .dealloc = StringDealloc,
    .hash = StringHash
  }
};

Value ValueInit(Type type, Flag mask) {
  return type;
}

Type ValueType(Value *value) {
  return *value & 0XF;
}

void ValueSetFlag(Value *value, Flag mask, bool truth) {
  *value = truth ? *value | mask : *value & ~mask;
}

bool ValueFlagSet(Value *value, Flag mask) {
  return (*value & mask) == mask;
}

bool ValueBaseFlagSet(Value value, Flag mask) {
  return (value & mask) == mask;
}

Boolean *ValueBooleanBridge(Value *value) {
  return (Boolean *)value;
}

Identifier *ValueIdentifierBridge(Value *value) {
  return (Identifier *)value;
}

Integer *ValueIntegerBridge(Value *value) {
  return (Integer *)value;
}

Lambda *ValueLambdaBridge(Value *value) {
  return (Lambda *)value;
}

List *ValueListBridge(Value *value) {
  return (List *)value;
}

Map *ValueMapBridge(Value *value) {
  return (Map *)value;
}

Nil *ValueNilBridge(Value *value) {
  return (Nil *)value;
}

String *ValueStringBridge(Value *value) {
  return (String *)value;
}

void ValueEnumerate(Value *value, void (*block)(Value *value)) {
  Type type = ValueType(value);
  Enumerate *enumerate = class[type].enumerate;
  if (enumerate != NULL) {
    enumerate(value, block);
  }
}

void ValueDealloc(Value *value) {
  Type type = ValueType(value);
  Dealloc *dealloc = class[type].dealloc;
  if (dealloc != NULL) {
    dealloc(value);
  }
}

Integer64Bit ValueHash(Value *value) {
  Type type = ValueType(value);
  return class[type].hash(value);
}

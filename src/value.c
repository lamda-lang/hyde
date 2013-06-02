#include "value.h"

typedef struct {
    Dealloc *dealloc;
    Hash *hash;
    Enumerate *enumerate;
} Class;

Class class[] = {
    [TypeBoolean] = {
        .hash = BooleanHash
    },
    [TypeDo] = {
	.dealloc = DoDealloc,
	.hash = DoHash,
	.enumerate = DoEnumerate
    },
    [TypeFloat] = {
	.dealloc = FloatDealloc,
	.hash = FloatHash
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
        .hash = NilHash
    },
    [TypeRange] = {
	.dealloc = RangeDealloc,
	.hash = RangeHash,
	.enumerate = RangeEnumerate
    },
    [TypeSet] = {
	.dealloc = SetDealloc,
	.hash = SetHash,
	.enumerate = SetEnumerate
    },
    [TypeString] = {
        .dealloc = StringDealloc,
        .hash = StringHash
    }
};

Type ValueType(Value *value) {
    return *value & 0XF;
}

void ValueSetFlag(Value *value, Flag mask, bool truth) {
    *value = truth ? *value | mask : *value & ~mask;
}

bool ValueFlagSet(Value *value, Flag mask) {
    return (*value & mask) == mask;
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

Integer64 ValueHash(Value *value) {
    Type type = ValueType(value);
    return class[type].hash(value);
}

Boolean *ValueBooleanBridge(Value *booleanValue) {
    return (Boolean *)booleanValue;
}

Do *ValueDoBridge(Value *doValue) {
    return (Do *)doValue;
}

Float *ValueFloatBridge(Value *floatValue) {
    return (Float *)floatValue;
}

Identifier *ValueIdentifierBridge(Value *idValue) {
    return (Identifier *)idValue;
}

Integer *ValueIntegerBridge(Value *integerValue) {
    return (Integer *)integerValue;
}

Lambda *ValueLambdaBridge(Value *lambdaValue) {
    return (Lambda *)lambdaValue;
}

List *ValueListBridge(Value *listValue) {
    return (List *)listValue;
}

Map *ValueMapBridge(Value *mapValue) {
    return (Map *)mapValue;
}

Nil *ValueNilBridge(Value *nilValue) {
    return (Nil *)nilValue;
}

Range *ValueRangeBridge(Value *rangeValue) {
    return (Range *)rangeValue;
}

Set *ValueSetBridge(Value *setValue) {
    return (Set *)setValue;
}

String *ValueStringBridge(Value *stringValue) {
    return (String *)stringValue;
}

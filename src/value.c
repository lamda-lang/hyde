#include "value.h"

typedef struct {
    Dealloc *dealloc;
    Hash *hash;
    Equal *equal;
    Enumerate *enumerate;
} Class;

Class class[] = {
    [TypeBoolean] = {
        .hash = BooleanHash,
        .equal = BooleanEqual,
    },
    [TypeDo] = {
        .dealloc = DoDealloc,
        .hash = DoHash,
        .enumerate = DoEnumerate,
    },
    [TypeFloat] = {
        .dealloc = FloatDealloc,
        .hash = FloatHash,
        .equal = FloatEqual,
    },
    [TypeTag] = {
        .dealloc = TagDealloc,
        .hash = TagHash,
        .equal = TagEqual,
    },
    [TypeInteger] = {
        .dealloc = IntegerDealloc,
        .hash = IntegerHash,
        .equal = IntegerEqual,
    },
    [TypeLamda] = {
        .dealloc = LamdaDealloc,
        .hash = LamdaHash,
        .enumerate = LamdaEnumerate,
    },
    [TypeList] = {
        .dealloc = ListDealloc,
        .hash = ListHash,
        .enumerate = ListEnumerate,
    },
    [TypeMap] = {
        .dealloc = MapDealloc,
        .hash = MapHash,
        .enumerate = MapEnumerate,
    },
    [TypeModule] = {
        .dealloc = ModuleDealloc,
    },
    [TypeNil] = {
        .hash = NilHash,
        .equal = NilEqual,
    },
    [TypeRange] = {
        .dealloc = RangeDealloc,
        .hash = RangeHash,
        .enumerate = RangeEnumerate,
    },
    [TypeSet] = {
        .dealloc = SetDealloc,
        .hash = SetHash,
        .enumerate = SetEnumerate,
    },
    [TypeString] = {
        .dealloc = StringDealloc,
        .hash = StringHash,
        .equal = StringEqual,
    },
};

Type ValueType(Value *value) {
    return *value & 0XF;
}

void ValueSetFlag(Value *value, Flag mask, Bool truth) {
    *value = truth ? *value | mask : *value & ~mask;
}

Bool ValueFlagSet(Value *value, Flag mask) {
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

Bool ValueEqual(Value *value, Value *other) {
    Type type = ValueType(value);
    return type == ValueType(other) ? class[type].equal(value, other) : FALSE;
}

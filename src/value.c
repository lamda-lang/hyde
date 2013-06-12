#include "value.h"

typedef struct {
    Dealloc *dealloc;
    Hash *hash;
    Enumerate *enumerate;
    Eval *eval;
} Class;

Class class[] = {
    [TypeBoolean] = {
        .hash = BooleanHash,
	.eval = BooleanEval
    },
    [TypeCase] = {
        .dealloc = CaseDealloc,
	.eval = CaseEval
    },
    [TypeDo] = {
	.dealloc = DoDealloc,
	.hash = DoHash,
	.enumerate = DoEnumerate,
	.eval = DoEval
    },
    [TypeFloat] = {
	.dealloc = FloatDealloc,
	.hash = FloatHash,
	.eval = FloatEval
    },
    [TypeIdentifier] = {
        .dealloc = IdentifierDealloc,
        .hash = IdentifierHash,
	.eval = IdentifierEval
    },
    [TypeInteger] = {
        .dealloc = IntegerDealloc,
        .hash = IntegerHash,
	.eval = IntegerEval
    },
    [TypeLambda] = {
        .dealloc = LambdaDealloc,
        .hash = LambdaHash,
        .enumerate = LambdaEnumerate,
	.eval = LambdaEval
    },
    [TypeList] = {
        .dealloc = ListDealloc,
        .hash = ListHash,
        .enumerate = ListEnumerate,
	.eval = ListEval
    },
    [TypeMap] = {
        .dealloc = MapDealloc,
        .hash = MapHash,
        .enumerate = MapEnumerate,
	.eval = MapEval
    },
    [TypeNil] = {
        .hash = NilHash,
	.eval = NilEval
    },
    [TypeRange] = {
	.dealloc = RangeDealloc,
	.hash = RangeHash,
	.enumerate = RangeEnumerate,
	.eval = RangeEval
    },
    [TypeResult] = {
	.dealloc = ResultDealloc,
	.eval = ResultEval
    },
    [TypeSet] = {
	.dealloc = SetDealloc,
	.hash = SetHash,
	.enumerate = SetEnumerate,
	.eval = SetEval
    },
    [TypeString] = {
        .dealloc = StringDealloc,
        .hash = StringHash,
	.eval = StringEval
    },
    [TypeWhen] = {
	.dealloc = WhenDealloc,
	.eval = WhenEval
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

Value *ValueEval(Value *value, bool pure, Error *error) {
    Type type = ValueType(value);
    return class[type].eval(value, pure, error);
}

Boolean *ValueBooleanBridge(Value *value) {
    return (Boolean *)value;
}

Case *ValueCaseBridge(Value *value) {
    return (Case *)value;
}

Do *ValueDoBridge(Value *value) {
    return (Do *)value;
}

Float *ValueFloatBridge(Value *value) {
    return (Float *)value;
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

Range *ValueRangeBridge(Value *value) {
    return (Range *)value;
}

Result *ValueResultBridge(Value *value) {
    return (Result *)value;
}

Set *ValueSetBridge(Value *value) {
    return (Set *)value;
}

String *ValueStringBridge(Value *value) {
    return (String *)value;
}

When *ValueWhenBridge(Value *value) {
    return (When *)value;
}

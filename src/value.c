#include "value.h"

typedef struct {
    Dealloc *dealloc;
    Hash *hash;
    Enumerate *enumerate;
    Fetch *fetch;
    Eval *eval;
} Class;

Class class[] = {
    [TypeBoolean] = {
        .hash = BooleanHash,
	.eval = BooleanEval
    },
    [TypeCase] = {
        .dealloc = CaseDealloc,
	.fetch = CaseFetch,
	.eval = CaseEval
    },
    [TypeDo] = {
	.dealloc = DoDealloc,
	.hash = DoHash,
	.enumerate = DoEnumerate,
	.fetch = DoFetch,
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
	.fetch = LambdaFetch,
	.eval = LambdaEval
    },
    [TypeList] = {
        .dealloc = ListDealloc,
        .hash = ListHash,
        .enumerate = ListEnumerate,
	.fetch = ListFetch,
	.eval = ListEval
    },
    [TypeMap] = {
        .dealloc = MapDealloc,
        .hash = MapHash,
        .enumerate = MapEnumerate,
	.fetch = MapFetch,
	.eval = MapEval
    },
    [TypeModule] = {
	.dealloc = ModuleDealloc,
	.fetch = ModuleFetch,
	.eval = ModuleEval
    },
    [TypeNil] = {
        .hash = NilHash,
	.eval = NilEval
    },
    [TypeRange] = {
	.dealloc = RangeDealloc,
	.hash = RangeHash,
	.enumerate = RangeEnumerate,
	.fetch = RangeFetch,
	.eval = RangeEval
    },
    [TypeResult] = {
	.dealloc = ResultDealloc,
	.fetch = ResultFetch,
	.eval = ResultEval
    },
    [TypeSet] = {
	.dealloc = SetDealloc,
	.hash = SetHash,
	.enumerate = SetEnumerate,
	.fetch = SetFetch,
	.eval = SetEval
    },
    [TypeString] = {
        .dealloc = StringDealloc,
        .hash = StringHash,
	.eval = StringEval
    },
    [TypeWhen] = {
	.dealloc = WhenDealloc,
	.fetch = WhenFetch,
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

void ValueFetch(Value *value, Value **values) {
    Type type = ValueType(value);
    Fetch *fetch = class[type].fetch;
    if (fetch != NULL) {
	fetch(value, values);
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

Boolean *ValueBooleanBridge(Value *boolValue) {
    return (Boolean *)boolValue;
}

Case *ValueCaseBridge(Value *caseValue) {
    return (Case *)caseValue;
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

Result *ValueResultBridge(Value *resultValue) {
    return (Result *)resultValue;
}

Set *ValueSetBridge(Value *setValue) {
    return (Set *)setValue;
}

String *ValueStringBridge(Value *stringValue) {
    return (String *)stringValue;
}

Module *ValueModuleBridge(Value *moduleValue) {
    return (Module *)moduleValue;
}

When *ValueWhenBridge(Value *whenValue) {
    return (When *)whenValue;
}

#include "value.h"

typedef struct {
    Dealloc *dealloc;
    Hash *hash;
    Equal *equal;
    Enumerate *enumerate;
    Fetch *fetch;
    Eval *eval;
} Class;

Class class[] = {
    [TypeBoolean] = {
        .hash = BooleanHash,
	.equal = BooleanEqual,
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
	.equal = FloatEqual,
	.eval = FloatEval
    },
    [TypeIdentifier] = {
        .dealloc = IdentifierDealloc,
        .hash = IdentifierHash,
	.equal = IdentifierEqual,
	.eval = IdentifierEval
    },
    [TypeInteger] = {
        .dealloc = IntegerDealloc,
        .hash = IntegerHash,
	.equal = IntegerEqual,
	.eval = IntegerEval
    },
    [TypeLamda] = {
        .dealloc = LamdaDealloc,
        .hash = LamdaHash,
        .enumerate = LamdaEnumerate,
	.fetch = LamdaFetch,
	.eval = LamdaEval
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
	.equal = NilEqual,
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
	.equal = StringEqual,
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

bool ValueEqual(Value *value, Value *other) {
    Type type = ValueType(value);
    if (type != ValueType(other)) return false;
    return class[type].equal(value, other);
}

Value *ValueEval(Value *value, bool pure, Error *error) {
    Type type = ValueType(value);
    return class[type].eval(value, pure, error);
}

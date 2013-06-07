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

static Type GetType(Value *value) {
    return *value & 0XF;
}

void ValueSetFlag(Value *value, Flag mask, bool truth) {
    *value = truth ? *value | mask : *value & ~mask;
}

bool ValueFlagSet(Value *value, Flag mask) {
    return (*value & mask) == mask;
}

void ValueEnumerate(Value *value, void (*block)(Value *value)) {
    Type type = GetType(value);
    Enumerate *enumerate = class[type].enumerate;
    if (enumerate != NULL) {
        enumerate(value, block);
    }
}

void ValueDealloc(Value *value) {
    Type type = GetType(value);
    Dealloc *dealloc = class[type].dealloc;
    if (dealloc != NULL) {
        dealloc(value);
    }
}

Integer64 ValueHash(Value *value) {
    Type type = GetType(value);
    return class[type].hash(value);
}

Boolean *ValueBooleanBridge(Value *value, Error *error) {
    if (error != NULL && GetType(value) != TypeBoolean) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    return (Boolean *)value;

returnError:
    return NULL;
}

Do *ValueDoBridge(Value *value, Error *error) {
    if (error != NULL && GetType(value) != TypeDo) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    return (Do *)value;

returnError:
    return NULL;
}

Float *ValueFloatBridge(Value *value, Error *error) {
    if (error != NULL && GetType(value) != TypeFloat) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    return (Float *)value;

returnError:
    return NULL;
}

Identifier *ValueIdentifierBridge(Value *value, Error *error) {
    if (error != NULL && GetType(value) != TypeIdentifier) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    return (Identifier *)value;

returnError:
    return NULL;
}

Integer *ValueIntegerBridge(Value *value, Error *error) {
    if (error != NULL && GetType(value) != TypeInteger) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    return (Integer *)value;

returnError:
    return NULL;
}

Lambda *ValueLambdaBridge(Value *value, Error *error) {
    if (error != NULL && GetType(value) != TypeLambda) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    return (Lambda *)value;

returnError:
    return NULL;
}

List *ValueListBridge(Value *value, Error *error) {
    if (error != NULL && GetType(value) != TypeList) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    return (List *)value;

returnError:
    return NULL;
}

Map *ValueMapBridge(Value *value, Error *error) {
    if (error != NULL && GetType(value) != TypeMap) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    return (Map *)value;

returnError:
    return NULL;
}

Nil *ValueNilBridge(Value *value, Error *error) {
    if (error != NULL && GetType(value) != TypeNil) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    return (Nil *)value;

returnError:
    return NULL;
}

Range *ValueRangeBridge(Value *value, Error *error) {
    if (error != NULL && GetType(value) != TypeRange) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    return (Range *)value;

returnError:
    return NULL;
}

Result *ValueResultBridge(Value *value, Error *error) {
    if (error != NULL && GetType(value) != TypeResult) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    return (Result *)value;

returnError:
    return NULL;
}

Set *ValueSetBridge(Value *value, Error *error) {
    if (error != NULL && GetType(value) != TypeSet) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    return (Set *)value;

returnError:
    return NULL;
}

String *ValueStringBridge(Value *value, Error *error) {
    if (error != NULL && GetType(value) != TypeString) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    return (String *)value;

returnError:
    return NULL;
}

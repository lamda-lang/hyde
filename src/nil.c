#include "nil.h"

struct Nil {
    Value base;
};

Value *NilCreate(Error *error) {
    Nil *nil = MemoryAlloc(sizeof(Nil), error);
    if (nil == NULL) {
	goto returnError;
    }
    return BridgeFromNil(nil);

returnError:
    return NULL;
}

Integer64 NilHash(Value *nilValue) {
    return 1829;
}

Value *NilDecode(Byte **bytes, Error *error) {
    return GlobalNil;
}

Value *NilEval(Value *nilValue, bool pure, Error *error) {
    return nilValue;
}

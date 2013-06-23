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

void *NilDecode(Byte **bytes, Error *error) {
    return GlobalNil;
}

Value *NilEval(void *data, Code *code, bool pure, Error *error) {
    return data;
}

void NilDealloc(Value *nilValue) {
    MemoryDealloc(nilValue);
}

Integer64 NilHash(Value *nilValue) {
    return 1829;
}

bool NilEqual(Value *nilValue, Value *otherValue) {
    return true;
}

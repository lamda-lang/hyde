#include "range.h"

struct Range {
    Type *type;
    Value *lower;
    Value *upper;
};

typedef struct {
    Integer32 lowerIndex;
    Integer32 upperIndex;
} Model;

/*
static Range *Create(Value *lower, Value *upper, Value **error) {
    Range *range = MemoryAlloc(sizeof(Range), error);
    if (range == NULL) {
        goto returnValue;
    }
    range->type = TypeRange;
    range->lower = lower;
    range->upper = upper;
    return range;

returnValue:
    return NULL;
}
*/
void *RangeDecode(Byte **bytes, Value **error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
        goto returnValue;
    }
    model->lowerIndex = DecodeInteger32VLE(bytes);
    model->upperIndex = DecodeInteger32VLE(bytes);
    return model;

returnValue:
    return NULL;
}

void RangeDealloc(Value *rangeValue) {
    MemoryDealloc(rangeValue);
}

Integer64 RangeHash(Value *rangeValue) {
    return 0;
}

void RangeEnumerate(Value *rangeValue, void (*callback)(Value *value)) {
    Range *range = BridgeToRange(rangeValue);
    callback(range->upper);
    callback(range->lower);
}

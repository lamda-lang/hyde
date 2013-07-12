#include "range.h"

struct Range {
    Value base;
    Value *lower;
    Value *upper;
};

typedef struct {
    Integer32 lowerIndex;
    Integer32 upperIndex;
} Model;

static Range *Create(Value *lower, Value *upper, Error *error) {
    Range *range = MemoryAlloc(sizeof(Range), error);
    if (range == NULL) {
        goto returnError;
    }
    range->base = TypeRange;
    range->lower = lower;
    range->upper = upper;
    return range;

returnError:
    return NULL;
}

void *RangeDecode(Byte **bytes, Error *error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
        goto returnError;
    }
    model->lowerIndex = DecodeInteger32VLE(bytes);
    model->upperIndex = DecodeInteger32VLE(bytes);
    return model;

returnError:
    return NULL;
}

Value *RangeEval(void *data, Code *code, Value **context, bool pure, Error *error) {
    Model *model = data;
    Value *lower = CodeEvalInstructionAtIndex(code, context, model->lowerIndex, true, error);
    if (lower == NULL) {
        goto returnError;
    }
    Value *upper = CodeEvalInstructionAtIndex(code, context, model->upperIndex, true, error);
    if (upper == NULL) {
        goto deallocLower;
    }
    Range *range = Create(lower, upper, error);
    if (range == NULL) {
        goto deallocUpper;
    }
    return BridgeFromRange(range);

deallocUpper:
    ValueDealloc(upper);
deallocLower:
    ValueDealloc(lower);
returnError:
    return NULL;
}

void RangeDealloc(Value *rangeValue) {
    MemoryDealloc(rangeValue);
}

Integer64 RangeHash(Value *rangeValue) {
    Range *range = BridgeToRange(rangeValue);
    return ValueHash(range->lower) + ValueHash(range->upper);
}

void RangeEnumerate(Value *rangeValue, void (*callback)(Value *value)) {
    Range *range = BridgeToRange(rangeValue);
    callback(range->upper);
    callback(range->lower);
}

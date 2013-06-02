#include "range.h"

struct Range {
    Value base;
    Value *lower;
    Value *upper;
};

static inline Integer64 HashValue(Value *value) {
    return value != NULL ? ValueHash(value) : 0;
}

Range *RangeCreate(Error *error) {
    Range *range = MemoryAlloc(sizeof(Range), error);
    if (range == NULL) {
	goto returnError;
    }
    range->base = TypeRange;
    return range;

returnError:
    return NULL;
}

Value *RangeValueBridge(Range *range) {
    return (Value *)range;
}

void RangeDealloc(Value *rangeValue) {
    MemoryDealloc(rangeValue);
}

void RangeSetBounds(Range *range, Value *lower, Value *upper) {
    range->lower = lower;
    range->upper = upper;
}

Integer64 RangeHash(Value *rangeValue) {
    Range *range = ValueRangeBridge(rangeValue);
    return HashValue(range->lower) + HashValue(range->upper);
}

void RangeEnumerate(Value *rangeValue, void (*block)(Value *value)) {
    Range *range = ValueRangeBridge(rangeValue);
    block(range->lower);
    block(range->upper);
}

#include "range.h"

struct Range {
    Value base;
    Element lower;
    Element upper;
};

static Range *Create(Integer32 upperIndex, Integer32 lowerIndex, Error *error) {
    Size size = sizeof(Range);
    Range *range = MemoryAlloc(size, error);
    if (range == NULL) {
	goto returnError;
    }
    range->base = TypeRange;
    range->upper.index = upperIndex;
    range->lower.index = lowerIndex;
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

Integer64 RangeHash(Value *rangeValue) {
    Range *range = ValueRangeBridge(rangeValue);
    return ValueHash(range->lower.value) + ValueHash(range->upper.value);
}

void RangeEnumerate(Value *rangeValue, void (*callback)(Value *value)) {
    Range *range = ValueRangeBridge(rangeValue);
    callback(range->upper.value);
    callback(range->lower.value);
}

Value *RangeDecode(Byte **bytes, Error *error) {
    Integer32 lowerIndex = DecodeInteger32VLE(bytes);
    Integer32 upperIndex = DecodeInteger32VLE(bytes);
    Range *range = Create(lowerIndex, upperIndex, error);
    return RangeValueBridge(range);
}

void RangeFetch(Value *rangeValue, Value **values) {
    Range *range = ValueRangeBridge(rangeValue);
    range->upper.value = values[range->upper.index];
    range->lower.value = values[range->lower.index];
}

Value *RangeEval(Value *rangeValue, Error *error) {
    Range *range = ValueRangeBridge(rangeValue);
    Value *lower = ValueEval(range->lower.value, error);
    if (lower == NULL) {
	goto returnError;
    }
    Value *upper = ValueEval(range->upper.value, error);
    if (upper == NULL) {
	goto returnError;
    }
    range->lower.value = lower;
    range->upper.value = upper;
    return rangeValue;

returnError:
    return NULL;
}

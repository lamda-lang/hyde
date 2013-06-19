#include "range.h"

struct Range {
    Value base;
    Element lower;
    Element upper;
};

static Range *Create(Integer32 upperIndex, Integer32 lowerIndex, Error *error) {
    Range *range = MemoryAlloc(sizeof(Range), error);
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

void RangeDealloc(Value *rangeValue) {
    MemoryDealloc(rangeValue);
}

Integer64 RangeHash(Value *rangeValue) {
    Range *range = BridgeToRange(rangeValue);
    return ValueHash(range->lower.value) + ValueHash(range->upper.value);
}

void RangeEnumerate(Value *rangeValue, void (*callback)(Value *value)) {
    Range *range = BridgeToRange(rangeValue);
    callback(range->upper.value);
    callback(range->lower.value);
}

Value *RangeDecode(Byte **bytes, Error *error) {
    Integer32 lowerIndex = DecodeInteger32VLE(bytes);
    Integer32 upperIndex = DecodeInteger32VLE(bytes);
    Range *range = Create(lowerIndex, upperIndex, error);
    return BridgeFromRange(range);
}

void RangeFetch(Value *rangeValue, Value **values) {
    Range *range = BridgeToRange(rangeValue);
    range->upper.value = values[range->upper.index];
    range->lower.value = values[range->lower.index];
}

Value *RangeEval(Value *rangeValue, bool pure, Error *error) {
    Range *range = BridgeToRange(rangeValue);
    Value *lower = ValueEval(range->lower.value, true, error);
    if (lower == NULL) {
	goto returnError;
    }
    Value *upper = ValueEval(range->upper.value, true, error);
    if (upper == NULL) {
	goto returnError;
    }
    range->lower.value = lower;
    range->upper.value = upper;
    return rangeValue;

returnError:
    return NULL;
}

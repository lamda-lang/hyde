#include "range.h"

enum {
    FlagUpper = FlagAlpha,
    FlagLower = FlagBeta
};

struct Range {
    Value base;
    Element upper;
    Element lower;
};

static Range *Create(Flag mask, Integer32 upperIndex, Integer32 lowerIndex, Error *error) {
    Size size = sizeof(Range);
    Range *range = MemoryAlloc(size, error);
    if (range == NULL) {
	goto returnError;
    }
    range->base = TypeRange | mask;
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
    Range *range = ValueRangeBridge(rangeValue, NULL);
    Integer64 upperHash = ValueFlagSet(rangeValue, FlagUpper) ? ValueHash(range->upper.value) : 0;
    Integer64 lowerHash = ValueFlagSet(rangeValue, FlagLower) ? ValueHash(range->lower.value) : 0;
    return upperHash + lowerHash;
}

void RangeEnumerate(Value *rangeValue, void (*callback)(Value *value)) {
    Range *range = ValueRangeBridge(rangeValue, NULL);
    if (ValueFlagSet(rangeValue, FlagUpper)) {
	callback(range->upper.value);
    }
    if (ValueFlagSet(rangeValue, FlagLower)) {
	callback(range->lower.value);
    }
}

Value *RangeDecode(Byte **bytes, Error *error) {
    Integer32 lowerIndex = DecodeInteger32VLE(bytes);
    Integer32 upperIndex = DecodeInteger32VLE(bytes);
    Range *range = Create(FlagUpper | FlagLower, lowerIndex, upperIndex, error);
    return RangeValueBridge(range);
}

void RangeFetch(Value *rangeValue, Value **values) {
    Range *range = ValueRangeBridge(rangeValue, NULL);
    if (ValueFlagSet(rangeValue, FlagUpper)) {
	range->upper.value = values[range->upper.index];
    }
    if (ValueFlagSet(rangeValue, FlagLower)) {
	range->lower.value = values[range->lower.index];
    }
}

Value *RangeDecodeUpper(Byte **bytes, Error *error) {
    Integer32 upperIndex = DecodeInteger32VLE(bytes);
    Range *range = Create(FlagUpper, upperIndex, 0, error);
    return RangeValueBridge(range);
}

Value *RangeDecodeLower(Byte **bytes, Error *error) {
    Integer32 lowerIndex = DecodeInteger32VLE(bytes);
    Range *range = Create(FlagLower, 0, lowerIndex, error);
    return RangeValueBridge(range);
}

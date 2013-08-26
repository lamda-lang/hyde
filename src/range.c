#include "range.h"

struct Range {
    Type *type;
    VALUE *lower;
    VALUE *upper;
};

static Range *RangeCreate(VALUE *lower, VALUE *upper, VALUE **error) {
    Range *range = MemoryAlloc(sizeof(Range), error);
    if (*error != NULL) {
        return NULL;
    }
    range->type = TypeRange;
    range->lower = lower;
    range->upper = upper;
    return range;
}

VALUE *RangeDecode(Byte **bytes, VALUE **error) {
    VALUE *lower = DecodeValue(bytes, error);
    if (*error != NULL) {
        return NULL;
    }
    VALUE *upper = DecodeValue(bytes, error);
    if (*error != NULL) {
        return NULL;
    }
    Range *range = RangeCreate(lower, upper, error);
    return BridgeFromRange(range);
}

void RangeDealloc(VALUE *rangeValue) {
    MemoryDealloc(rangeValue);
}

Integer64 RangeHash(VALUE *rangeValue) {
    return 7;
}

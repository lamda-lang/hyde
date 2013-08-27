#include "range.h"

typedef struct {
    VALUE *type;
    VALUE *lower;
    VALUE *upper;
} Range;

static Range *RangeCreate(VALUE *lower, VALUE *upper, VALUE **error) {
    Range *range = MemoryAlloc(sizeof(Range), error);
    if (*error != NULL) {
        return NULL;
    }
    range->type = RuntimeRangeType;
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
    return RangeCreate(lower, upper, error);
}

void RangeDealloc(VALUE *rangeValue) {
    MemoryDealloc(rangeValue);
}

Integer64 RangeHash(VALUE *rangeValue) {
    return 7;
}

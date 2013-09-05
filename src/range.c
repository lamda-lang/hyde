#include "range.h"

typedef struct Range Range;

struct Range {
    VALUE *type;
    VALUE *lower;
    VALUE *upper;
};

static Range *RangeCreate(VALUE *lower, VALUE *upper, Error *error) {
    Range *range = MemoryAlloc(sizeof(Range), error);
    if (*error != ErrorNone) return NULL;
    range->type = RuntimeValueForConstant(ConstantRangeType);
    range->lower = lower;
    range->upper = upper;
    return range;
}

VALUE *RangeDecode(Byte **bytes, Error *error) {
    VALUE *lower = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    VALUE *upper = DecodeValue(bytes, error);
    if (*error != ErrorNone) return NULL;
    return RangeCreate(lower, upper, error);
}

void RangeDealloc(VALUE *rangeValue) {
    MemoryDealloc(rangeValue);
}

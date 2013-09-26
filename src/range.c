#include "range.h"

struct Range {
    Value *lower;
    Value *upper;
};

static Range *RangeCreate(Value *lower, Value *upper, Error *error) {
    Range *range = MemoryAlloc(sizeof(Range), error);
    if (ERROR(error))
        return NULL;
    range->lower = lower;
    range->upper = upper;
    return range;
}

Size RangeSize(Range *range) {
    return ValueSize(range->lower) + ValueSize(range->upper);
}

Size RangeEncode(Range *range, Byte **bytes) {
    ValueEncode(range->lower, bytes);
    ValueEncode(range->upper, bytes);
    return RangeSize(range);
}

Range *RangeDecode(Byte **bytes, Error *error) {
    Value *lower = ValueDecode(bytes, error);
    if (ERROR(error))
        return NULL;
    Value *upper = ValueDecode(bytes, error);
    if (ERROR(error))
        return NULL;
    return RangeCreate(lower, upper, error);
}

Range *RangeEval(Range *range, Value *context, Error *error) {
    Value *lower = ValueEval(range->lower, context, error);
    if (ERROR(error))
        return NULL;
    Value *upper = ValueEval(range->upper, context, error);
    if (ERROR(error))
        return NULL;
    return RangeCreate(lower, upper, error);
}

Bool RangeEqual(Range *range, Range *other) {
    if (!ValueEqual(range->lower, other->lower))
        return FALSE;
    if (!ValueEqual(range->upper, other->upper))
        return FALSE;
    return TRUE;
}

Size RangeRelease(Range *range) {
    MemoryDealloc(range);
    return sizeof(Range);
}

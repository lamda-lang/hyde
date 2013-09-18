#include <builtin/range.h>

struct Range {
    Value *lower;
    Value *upper;
};

static Range *RangeCreate(Value *lower, Value *upper) {
    Range *range = MemoryAlloc(sizeof(Range));
    if (range == NULL)
        return NULL;
    range->lower = lower;
    range->upper = upper;
    return range;
}

Range *RangeDecode(Byte **bytes) {
    Value *lower = ValueDecode(bytes);
    if (lower == NULL)
        return NULL;
    Value *upper = ValueDecode(bytes);
    if (lower == NULL)
        return NULL;
    return RangeCreate(lower, upper);
}

Range *RangeEval(Range *range, Value *context) {
    Value *lower = ValueEval(range->lower, context);
    if (lower == NULL)
        return NULL;
    Value *upper = ValueEval(range->upper, context);
    if (upper == NULL)
        return NULL;
    return RangeCreate(lower, upper);
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

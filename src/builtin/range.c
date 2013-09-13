#include <builtin/range.h>

struct Range {
    Value *lower;
    Value *upper;
};

static Value *RangeCreate(Value *lower, Value *upper) {
    Range *range = MemoryAlloc(sizeof(Range));
    if (range == NULL)
        return NULL;
    range->lower = lower;
    range->upper = upper;
    return ValueCreate(MODEL_RANGE, range);
}

Value *RangeDecode(Byte **bytes) {
    Value *lower = ValueDecode(bytes);
    if (lower == NULL)
        return NULL;
    Value *upper = ValueDecode(bytes);
    if (lower == NULL)
        return NULL;
    return RangeCreate(lower, upper);
}

Size RangeRelease(Range *range) {
    MemoryDealloc(range);
    return sizeof(Range);
}

Bool RangeEqual(Range *range, Range *other) {
    return ValueEqual(range->lower, other->lower) && ValueEqual(range->upper, other->upper);
}

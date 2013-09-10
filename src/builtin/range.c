#include <builtin/range.h>

typedef struct Range Range;

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
    return ValueCreate(ModelRange, range);
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

void RangeRelease(void *rangeData) {
    MemoryDealloc(rangeData);
}

Bool RangeEqual(void *rangeData, void *otherData) {
    Range *range = rangeData;
    Range *other = otherData;
    return ValueEqual(range->lower, other->lower) && ValueEqual(range->upper, other->upper);
}

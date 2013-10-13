#include "range.h"

struct Range {
    Value *lower;
    Value *upper;
};

static Value *RangeCreate(Value *lower, Value *upper) {
    Range *range = MemoryAllocUnit(sizeof(Range));
    range->lower = lower;
    range->upper = upper;
    return ValueCreateRange(range);
}

Value *RangeDecode(Binary *binary, Integer32 *offset) {
    Value *lower = BinaryDecodeValue(binary, offset);
    if (lower == NULL)
        return NULL;
    Value *upper = BinaryDecodeValue(binary, offset);
    if (upper == NULL)
        return NULL;
    return RangeCreate(lower, upper);
}

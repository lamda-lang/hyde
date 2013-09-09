#include <builtin/range.h>

typedef struct Range Range;

struct Range {
    Value *type;
    Value *lower;
    Value *upper;
};

static Range *RangeCreate(Value *lower, Value *upper, Error *error) {
    Range *range = MemoryAlloc(sizeof(Range), error);
    if (*error != ErrorNone)
        return NULL;
    range->type = NULL;
    range->lower = lower;
    range->upper = upper;
    return range;
}

Value *RangeDecode(Byte **bytes, Error *error) {
    Value *lower = DecodeValue(bytes, error);
    if (*error != ErrorNone)
        return NULL;
    Value *upper = DecodeValue(bytes, error);
    if (*error != ErrorNone)
        return NULL;
    return RangeCreate(lower, upper, error);
}

void RangeDealloc(Value *rangeValue) {
    MemoryDealloc(rangeValue);
}

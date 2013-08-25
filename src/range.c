#include "range.h"

struct Range {
    Type *type;
    VALUE *lower;
    VALUE *upper;
};

typedef struct {
    Integer32 lowerIndex;
    Integer32 upperIndex;
} Model;

/*
static Range *Create(VALUE *lower, VALUE *upper, VALUE **error) {
    Range *range = MemoryAlloc(sizeof(Range), error);
    if (range == NULL) {
        goto returnVALUE;
    }
    range->type = TypeRange;
    range->lower = lower;
    range->upper = upper;
    return range;

returnVALUE:
    return NULL;
}
*/
VALUE *RangeDecode(Byte **bytes, VALUE **error) {
    return NULL;
}

void RangeDealloc(VALUE *rangeVALUE) {
    MemoryDealloc(rangeVALUE);
}

Integer64 RangeHash(VALUE *rangeVALUE) {
    return 0;
}

void RangeEnumerate(VALUE *rangeVALUE, void (*callback)(VALUE *value)) {
    Range *range = BridgeToRange(rangeVALUE);
    callback(range->upper);
    callback(range->lower);
}

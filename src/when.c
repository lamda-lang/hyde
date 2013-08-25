#include "when.h"

struct When {
    Type *type;
};

typedef struct {
    Integer32 condition;
    Integer32 value;
} Index;

typedef struct {
    Integer8 count;
    Index index[];
} Model;

VALUE *WhenDecode(Byte **bytes, VALUE **error) {
    return NULL;
}

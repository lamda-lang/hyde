#include "case.h"

struct Case {
    Type *type;
};

typedef struct {
    Integer32 match;
    Integer32 guard;
    Integer32 value;
} Clause;

typedef struct {
    Integer8 length;
    Integer32 arg;
    Clause clause[];
} Model;

VALUE *CaseDecode(Byte **bytes, VALUE **error) {
    return NULL;
}

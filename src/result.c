#include "result.h"

struct Result {
    Type *type;
};

typedef struct {
    Integer32 lamda;
    Integer8 arity;
    Integer32 arg[];
} Model;

VALUE *ResultDecode(Byte **bytes, VALUE **error) {
    return NULL;
}

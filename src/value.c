#include "value.h"

typedef enum {
    MODEL_BINARY = 0,
    MODEL_BOOLEAN = 1,
    MODEL_CASE = 2,
    MODEL_DO = 3,
    MODEL_FLOAT = 4,
    MODEL_IDENTIFIER = 5,
    MODEL_INTEGER = 6,
    MODEL_LAMDA = 7,
    MODEL_LIST = 8,
    MODEL_MAP = 9,
    MODEL_MODULE = 10,
    MODEL_NIL = 11,
    MODEL_RANGE = 12,
    MODEL_RESULT = 13,
    MODEL_SET = 14,
    MODEL_STRING = 15,
    MODEL_TOKEN = 16,
    MODEL_TYPE = 17,
    MODEL_WHEN = 18
} Model;

struct Value {
    void *data;
    Integer8 model;
};


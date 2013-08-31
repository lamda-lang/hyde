#include "element.h"

typedef struct {
    VALUE *type;
    VALUE *collection;
    VALUE *key;
} Element;

static VALUE *ElementCreate(VALUE *collection, VALUE *key, Error *error) {
    Element *element = MemoryAlloc(sizeof(Element), error);
    if (*error != ErrorNone) {
        return NULL;
    }
    element->type = NULL;
    element->collection = collection;
    element->key = key;
    return element;
}

VALUE *ElementDecode(Byte **bytes, Error *error) {
    VALUE *collection = DecodeValue(bytes, error);
    if (*error != ErrorNone) {
        goto returnError;
    }
    VALUE *key = DecodeValue(bytes, error);
    if (*error != ErrorNone) {
        goto returnError;
    }
    return ElementCreate(collection, key, error);

returnError:
    return NULL;
}

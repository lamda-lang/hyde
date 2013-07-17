#include <string.h>
#include "tag.h"

struct Tag {
    Value base;
    Integer8 length;
    Integer8 codepoint[];
};

typedef struct {
    Integer8 length;
    Integer8 codepoint[];
} Model;

static Tag *Create(Integer8 length, Error *error) {
    Tag *tag = MemoryAlloc(sizeof(Tag) + sizeof(Integer8) * length, error);
    if (tag == NULL) {
        goto returnError;
    }
    tag->base = TypeTag;
    tag->length = length;
    return tag;

returnError:
    return NULL;
}

void *TagDecode(Byte **bytes, Error *error) {
    Integer8 length = DecodeInteger8FLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer8) * length, error);
    if (model == NULL) {
        goto returnError;
    }
    for (Integer8 index = 0; index < length; index += 1) {
        model->codepoint[index] = DecodeInteger8FLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *TagEval(void *data, Code *code, Value **context, Bool pure, Error *error) {
    Model *model = data;
    Tag *tag = Create(model->length, error);
    if (tag == NULL) {
        goto returnError;
    }
    MemoryCopy(model->codepoint, tag->codepoint, sizeof(Integer8) * model->length);
    return BridgeFromTag(tag);

returnError:
    return NULL;
}

Value *TagCreateWithCharacters(Char *chars, Error *error) {
    Integer8 length = strnlen(chars, 0XF) & 0XF;
    Tag *tag = Create(length, error);
    if (tag == NULL) {
        goto returnError;
    }
    MemoryCopy(chars, tag->codepoint, length);
    return BridgeFromTag(tag);

returnError:
    return NULL;
}

void TagDealloc(Value *tagValue) {
    MemoryDealloc(tagValue);
}

Integer64 TagHash(Value *tagValue) {
    return BridgeToTag(tagValue)->length;
}

Bool TagEqual(Value *tagValue, Value *otherValue) {
    Tag *tag = BridgeToTag(tagValue);
    Tag *other = BridgeToTag(otherValue);
    return tag->length == other->length &&
           MemoryEqual(tag->codepoint, other->codepoint, sizeof(Integer8) * tag->length);
}

#include "member.h"

typedef struct {
    VALUE *type;
    VALUE *record;
    VALUE *field;
} Member;

static VALUE *MemberCreate(VALUE *record, VALUE *field, Error *error) {
    Member *member = MemoryAlloc(sizeof(Member), error);
    if (*error != ErrorNone) {
        return NULL;
    }
    member->type = NULL;
    member->record = record;
    member->field = field;
    return member;
}

VALUE *MemberDecode(Byte **bytes, Error *error) {
    VALUE *record = DecodeValue(bytes, error);
    if (*error != ErrorNone) {
        goto returnError;
    }
    VALUE *field = DecodeValue(bytes, error);
    if (*error != ErrorNone) {
        goto returnError;
    }
    return MemberCreate(record, field, error);

returnError:
    return NULL;
}

#include "member.h"

typedef struct {
    VALUE *type;
    VALUE *record;
    VALUE *field;
} Member;

static VALUE *MemberCreate(VALUE *record, VALUE *field, Error *error) {
    Member *member = MemoryAlloc(sizeof(Member), error);
    if (*error != NULL) {
        return NULL;
    }
    member->type = RuntimeMemberType;
    member->record = record;
    member->field = field;
    return member;
}

VALUE *MemberDecode(Byte **bytes, Error *error) {
    VALUE *record = DecodeValue(bytes, error);
    if (*error != NULL) {
        goto returnError;
    }
    VALUE *field = DecodeValue(bytes, error);
    if (*error != NULL) {
        goto returnError;
    }
    return MemberCreate(record, field, error);

returnError:
    return NULL;
}

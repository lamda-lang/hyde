#include "RTValue.h"

void RTValueDealloc(RTValue value) {
  RTType type = 0;
  switch (type) {
  case TYPE_IDENTIFIER:
      RTIdentifierDealloc(IDENTIFIER(value));
      return;
  case TYPE_INTEGER:
      RTIntegerDealloc(INTEGER(value));
      return;
  case TYPE_LAMBDA:
      RTLambdaDealloc(LAMBDA(value));
      return;
  case TYPE_LIST:
      RTListDealloc(LIST(value));
      return;
  case TYPE_MAP:
      RTMapDealloc(MAP(value));
      return;
  case TYPE_STRING:
      RTStringDealloc(STRING(value));
      return;
  }
}

void RTValueMark(RTValue value) {
  value = NULL;
}

RTBool RTValueResetMark(RTValue value) {
  value = NULL;
  return TRUE;
}

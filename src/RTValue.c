#include "RTIdentifier.h"
#include "RTList.h"
#include "RTMemory.h"
#include "RTModule.h"
#include "RTString.h"
#include "RTValue.h"

struct RTValue {
  void *primitive;
  RTInteger8Bit type;
};

typedef enum {
  IDENTIFIER = 0,
  LIST = 1,
  MODULE = 2,
  STRING = 3
} RTType;

static inline RTValue RTValueCreate(void *primitive, RTType type) {
  return NULL;
}

RTValue RTValueCreateIdentifier(RTIdentifier id) {
  return RTValueCreate(id, IDENTIFIER);
}

RTValue RTValueCreateList(RTList list) {
  return RTValueCreate(list, LIST);
}

RTValue RTValueCreateModule(RTModule module) {
  return RTValueCreate(module, MODULE);
}

RTValue RTValueCreateString(RTString string) {
  return RTValueCreate(string, STRING);
}

RTIdentifier RTValueGetIdentifier(RTValue value) {
  return value->primitive;
}

RTList RTValueGetList(RTValue value) {
  return value->primitive;
}

RTModule RTValueGetModule(RTValue value) {
  return value->primitive;
}

RTString RTValueGetString(RTValue value) {
  return value->primitive;
}

void RTValueDealloc(RTValue value) {
  switch (value->type) {
    case IDENTIFIER:
      RTIdentifierDealloc(value->primitive);
      break;
    case LIST:
      RTListDealloc(value->primitive);
      break;
    case MODULE:
      RTModuleDealloc(value->primitive);
      break;
    case STRING:
      RTStringDealloc(value->primitive);
      break;
  }
  RTMemoryDealloc(value);
}

RTInteger32Bit RTValueHash(RTValue value) {
  switch (value->type) {
    case IDENTIFIER:
      return RTIdentifierHash(value->primitive);
    case LIST:
      return RTListHash(value->primitive);
    case MODULE:
      return RTModuleHash(value->primitive);
    case STRING:
      return RTStringHash(value->primitive);
  }
}

RTBool RTValueEqual(RTValue value, RTValue other) {
  if (value->type != other->type) {
    return FALSE;
  }
  switch (value->type) {
    case IDENTIFIER:
      return RTIdentifierEqual(value->primitive, other->primitive);
    case LIST:
      return RTListEqual(value->primitive, other->primitive);
    case MODULE:
      return RTModuleEqual(value->primitive, other->primitive);
    case STRING:
      return RTStringEqual(value->primitive, other->primitive);
  }
}

#ifdef RT_VALUE_TEST

int main(void) {

}

#endif

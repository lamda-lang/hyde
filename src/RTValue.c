#include "RTIdentifier.h"
#include "RTList.h"
#include "RTMemory.h"
#include "RTModule.h"
#include "RTString.h"
#include "RTValue.h"

struct RTValue {
  void *object;
  RTInteger8Bit type;
};

typedef enum {
  IDENTIFIER = 0,
  LIST = 1,
  MODULE = 2,
  STRING = 3
} RTType;

static inline void Dealloc(void *object, RTType type) {
}

RTValue RTValueCreate() {
  RTValue value = RTMemoryAlloc(sizeof(struct RTValue));
  if (value == NULL) {
    return NULL;
  }
  value->object = NULL;
  return value;
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
  return value->object;
}

RTList RTValueGetList(RTValue value) {
  return value->object;
}

RTModule RTValueGetModule(RTValue value) {
  return value->object;
}

RTString RTValueGetString(RTValue value) {
  return value->object;
}

void RTValueDealloc(RTValue value) {
  if (value->object == NULL) {
    return;
  }
  switch (type) {
  case IDENTIFIER:
    RTIdentifierDealloc(object);
    return;
  case LIST:
    RTListDealloc(object);
    return;
  case MODULE:
    RTModuleDealloc(object);
    return;
  case STRING:
    RTStringDealloc(object);
    return;
  }
}

RTInteger32Bit RTValueHash(RTValue value, RTBool recursive) {
  switch (value->type) {
  case IDENTIFIER:
    return RTIdentifierHash(value->object);
  case LIST:
    return RTListHash(value->object, recursive);
  case MODULE:
    return RTModuleHash(value->object, recursive);
  case STRING:
    return RTStringHash(value->object);
  }
}

RTBool RTValueEqual(RTValue value, RTValue other) {
  if (value->type != other->type) {
    return FALSE;
  }
  switch (value->type) {
  case IDENTIFIER:
    return RTIdentifierEqual(value->object, other->object);
  case LIST:
    return RTListEqual(value->object, other->object);
  case MODULE:
    return RTModuleEqual(value->object, other->object);
  case STRING:
    return RTStringEqual(value->object, other->object);
  }
}

#ifdef RT_VALUE_TEST

int main(void) {

}

#endif

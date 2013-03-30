#include "RTIdentifier.h"
#include "RTList.h"
#include "RTMemory.h"
#include "RTModule.h"
#include "RTString.h"
#include "RTValue.h"

struct RTValue {
  RTPrimitive primitive;
  RTInteger8Bit type;
};

typedef enum {
  IDENTIFIER = 0,
  LIST = 1,
  MODULE = 2,
  STRING = 3
} RTType;

RTValue RTValueCreate() {
  return RTMemoryAlloc(sizeof(struct RTValue));
}

void RTValueDealloc(RTValue value,  RTBool recursive) {
  if (recursive == TRUE) {
    switch (value->type) {
    case IDENTIFIER:
      RTIdentifierDealloc(value->primitive.id);
      break;
    case LIST:
      RTListDealloc(value->primitive.list);
      break;
    case MODULE:
      RTModuleDealloc(value->primitive.module);
      break;
    case STRING:
      RTStringDealloc(value->primitive.string);
      break;
    }
  }
  RTMemoryDealloc(value);
}

void RTValueSetIdentifier(RTValue value, RTIdentifier id) {
  value->primitive.id = id;
  value->type = IDENTIFIER;
}

void RTValueSetList(RTValue value, RTList list) {
  value->primitive.list = list;
  value->type = LIST;
}

void RTValueSetModule(RTValue value, RTModule module) {
  value->primitive.module = module;
  value->type = MODULE;
}

void RTValueSetString(RTValue value, RTString string) {
  value->primitive.string = string;
  value->type = STRING;
}

RTInteger32Bit RTValueHash(RTValue value, RTBool recursive) {
  switch (value->type) {
  case IDENTIFIER:
    return RTIdentifierHash(value->primitive.id);
  case LIST:
    return RTListHash(value->primitive.list, recursive);
  case MODULE:
    return RTModuleHash(value->primitive.module, recursive);
  case STRING:
    return RTStringHash(value->primitive.string);
  }
}

RTBool RTValueEqual(RTValue value, RTValue other) {
  if (value->type != other->type) {
    return FALSE;
  }
  switch (value->type) {
  case IDENTIFIER:
    return RTIdentifierEqual(value->primitive.id, other->primitive.id);
  case LIST:
    return RTListEqual(value->primitive.list, other->primitive.list);
  case MODULE:
    return RTModuleEqual(value->primitive.module, other->primitive.module);
  case STRING:
    return RTStringEqual(value->primitive.string, other->primitive.string);
  }
}

#ifdef RT_VALUE_TEST

int main(void) {

}

#endif

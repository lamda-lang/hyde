#include "RTIdentifier.h"
#include "RTList.h"
#include "RTMemory.h"
#include "RTModule.h"
#include "RTPrimitive.h"
#include "RTString.h"

struct RTPrimitive {
  void *object;
  RTType type;
};

static RTDealloc dealloc[] = {
  [IDENTIFIER] = RTIdentifierDealloc,
  [LIST] = RTListDealloc,
  [MODULE] = RTModuleDealloc,
  [STRING] = RTStringDealloc
};

static RTHash hash[] = {
  [IDENTIFIER] = RTIdentifierHash,
  [LIST] = RTListHash,
  [MODULE] = RTModuleHash,
  [STRING] = RTStringHash
};

static RTEqual equal[] = {
  [IDENTIFIER] = RTIdentifierEqual,
  [LIST] = RTListEqual,
  [MODULE] = RTModuleEqual,
  [STRING] = RTStringEqual
};

RTPrimitive RTPrimitiveCreate(void *object, RTType type) {
  if (object == NULL) {
    return NULL;
  }
  RTPrimitive primitive = RTMemoryAlloc(sizeof(struct RTPrimitive));
  if (primitive == NULL) {
    dealloc[type](object);
  }
  primitive->type = type;
  primitive->object = object;
  return primitive;
}

void RTPrimitiveDealloc(RTPrimitive primitive) {
  dealloc[primitive->type](primitive->object);
  RTMemoryDealloc(primitive);
}

void *RTPrimitiveGetObject(RTPrimitive primitive) {
  return primitive->object;
}

RTInteger32Bit RTPrimitiveHash(RTPrimitive primitive) {
  return hash[primitive->type](primitive->object);
}

RTBool RTPrimitiveEqual(RTPrimitive object, RTPrimitive other) {
  return object->type == other->type && equal[object->type](object, other);
}

#ifdef RT_PRIMITIVE_TEST

int main(void) {

}

#endif

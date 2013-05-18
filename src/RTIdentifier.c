#include "RTIdentifier.h"

struct RTIdentifier {
  RTValue base;
  RTInteger8Bit length;
  RTInteger8Bit codepoint[];
};

static inline RTIdentifier *Create(RTInteger8Bit length) {
  RTSize size = sizeof(struct RTIdentifier) + sizeof(RTInteger8Bit) * length;
  RTIdentifier *id = RTMemoryAlloc(size);
  if (id == NULL) {
    return NULL;
  }
  id->base = RTValueInit(RTTypeIdentifier, RTFlagNone);
  id->length = length;
  return id;
}

RTValue *RTIdentifierValueBridge(RTIdentifier *id) {
  return (RTValue *)id;
}

void RTIdentifierDealloc(RTIdentifier *id) {
  RTMemoryDealloc(id);
}

RTIdentifier *RTIdentifierDecode(RTByte **data) {
  RTInteger8Bit length = RTDecodeInteger8Bit(data);
  RTIdentifier *id = Create(length);
  if (id == NULL) {
    return NULL;
  }
  for (RTInteger8Bit index = 0; index < length; index += 1) {
    id->codepoint[index] = RTDecodeInteger8Bit(data);
  }
  return id;
}

bool RTIdentifierEqual(RTIdentifier *id, RTIdentifier *other) {
  RTSize size = sizeof(RTInteger8Bit) * id->length;
  return id->length == other->length &&
         RTMemoryEqual(id->codepoint, other->codepoint, size);
}

RTInteger64Bit RTIdentifierHash(RTIdentifier *id) {
  return id->length;
}

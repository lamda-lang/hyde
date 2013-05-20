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
    goto error;
  }
  id->base = RTValueInit(RTTypeIdentifier, RTFlagNone);
  id->length = length;
  return id;

error:
  return NULL;
}

RTValue *RTIdentifierValueBridge(RTIdentifier *id) {
  return (RTValue *)id;
}

void RTIdentifierDealloc(RTValue *id) {
  RTMemoryDealloc(id);
}

RTIdentifier *RTIdentifierDecode(RTByte **data) {
  RTInteger8Bit length = RTDecodeInteger8Bit(data);
  RTIdentifier *id = Create(length);
  if (id == NULL) {
    goto error;
  }
  for (RTInteger8Bit index = 0; index < length; index += 1) {
    id->codepoint[index] = RTDecodeInteger8Bit(data);
  }
  return id;

error:
  return NULL;
}

RTInteger64Bit RTIdentifierHash(RTValue *id_RTIdentifier) {
  RTIdentifier *id = RTValueIdentifierBridge(id_RTIdentifier);
  return id->length;
}

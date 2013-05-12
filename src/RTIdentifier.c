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
  id->base = RTValueInit(RTTypeIdentifier);
  id->length = length;
  return id;
}

RTValue *RTIdentifierValueBridge(RTIdentifier *id) {
  return (RTValue *)id;
}

void RTIdentifierDealloc(RTIdentifier *id) {
  RTMemoryDealloc(id);
}

RTSize RTIdentifierEncodingSize(RTIdentifier *id) {
  return sizeof(RTInteger8Bit) + sizeof(RTInteger8Bit) * id->length;
}

void RTIdentifierEncode(RTIdentifier *id, RTByte *buffer) {
  RTByte *alias = buffer;
  RTEncodeInteger8Bit(id->length, &alias);
  for (RTInteger8Bit index = 0; index < id->length; index +=1) {
    RTEncodeInteger8Bit(id->codepoint[index], &alias);
  }
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

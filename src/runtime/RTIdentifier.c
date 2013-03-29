#include "RTIdentifier.h"
#include "RTMemory.h"

struct RTIdentifier {
  RTInteger8Bit length;
  RTByte codepoint[];
};

RTIdentifier RTIdentifierCreate(RTInteger8Bit length) {
  RTSize size = sizeof(struct RTIdentifier) + length;
  RTIdentifier id = RTMemoryAlloc(size);
  if (id == NULL) {
    return NULL;
  }
  id->length = length;
  return id;
}

void RTIdentifierDealloc(RTIdentifier id) {
  RTMemoryDealloc(id);
}

void RTIdentifierDecode(RTIdentifier id, RTByte **data, RTInteger8Bit length) {
  RTMemoryCopy(*data, id->codepoint, length);
  *data += length;
}

RTBool RTIdentifierEqual(RTIdentifier id, RTIdentifier other) {
  return id->length == other->length && RTMemoryCompare(id->codepoint, other->codepoint, id->length);
}

RTInteger32Bit RTIdentifierHash(RTIdentifier id) {
  RTInteger32Bit hash = id->length;
  for (RTIndex index = 0; index < id->length; index += 1) {
    hash += id->codepoint[index];
  }
  return hash;
}

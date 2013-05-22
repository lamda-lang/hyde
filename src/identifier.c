#include "identifier.h"

struct Identifier {
  Value base;
  Integer8Bit length;
  Integer8Bit codepoint[];
};

static inline Identifier *Create(Integer8Bit length) {
  Size size = sizeof(struct Identifier) + sizeof(Integer8Bit) * length;
  Identifier *id = MemoryAlloc(size);
  if (id == NULL) {
    goto error;
  }
  id->base = ValueInit(TypeIdentifier, FlagNone);
  id->length = length;
  return id;

error:
  return NULL;
}

Value *IdentifierValueBridge(Identifier *id) {
  return (Value *)id;
}

void IdentifierDealloc(Value *id) {
  MemoryDealloc(id);
}

Identifier *IdentifierDecode(Byte **data) {
  Integer8Bit length = DecodeInteger8Bit(data);
  Identifier *id = Create(length);
  if (id == NULL) {
    goto error;
  }
  for (Integer8Bit index = 0; index < length; index += 1) {
    id->codepoint[index] = DecodeInteger8Bit(data);
  }
  return id;

error:
  return NULL;
}

Integer64Bit IdentifierHash(Value *id_Identifier) {
  Identifier *id = ValueIdentifierBridge(id_Identifier);
  return id->length;
}

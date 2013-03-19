#include "RTHash.h"
#include "RTMemory.h"
#include "RTModule.h"
#include "RTPrimitive.h"

union RTElement {
  RTPrimitive object;
  RTInteger32Bit index;
};

struct RTPair {
  union RTElement key;
  union RTElement value;
};

struct RTModule {
  RTInteger32Bit length;
  struct RTPair pair[];
};

static inline RTInteger32Bit RTModuleHashIndex(RTModule module, RTInteger32Bit hash) {
  return hash % (module->length >> 1);
}

static inline void RTModuleSetValueForKey(RTModule module, RTPrimitive value, RTPrimitive key) {
  RTInteger32Bit hash = RTPrimitiveHash(key);
  RTInteger32Bit index = RTModuleHashIndex(module, hash);
  while(module->pair[index].key.object != NULL) {
    index = RTModuleHashIndex(module, index + 1);
  }
  module->pair[index].key.object = key;
  module->pair[index].value.object = value;
}

RTModule RTModuleCreate(RTInteger32Bit capacity) {
  RTInteger32Bit length = capacity * 2;
  RTSize size = sizeof(struct RTModule) + SIZE_OF(struct RTPair, length);
  RTModule module = RTMemoryAlloc(size);
  if (module == NULL) {
    return NULL;
  }
  module->length = length;
  return module;
}

void RTModuleDealloc(void *module_RTModule) {
  RTMemoryDealloc(module_RTModule);
}

void RTModuleSetKeyValueIndexAtIndex(RTModule module, RTInteger32Bit keyIndex, RTInteger32Bit valueIndex, RTInteger32Bit index) {
  module->pair[index].key.index = keyIndex;
  module->pair[index].value.index = valueIndex;
}

void RTModuleFetch(RTModule module, RTPrimitive *reg) {
  RTInteger32Bit length = module->length;
  struct RTPair pair[length];
  RTMemoryCopy(module->pair, pair, SIZE_OF(struct RTPair, length));
  for (RTIndex index = 0; index < module->length; index += 1) {
    module->pair[index].key.object = NULL;
  }
  for (RTIndex index = 0; index < length; index += 1) {
    RTPrimitive key = reg[module->pair[index].key.index];
    RTPrimitive value = reg[module->pair[index].value.index];
    RTModuleSetValueForKey(module, value, key);
  }
}

RTPrimitive RTModuleGetValueForKey(RTModule module, RTPrimitive key) {
  RTInteger32Bit hash = RTPrimitiveHash(key);
  RTInteger32Bit index = RTModuleHashIndex(module, hash);
  RTPrimitive moduleKey = module->pair[index].key.object;
  while (key != NULL) {
    if (RTPrimitiveEqual(key, moduleKey)) {
      return module->pair[index].value.object;
    }
    index = RTModuleHashIndex(module, index + 1);
  }
  return NULL;
}

RTInteger32Bit RTModuleHash(void *module_RTModule) {
  RTModule module = module_RTModule;
  RTInteger32Bit hash = RTHashValue(&module->length, sizeof(RTInteger32Bit));
  for (RTIndex index = 0; index < module->length; index += 1) {
    RTPrimitive key = module->pair[index].key.object;
    RTPrimitive value = module->pair[index].value.object;
    if (key != NULL) {
      hash += RTPrimitiveHash(key) + RTPrimitiveHash(value);
    }
  }
  return hash;
}

RTBool RTModuleEqual(void *module_RTModule, void *other_RTModule) {
  RTModule module = module_RTModule;
  RTModule other = other_RTModule;
  if (module->length != other->length) {
    return FALSE;
  }
  for (RTIndex index = 0; index < module->length; index += 1) {
    RTPrimitive moduleKey = module->pair[index].key.object;
    RTPrimitive moduleValue = module->pair[index].value.object;
    RTPrimitive otherKey = other->pair[index].key.object;
    RTPrimitive otherValue = other->pair[index].value.object;
    if (moduleKey != NULL && otherKey != NULL) {
      return RTPrimitiveEqual(moduleKey, otherKey) && RTPrimitiveEqual(moduleValue, otherValue);
    }
  }
  return TRUE;
}

#ifdef RT_MODULE_TEST

#define CAPACITY 8

RTModule FIXTURE_Module(void) {
  RTModule module = RTModuleCreate(CAPACITY);
  REQUIRE(module != NULL);
  return module;
}

RTPrimitive FIXTURE_Primitive(void) {
  RTModule module = RTModuleCreate(CAPACITY);
  RTPrimitive value = RTPrimitiveCreate(module, MODULE);
  REQUIRE(value != NULL);
  return value;
}

void TEST_RTModuleCreate_Success(void) {
  RTPrimitive object = FIXTURE_Primitive();
  RTModule module = RTModuleCreate(CAPACITY);
  REQUIRE(module != NULL);
  ASSERT(module->length == CAPACITY * 2);
  for (RTIndex index = 0; index < module->length; index += 1) {
    module->pair[index].value.object = object;
    ASSERT(module->pair[index].key.object == NULL);
    ASSERT(module->pair[index].value.object == object);
  }
}

void TEST_RTModuleDealloc_Success(void) {
  RTModule module = FIXTURE_Module();
  RTModuleDealloc(module);
}

void TEST_RTModuleSetPrimitiveForIdentifier_Success(void) {
  RTModule module = FIXTURE_Module();
  RTPrimitive value = FIXTURE_Primitive();
  RTModuleSetValueForKey(module, value, value);
  RTInteger32Bit hash = RTPrimitiveHash(value);
  RTInteger32Bit index = RTModuleHashIndex(module, hash);
  ASSERT(module->pair[index].value.object == value);
}

void TEST_RTModuleGetPrimitiveForIdentifier_Success(void) {
  RTModule module = FIXTURE_Module();
  RTPrimitive value = FIXTURE_Primitive();
  RTInteger32Bit hash = RTPrimitiveHash(value);
  RTInteger32Bit index = RTModuleHashIndex(module, hash);
  module->pair[index].value.object = value;
  ASSERT(RTModuleGetValueForKey(module, value) == value);
}

int main(void) {
  TEST_RTModuleCreate_Success();
  TEST_RTModuleDealloc_Success();
  TEST_RTModuleSetPrimitiveForIdentifier_Success();
  TEST_RTModuleGetPrimitiveForIdentifier_Success();
}

#endif

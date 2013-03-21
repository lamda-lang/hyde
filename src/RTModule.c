#include "RTMemory.h"
#include "RTModule.h"
#include "RTValue.h"

union RTElement {
  RTValue value;
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

static inline void RTModuleSetValueForKey(RTModule module, RTValue value, RTValue key) {
  RTInteger32Bit hash = RTValueHash(key);
  RTInteger32Bit index = RTModuleHashIndex(module, hash);
  while(module->pair[index].key.value != NULL) {
    index = RTModuleHashIndex(module, index + 1);
  }
  module->pair[index].key.value = key;
  module->pair[index].value.value = value;
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

void RTModuleDealloc(RTModule module) {
  RTMemoryDealloc(module);
}

void RTModuleSetKeyValueIndexAtIndex(RTModule module, RTInteger32Bit keyIndex, RTInteger32Bit valueIndex, RTInteger32Bit index) {
  module->pair[index].key.index = keyIndex;
  module->pair[index].value.index = valueIndex;
}

void RTModuleFetch(RTModule module, RTValue *reg) {
  RTInteger32Bit length = module->length;
  struct RTPair pair[length];
  RTMemoryCopy(module->pair, pair, SIZE_OF(struct RTPair, length));
  for (RTIndex index = 0; index < module->length; index += 1) {
    module->pair[index].key.value = NULL;
  }
  for (RTIndex index = 0; index < length; index += 1) {
    RTValue key = reg[module->pair[index].key.index];
    RTValue value = reg[module->pair[index].value.index];
    RTModuleSetValueForKey(module, value, key);
  }
}

RTValue RTModuleGetValueForKey(RTModule module, RTValue key) {
  RTInteger32Bit hash = RTValueHash(key);
  RTInteger32Bit index = RTModuleHashIndex(module, hash);
  RTValue moduleKey = module->pair[index].key.value;
  while (key != NULL) {
    if (RTValueEqual(key, moduleKey)) {
      return module->pair[index].value.value;
    }
    index = RTModuleHashIndex(module, index + 1);
  }
  return NULL;
}

RTInteger32Bit RTModuleHash(RTModule module) {
  RTInteger32Bit hash = module->length;
  for (RTIndex index = 0; index < module->length; index += 1) {
    RTValue key = module->pair[index].key.value;
    RTValue value = module->pair[index].value.value;
    if (key != NULL) {
      hash += RTValueHash(key) + RTValueHash(value);
    }
  }
  return hash;
}

RTBool RTModuleEqual(RTModule module, RTModule other) {
  if (module->length != other->length) {
    return FALSE;
  }
  for (RTIndex index = 0; index < module->length; index += 1) {
    RTValue moduleKey = module->pair[index].key.value;
    RTValue moduleValue = module->pair[index].value.value;
    RTValue otherKey = other->pair[index].key.value;
    RTValue otherValue = other->pair[index].value.value;
    if (moduleKey != NULL && otherKey != NULL) {
      return RTValueEqual(moduleKey, otherKey) && RTValueEqual(moduleValue, otherValue);
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

RTValue FIXTURE_Value(void) {
  RTModule module = RTModuleCreate(CAPACITY);
  RTValue value = RTValueCreateModule(module);
  REQUIRE(value != NULL);
  return value;
}

void TEST_RTModuleCreate_Success(void) {
  RTValue value = FIXTURE_Value();
  RTModule module = RTModuleCreate(CAPACITY);
  REQUIRE(module != NULL);
  ASSERT(module->length == CAPACITY * 2);
  for (RTIndex index = 0; index < module->length; index += 1) {
    module->pair[index].value.value = value;
    ASSERT(module->pair[index].key.value == NULL);
    ASSERT(module->pair[index].value.value == value);
  }
}

void TEST_RTModuleDealloc_Success(void) {
  RTModule module = FIXTURE_Module();
  RTModuleDealloc(module);
}

void TEST_RTModuleSetValueForIdentifier_Success(void) {
  RTModule module = FIXTURE_Module();
  RTValue value = FIXTURE_Value();
  RTModuleSetValueForKey(module, value, value);
  RTInteger32Bit hash = RTValueHash(value);
  RTInteger32Bit index = RTModuleHashIndex(module, hash);
  ASSERT(module->pair[index].value.value == value);
}

void TEST_RTModuleGetValueForIdentifier_Success(void) {
  RTModule module = FIXTURE_Module();
  RTValue value = FIXTURE_Value();
  RTInteger32Bit hash = RTValueHash(value);
  RTInteger32Bit index = RTModuleHashIndex(module, hash);
  module->pair[index].value.value = value;
  ASSERT(RTModuleGetValueForKey(module, value) == value);
}

int main(void) {
  TEST_RTModuleCreate_Success();
  TEST_RTModuleDealloc_Success();
  TEST_RTModuleSetValueForIdentifier_Success();
  TEST_RTModuleGetValueForIdentifier_Success();
}

#endif

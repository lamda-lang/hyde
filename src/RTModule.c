#include "RTMemory.h"
#include "RTModule.h"
#include "RTValue.h"

struct RTElement {
  RTValue key;
  RTValue value;
};

struct RTModule {
  RTInteger32Bit length;
  struct RTElement element[];
};

static inline RTInteger32Bit RTModuleIndex(RTModule module, RTValue value, RTInteger32Bit offset) {
  return RTValueHash(value, TRUE) + offset % module->length;
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

void RTModuleSetValueForKey(RTModule module, RTValue value, RTValue key) {
  RTInteger32Bit index = RTModuleHashIndex(module, key, 0);
  while(module->element[index].key != NULL) {
    index = RTModuleHashIndex(module, key, index);
  }
  module->element[index].key = key;
  module->element[index].value = value;
}

RTValue RTModuleGetValueForKey(RTModule module, RTValue key) {
  /* missing */
}

RTInteger32Bit RTModuleHash(RTModule module, RTBool recursive) {
  if (recursive == FALSE) {
    return module->length;
  }
  RTInteger32Bit hash = module->length;
  for (RTIndex index = 0; index < module->length; index += 1) {
    RTValue key = module->element[index].key;
    RTValue value = module->element[index].value;
    if (key != NULL) {
      hash += RTValueHash(key, FALSE) + RTValueHash(value, FALSE);
    }
  }
  return hash;
}

RTBool RTModuleEqual(RTModule module, RTModule other) {
  if (module->length != other->length) {
    return FALSE;
  }
  for (RTIndex index = 0; index < module->length; index += 1) {
    RTValue moduleKey = module->element[index].key;
    if (moduleKey != NULL && RTModuleGetValueForKey(other, moduleKey) != NULL) {
/**/      
    }
  }
  return TRUE;
}

#ifdef RT_MODULE_TEST

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
    module->element[index].value = value;
    ASSERT(module->element[index].key == NULL);
    ASSERT(module->element[index].value == value);
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
  RTInteger32Bit hash = RTValueHash(value, TRUE);
  RTInteger32Bit index = RTModuleHashIndex(module, hash);
  ASSERT(module->element[index].value == value);
}

void TEST_RTModuleGetValueForIdentifier_Success(void) {
  RTModule module = FIXTURE_Module();
  RTValue value = FIXTURE_Value();
  RTInteger32Bit hash = RTValueHash(value, TRUE);
  RTInteger32Bit index = RTModuleHashIndex(module, hash);
  module->element[index].value = value;
  ASSERT(RTModuleGetValueForKey(module, value) == value);
}

int main(void) {
  TEST_RTModuleCreate_Success();
  TEST_RTModuleDealloc_Success();
  TEST_RTModuleSetValueForIdentifier_Success();
  TEST_RTModuleGetValueForIdentifier_Success();
}

#endif

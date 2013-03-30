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
  RTSize size = sizeof(struct RTModule) + SIZE_OF(struct RTElement, length);
  RTModule module = RTMemoryAlloc(size);
  if (module == NULL) {
    return NULL;
  }
  module->length = length;
  for (RTIndex index = 0; index < length; index += 1) {
    module->element[index].key = NULL;
    module->element[index].value = NULL;
  }
  return module;
}

void RTModuleDealloc(RTModule module) {
  RTMemoryDealloc(module);
}

void RTModuleSetValueForKey(RTModule module, RTValue value, RTValue key) {
  RTInteger32Bit index = RTModuleIndex(module, key, 0);
  while (module->element[index].key != NULL) {
    index = RTModuleIndex(module, key, index);
  }
  module->element[index].key = key;
  module->element[index].value = value;
}

RTValue RTModuleGetValueForKey(RTModule module, RTValue key) {
  RTInteger32Bit index = RTModuleIndex(module, key, 0);
  while (module->element[index].key != NULL && RTValueEqual(key, module->element[index].key) == FALSE) {
    index = RTModuleIndex(module, key, index);
  }
  return module->element[index].value;
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
    if (moduleKey != NULL) {
      RTValue moduleValue = RTModuleGetValueForKey(module, moduleKey);
      RTValue otherValue = RTModuleGetValueForKey(other, moduleKey);
      if (otherValue == NULL || RTValueEqual(moduleValue, otherValue) == FALSE) {
	return  FALSE;
      }
    }
  }
  return TRUE;
}

#ifdef RT_MODULE_TEST

int main(void) {

}

#endif

#include "RTBoolean.h"

struct RTBoolean {
  RTBase base;
  RTBool value;
};

RTValue RTBooleanValueBridge(RTBoolean boolean) {
  return (RTValue)boolean;
}

RTBoolean RTBooleanCreate(RTBool value) {
  RTSize size = sizeof(struct RTBoolean);
  RTBoolean boolean = RTMemoryAlloc(size);
  if (boolean == NULL) {
    return NULL;
  }
  boolean->base = RTBaseInit(RTTypeBoolean, RTFlagNone);
  boolean->value = value;
  return boolean;
}

void RTBooleanDealloc(RTBoolean boolean) {
  RTMemoryDealloc(boolean);
}

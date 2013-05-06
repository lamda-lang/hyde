#include "RTBoolean.h"

struct RTBoolean {
  RTBase base;
  RTBool bool;
};

RTValue RTBooleanValueBridge(RTBoolean boolean) {
  return (RTValue)boolean;
}

RTBoolean RTBooleanCreate(RTBool bool) {
  RTSize size = sizeof(struct RTBoolean);
  RTBoolean boolean = RTMemoryAlloc(size);
  if (boolean == NULL) {
    return NULL;
  }
  boolean->base = RTBaseInit(RTTypeBoolean, RTFlagNone);
  boolean->bool = bool;
  return boolean;
}

void RTBooleanDealloc(RTBoolean boolean) {
  RTMemoryDealloc(boolean);
}

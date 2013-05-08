#include "RTBoolean.h"

struct RTBoolean {
  RTBase base;
  RTBool truth;
};

RTValue RTBooleanValueBridge(RTBoolean boolean) {
  return (RTValue)boolean;
}

RTBoolean RTBooleanCreate(RTBool truth) {
  RTSize size = sizeof(struct RTBoolean);
  RTBoolean boolean = RTMemoryAlloc(size);
  if (boolean == NULL) {
    return NULL;
  }
  boolean->base = RTBaseInit(RTTypeBoolean, RTFlagNone);
  boolean->truth = truth;
  return boolean;
}

void RTBooleanDealloc(RTBoolean boolean) {
  RTMemoryDealloc(boolean);
}

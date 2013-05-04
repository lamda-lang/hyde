#include "RTBoolean.h"

struct RTBoolean {
  RTBase base;
};

struct RTBoolean TrueSingleton = {
  .base = 0
};

struct RTBoolean FalseSingleton = {
  .base = 0
};

const RTBoolean RTBooleanTrueSingleton = &TrueSingleton;
const RTBoolean RTBooleanFalseSingleton = &FalseSingleton;

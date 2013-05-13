#include "RTCollect.h"


void RTCollectValue(RTValue *value) {
  if (RTValueFlagSet(value, RTFlagMark)) {
    RTValueDealloc(value);
  }
}

void RTCollectRetainValue(RTValue *value) {
  if (!RTValueFlagSet(value, RTFlagRetain)) {
    RTValueSetFlag(value, RTFlagRetain, true);
    RTValueSetFlag(value, RTFlagMark, false);
    RTValueEnumerate(value, RTCollectRetainValue);
  }
  if (RTValueFlagSet(value, RTFlagRetain)) {
    RTValueSetFlag(value, RTFlagRetain, false);
    RTValueEnumerate(value, RTCollectReleaseValue);
  }
}

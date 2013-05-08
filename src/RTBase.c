#include "RTBase.h"

RTBase RTBaseInit(RTType type, RTFlag mask) {
  return type | mask;
}

RTType RTBaseGetType(RTBase base) {
  return base & 0XF;
}

RTBase RTBaseSetFlag(RTBase base, RTFlag flag, RTBool truth) {
  return truth ? base | flag : base & ~flag;
}

RTBool RTBaseFlagSet(RTBase base, RTFlag flag) {
  return (base & flag) == flag;
}

RTBool RTBaseFlagEqual(RTBase base, RTBase other, RTFlag flag) {
  return (base & flag) == (other & flag);
}

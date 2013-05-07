#include "RTBase.h"

RTBase RTBaseInit(RTType type, RTFlag mask) {
  return type | mask;
}

RTType RTBaseGetType(RTBase base) {
  return base & 0XF;
}

RTBase RTBaseSetFlag(RTBase base, RTFlag flag, RTBool value) {
  return value ? base | flag : base & ~flag;
}

RTBool RTBaseGetFlag(RTBase base, RTFlag flag) {
  return (base & flag) == flag;
}

RTBool RTBaseEqualFlag(RTBase base, RTBase other, RTFlag flag) {
  return (base & flag) == (other & flag);
}

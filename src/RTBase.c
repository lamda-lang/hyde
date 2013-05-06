#include "RTBase.h"

RTBase RTBaseInit(RTType type, RTFlag mask) {
  return type | mask;
}

RTType RTBaseGetType(RTBase base) {
  return base & 0XF0;
}

RTBase RTBaseSetFlag(RTBase base, RTFlag flag, RTBool bool) {
  return bool ? base | flag : base & ~flag;
}

RTBool RTBaseGetFlag(RTBase base, RTFlag flag) {
  return (base & flag) == flag;
}

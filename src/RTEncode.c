#include "RTEncode.h"

RTError RTEncodeInteger8Bit(RTInteger8Bit value, RTBuffer *buffer) {
  RTByte byte[] = {
    value >> 0 & 0XFF
  };
  return RTBufferAppend(buffer, byte, sizeof(value));
}

RTError RTEncodeInteger16Bit(RTInteger16Bit value, RTBuffer *buffer) {
  RTByte byte[] = {
    value >> 0 & 0XFF,
    value >> 8 & 0XFF
  };
  return RTBufferAppend(buffer, byte, sizeof(value));
}

RTError RTEncodeInteger32Bit(RTInteger32Bit value, RTBuffer *buffer) {
  RTByte byte[] = {
    value >> 0 & 0XFF,
    value >> 8 & 0XFF,
    value >> 16 & 0XFF,
    value >> 24 & 0XFF
  };
  return RTBufferAppend(buffer, byte, sizeof(value));
}

RTError RTEncodeInteger64Bit(RTInteger64Bit value, RTBuffer *buffer) {
  RTByte byte[] = {
    value >> 0 & 0XFF,
    value >> 8 & 0XFF,
    value >> 16 & 0XFF,
    value >> 24 & 0XFF,
    value >> 32 & 0XFF,
    value >> 40 & 0XFF,
    value >> 48 & 0XFF,
    value >> 56 & 0XFF
  };
  return RTBufferAppend(buffer, byte, sizeof(value));
}

RTError RTEncodeVBRInteger32Bit(RTInteger32Bit value, RTBuffer *buffer) {
  value = 0;
  buffer = NULL;
  return RTErrorNone;
}

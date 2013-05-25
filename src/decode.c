#include "decode.h"

Integer8Bit DecodeInteger8Bit(Byte **bytes) {
  Integer8Bit value = **bytes;
  *bytes += 1;
  return value;
}

Integer16Bit DecodeInteger16Bit(Byte **bytes) {
  Byte *byte = *bytes;
  Integer16Bit value[] = {byte[0], byte[1]};
  value[1] <<= 8;
  *bytes += 2;
  return value[0] | value[1];
}

Integer32Bit DecodeInteger32Bit(Byte **bytes) {
  Byte *byte = *bytes;
  Integer32Bit value[] = {byte[0], byte[1], byte[2], byte[3]};
  value[1] <<= 8;
  value[2] <<= 16;
  value[3] <<= 24;
  *bytes += 4;
  return value[0] | value[1] | value[2] | value[3];
}

Integer64Bit DecodeInteger64Bit(Byte **bytes) {
  Byte *byte = *bytes;
  Integer64Bit value[] = {byte[0], byte[1], byte[2], byte[3], byte[4], byte[5], byte[6], byte[7]};
  value[1] <<= 8;
  value[2] <<= 16;
  value[3] <<= 24;
  value[4] <<= 32;
  value[5] <<= 40;
  value[6] <<= 48;
  value[7] <<= 56;
  *bytes += 8;
  return value[0] | value[1] | value[2] | value[3] | value[4] | value[5] | value[6] | value[7];
}

Integer32Bit DecodeVBRInteger32Bit(Byte **bytes) {
  Integer32Bit result = 0;
  bool more = true;
  for (Index index = 0; more; index += 1) {
    Integer32Bit value = (**bytes & 0X7F);
    result |= value << index * 7;
    more = (**bytes & 0X80) != 0; 
    *bytes += 1;
  }
  return result;
}

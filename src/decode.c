#include "decode.h"

Integer8Bit DecodeInteger8Bit(Byte **data) {
  Byte *alias = *data;
  Integer8Bit value = alias[0];
  *data += 1;
  return value;
}

Integer16Bit DecodeInteger16Bit(Byte **data) {
  Byte *alias = *data;
  Integer16Bit value[] = {alias[0], alias[1]};
  *data += 2;
  value[1] <<= 8;
  return value[0] | value[1];
}

Integer32Bit DecodeInteger32Bit(Byte **data) {
  Byte *alias = *data;
  Integer32Bit value[] = {alias[0], alias[1], alias[2], alias[3]};
  *data += 4;
  value[1] <<= 8;
  value[2] <<= 16;
  value[3] <<= 24;
  return value[0] | value[1] | value[2] | value[3];
}

Integer64Bit DecodeInteger64Bit(Byte **data) {
  Byte *alias = *data;
  Integer64Bit value[] = {alias[0], alias[1], alias[2], alias[3], alias[4], alias[5], alias[6], alias[7]};
  *data += 8;
  value[1] <<= 8;
  value[2] <<= 16;
  value[3] <<= 24;
  value[4] <<= 32;
  value[5] <<= 40;
  value[6] <<= 48;
  value[7] <<= 56;
  return value[0] | value[1] | value[2] | value[3] | value[4] | value[5] | value[6] | value[7];
}

Integer32Bit DecodeVBRInteger32Bit(Byte **data) {
  Integer32Bit result = 0;
  bool more = true;
  for (Index index = 0; more; index += 1) {
    Integer32Bit value = (**data & 0X7F);
    result |= value << index * 7;
    more = (**data & 0X80) != 0; 
    *data += 1;
  }
  return result;
}

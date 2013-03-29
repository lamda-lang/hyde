#include "RTDecode.h"

RTInteger8Bit RTDecodeInteger8Bit(RTByte **data) {
  RTByte *alias = *data;
  RTInteger8Bit value = alias[0];
  *data += 1;
  return value;
}

RTInteger16Bit RTDecodeInteger16Bit(RTByte **data) {
  RTByte *alias = *data;
  RTInteger16Bit value[] = {alias[0], alias[1]};
  *data += 2;
  value[1] <<= 8;
  return value[0] | value[1];
}

RTInteger32Bit RTDecodeInteger32Bit(RTByte **data) {
  RTByte *alias = *data;
  RTInteger32Bit value[] = {alias[0], alias[1], alias[2], alias[3]};
  *data += 4;
  value[1] <<= 8;
  value[2] <<= 16;
  value[3] <<= 24;
  return value[0] | value[1] | value[2] | value[3];
}

RTInteger64Bit RTDecodeInteger64Bit(RTByte **data) {
  RTByte *alias = *data;
  RTInteger64Bit value[] = {alias[0], alias[1], alias[2], alias[3], alias[4], alias[5], alias[6], alias[7]};
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

RTInteger32Bit RTDecodeVBRInteger32Bit(RTByte **data) {
  RTInteger32Bit result = 0;
  RTBool flag = TRUE;
  for (RTIndex index = 0; flag == TRUE; index += 1) {
    RTInteger32Bit value = (**data & 0X7F);
    result |= value << index * 7;
    flag = (**data & 0X80) != 0; 
    *data += 1;
  }
  return result;
}

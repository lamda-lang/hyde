#include "RTEncode.h"

void RTEncodeInteger8Bit(RTInteger8Bit value, RTByte **data) {
  RTByte *alias = *data;
  alias[0] = value;
  *data += 1;
}

void RTEncodeInteger16Bit(RTInteger16Bit value, RTByte **data) {
  RTByte *alias = *data;
  alias[0] = value & 0XFF;
  alias[1] = value >> 8 & 0XFF;
  *data += 2;
}

void RTEncodeInteger32Bit(RTInteger32Bit value, RTByte **data) {
  RTByte *alias = *data;
  alias[0] = value & 0XFF;
  alias[1] = value >> 8 & 0XFF;
  alias[2] = value >> 16 & 0XFF;
  alias[3] = value >> 24 & 0XFF;
  *data += 4;
}

void RTEncodeInteger64Bit(RTInteger64Bit value, RTByte **data) {
  RTByte *alias = *data;
  alias[0] = value & 0XFF;
  alias[1] = value >> 8 & 0XFF;
  alias[2] = value >> 16 & 0XFF;
  alias[3] = value >> 24 & 0XFF;
  alias[4] = value >> 32 & 0XFF;
  alias[5] = value >> 40 & 0XFF;
  alias[6] = value >> 48 & 0XFF;
  alias[7] = value >> 56 & 0XFF;
  *data += 8;
}

#ifdef RT_ENCODE_TEST

int main(void) {

}

#endif

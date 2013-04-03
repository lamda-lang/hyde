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

static void TEST_RTEncodeInteger8Bit_AllBytesDistinct(void) {
  RTByte buffer[] = {0X00};
  RTByte *alias = buffer;
  RTEncodeInteger8Bit(0X01, &alias);
  ASSERT(buffer[0] == 0X01);
  ASSERT(alias == buffer + sizeof(buffer));
}

static void TEST_RTEncodeInteger16Bit_AllBytesDistinct(void) {
  RTByte buffer[] = {0X00, 0X00};
  RTByte *alias = buffer;
  RTEncodeInteger16Bit(0X0201, &alias);
  ASSERT(buffer[0] == 0X01);
  ASSERT(buffer[1] == 0X02);
  ASSERT(alias == buffer + sizeof(buffer));
}

static void TEST_RTEncodeInteger32Bit_AllBytesDistinct(void) {
  RTByte buffer[] = {0X00, 0X00, 0X00, 0X00};
  RTByte *alias = buffer;
  RTEncodeInteger32Bit(0X08040201, &alias);
  ASSERT(buffer[0] == 0X01);
  ASSERT(buffer[1] == 0X02);
  ASSERT(buffer[2] == 0X04);
  ASSERT(buffer[3] == 0X08);
  ASSERT(alias == buffer + sizeof(buffer));
}

static void TEST_RTEncodeInteger64Bit_AllBytesDistinct(void) {
  RTByte buffer[] = {0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00};
  RTByte *alias = buffer;
  RTEncodeInteger64Bit(0X8040201008040201, &alias);
  ASSERT(buffer[0] == 0X01);
  ASSERT(buffer[1] == 0X02);
  ASSERT(buffer[2] == 0X04);
  ASSERT(buffer[3] == 0X08);
  ASSERT(buffer[4] == 0X10);
  ASSERT(buffer[5] == 0X20);
  ASSERT(buffer[6] == 0X40);
  ASSERT(buffer[7] == 0X80);
  ASSERT(alias == buffer + sizeof(buffer));
}

int main(void) {
  TEST_RTEncodeInteger8Bit_AllBytesDistinct();
  TEST_RTEncodeInteger16Bit_AllBytesDistinct();
  TEST_RTEncodeInteger32Bit_AllBytesDistinct();
  TEST_RTEncodeInteger64Bit_AllBytesDistinct();
}

#endif

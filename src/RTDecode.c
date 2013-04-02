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

#ifdef RT_DECODE_TEST

static void TEST_RTDecodeInteger8Bit_AllBytesDistinct(void) {
  RTByte data[] = {0X01};
  RTByte *alias = data;
  ASSERT(RTDecodeInteger8Bit(&alias) == 0X01);
  ASSERT(alias == data + sizeof(data));
}

static void TEST_RTDecodeInteger16Bit_AllBytesDistinct(void) {
  RTByte data[] = {0X01, 0X02};
  RTByte *alias = data;
  ASSERT(RTDecodeInteger16Bit(&alias) == 0X0201);
  ASSERT(alias == data + sizeof(data));
}

static void TEST_RTDecodeInteger32Bit_AllBytesDistinct(void) {
  RTByte data[] = {0X01, 0X02, 0X04, 0X08};
  RTByte *alias = data;
  ASSERT(RTDecodeInteger32Bit(&alias) == 0X08040201);
  ASSERT(alias == data + sizeof(data));
}

static void TEST_RTDecodeInteger64Bit_AllBytesDistinct(void) {
  RTByte data[] = {0X01, 0X02, 0X04, 0X08, 0X10, 0X20, 0X40, 0X80};
  RTByte *alias = data;
  ASSERT(RTDecodeInteger64Bit(&alias) == 0X8040201008040201);
  ASSERT(alias == data + sizeof(data));
}

static void TEST_RTDecodeVBRInteger32Bit_AllBytesDistinct(void) {
  RTByte data[] = {0X81, 0X84, 0X90, 0X40};
  RTByte *alias = data;
  ASSERT(RTDecodeVBRInteger32Bit(&alias) == 0X08040201);
  ASSERT(alias == data + sizeof(data));
}

static void TEST_RTDecodeVBRInteger32Bit_OneByte(void) {
  RTByte data[] = {0X01};
  RTByte *alias = data;
  ASSERT(RTDecodeVBRInteger32Bit(&alias) == 0X01);
  ASSERT(alias == data + sizeof(data));
}

int main(void) {
  TEST_RTDecodeInteger8Bit_AllBytesDistinct();
  TEST_RTDecodeInteger16Bit_AllBytesDistinct();
  TEST_RTDecodeInteger32Bit_AllBytesDistinct();
  TEST_RTDecodeInteger64Bit_AllBytesDistinct();
  TEST_RTDecodeVBRInteger32Bit_AllBytesDistinct();
  TEST_RTDecodeVBRInteger32Bit_OneByte();
}

#endif

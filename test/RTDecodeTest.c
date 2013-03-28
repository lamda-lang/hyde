#include "RTDecode.c"

void TEST_RTDecodeInteger8Bit_AllBytesDistinct(void) {
  RTByte data[] = {0X01};
  RTByte *alias = data;
  ASSERT(RTDecodeInteger8Bit(&alias) == 0X01);
  ASSERT(alias == data + sizeof(data));
}

void TEST_RTDecodeInteger16Bit_AllBytesDistinct(void) {
  RTByte data[] = {0X01, 0X02};
  RTByte *alias = data;
  ASSERT(RTDecodeInteger16Bit(&alias) == 0X0201);
  ASSERT(alias == data + sizeof(data));
}

void TEST_RTDecodeInteger32Bit_AllBytesDistinct(void) {
  RTByte data[] = {0X01, 0X02, 0X04, 0X08};
  RTByte *alias = data;
  ASSERT(RTDecodeInteger32Bit(&alias) == 0X08040201);
  ASSERT(alias == data + sizeof(data));
}

void TEST_RTDecodeInteger64Bit_AllBytesDistinct(void) {
  RTByte data[] = {0X01, 0X02, 0X04, 0X08, 0X10, 0X20, 0X40, 0X80};
  RTByte *alias = data;
  ASSERT(RTDecodeInteger64Bit(&alias) == 0X8040201008040201);
  ASSERT(alias == data + sizeof(data));
}

void TEST_RTDecodeVBRInteger32Bit_AllBytesDistinct(void) {
  RTByte data[] = {0X81, 0X84, 0X90, 0X40};
  RTByte *alias = data;
  ASSERT(RTDecodeVBRInteger32Bit(&alias) == 0X08040201);
  ASSERT(alias == data + sizeof(data));
}

void TEST_RTDecodeVBRInteger32Bit_OneByte(void) {
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

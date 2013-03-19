#include "RTHash.h"

RTInteger32Bit RTHashValue(void *buffer, RTSize size) {
  RTInteger32Bit hash = 0;
  RTByte *data = buffer;
  for (RTIndex index = 0; index < size; index += 1) {
    hash = hash + data[index];
  }
  return hash;
}

#ifdef RT_HASH_TEST

void TEST_RTHashValue_AllBytesDistinct(void) {
  RTByte data[] = {0X01, 0X02, 0X04, 0X08, 0X10, 0X20, 0X40, 0X80};
  ASSERT(RTHashValue(data, sizeof(data)) == 0XFF);
}

int main(void) {
  TEST_RTHashValue_AllBytesDistinct();
}

#endif

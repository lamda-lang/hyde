#include "RTMemory.h"

void *RTMemoryAlloc(RTSize size) {
  return malloc(size);
}

void RTMemoryDealloc(void *buffer) {
  free(buffer);
}

void RTMemoryCopy(void *source, void *target, RTSize size) {
  memcpy(target, source, size);
}

RTBool RTMemoryCompare(void *buffer, void *other, RTSize size) {
  return memcmp(buffer, other, size) == 0;
}

#ifdef RT_MEMORY_TEST

void *FIXTURE_Buffer(void) {
  void *buffer = RTMemoryAlloc(8);
  REQUIRE(buffer != NULL);
  return buffer;
}

void TEST_RTMemoryAlloc_CheckReadWrite(void) {
  RTIndex *buffer = RTMemoryAlloc(SIZE_OF(RTIndex, 8));
  REQUIRE(buffer != NULL);
  for (RTIndex index = 0; index < 8; index += 1) {
    buffer[index] = index;
    ASSERT(buffer[index] == index);
  }
}

void TEST_RTMemoryDealloc_ValidPointer(void) {
  void *buffer = FIXTURE_Buffer();
  RTMemoryDealloc(buffer);
}

void TEST_RTMemoryDealloc_CheckNULL(void) {
  RTMemoryDealloc(NULL);
}

void TEST_RTMemoryCopy_CheckSourceTarget(void) {
  RTByte data[] = {0X01};
  RTByte buffer[] = {0X02};
  RTMemoryCopy(data, buffer, sizeof(data));
  ASSERT(data[0] == 0X01);
  ASSERT(buffer[0] == 0X01);
}

void TEST_RTMemoryCopy_CheckBoundsZeroSize(void) {
  RTByte data[] = {0X01};
  RTByte buffer[] = {0X02};
  RTMemoryCopy(data, buffer, 0);
  ASSERT(buffer[0] == 0X02);
}

void TEST_RTMemoryCopy_CheckBounds(void) {
  RTByte data[] = {0X01, 0X02};
  RTByte buffer[] = {0X04, 0X08};
  RTMemoryCopy(data, buffer, 1);
  ASSERT(buffer[0] == 0X01);
  ASSERT(buffer[1] == 0X08);
}

void TEST_RTMemoryCompare_EqualBuffers(void) {
  RTByte buffer[] = {0X01};
  RTByte other[] = {0X01};
  ASSERT(RTMemoryCompare(buffer, other, sizeof(buffer)) == TRUE);
}

void TEST_RTMemoryCompare_UnequalBuffers(void) {
  RTByte buffer[] = {0X01};
  RTByte other[] = {0X02};
  ASSERT(RTMemoryCompare(buffer, other, sizeof(buffer)) == FALSE);
}

int main(void) {
  TEST_RTMemoryAlloc_CheckReadWrite();
  TEST_RTMemoryDealloc_ValidPointer();
  TEST_RTMemoryDealloc_CheckNULL();
  TEST_RTMemoryCopy_CheckSourceTarget();
  TEST_RTMemoryCopy_CheckBoundsZeroSize();
  TEST_RTMemoryCopy_CheckBounds();
  TEST_RTMemoryCompare_EqualBuffers();
  TEST_RTMemoryCompare_UnequalBuffers();
}

#endif

#include "RTExecute.c"

RTValue *FIXTURE_RegisterSet(RTInteger32Bit count) {
  RTValue *reg = CreateRegisterSet(count);
  REQUIRE(reg != NULL);
  return reg;
}

void TEST_CreateRegisterSet_Valid(void) {
  RTValue *reg = CreateRegisterSet(1);
  REQUIRE(reg != NULL);
  ASSERT(reg[0] != NULL);
}

void TEST_DeallocRegisterSet_Valid(void) {
  RTValue *reg = FIXTURE_RegisterSet(1);
  DeallocRegisterSet(reg, 1, FALSE);
}

int main(void) {

}

#include "Runtime.h"
#include "RTExecute.h"

#ifdef HYDE

int main(int argc, char **argv) {
  RTByte code[] = {0X01, 0X01, 0X03, 0X0C, 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
  RTValue value = RTExecuteBytecode(code);
}

#endif

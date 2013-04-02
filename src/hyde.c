#include <stdio.h>
#include <unistd.h>

#include "Runtime.h"
#include "RTExecute.h"
#include "RTString.h"
#include "RTDecode.h"
#include "RTValue.h"


#ifdef HYDE

int main(int argc, char **argv) {
  RTByte code[1024];
  read(STDIN_FILENO, code, 1024);
  RTValue value = RTExecuteBytecode(code);
  RTString string = RTValueGetPrimitive(value).string;
  RTSize size = RTStringEncodingSize(string);
  RTByte *buffer = malloc(size);
  RTStringEncode(string, buffer);
  RTInteger32Bit length = RTDecodeInteger32Bit(&buffer);
  for (RTInteger32Bit index = 0; index < length; index += 1) {
    RTInteger32Bit codepoint = RTDecodeInteger32Bit(&buffer);
    putchar(codepoint);
  }
  putchar('\n');
}

#endif

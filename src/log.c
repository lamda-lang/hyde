#include "log.h"

static inline void PrintCharacter(Integer32Bit codepoint) {
  putchar(codepoint & 0XFF);
}

void LogString(String *string) {
  StringEnumerateCodepoints(string, PrintCharacter);
  putchar('\n');
}

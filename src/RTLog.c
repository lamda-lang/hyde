#include "RTLog.h"

static inline void PrintCharacter(RTInteger32Bit codepoint) {
  putchar(codepoint & 0XFF);
}

void RTLogString(RTString *string) {
  RTStringEnumerateCodepoints(string, PrintCharacter);
  putchar('\n');
}

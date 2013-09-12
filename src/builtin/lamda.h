#ifndef BUILTIN_LAMDA_H
#define BUILTIN_LAMDA_H

#include <runtime.h>

Value *LamdaDecode(Byte **bytes);
void LamdaRelease(Lamda *lamda);
Bool LamdaEqual(Lamda *lamda, Lamda *other);

#endif

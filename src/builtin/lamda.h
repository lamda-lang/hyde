#ifndef BUILTIN_LAMDA_H
#define BUILTIN_LAMDA_H

#include <runtime.h>

Value *LamdaDecode(Byte **bytes);
void LamdaRelease(void *lamdaData);
Bool LamdaEqual(void *lamdaData, void *otherData);

#endif

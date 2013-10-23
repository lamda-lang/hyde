#ifndef INTEGER_H
#define INTEGER_H

#include "runtime.h"

Bool IntegerDecode(Binary *binary, Integer32 *offset, Value **value);
Bool IntegerEqual(Integer *integer, Integer *other);

#endif

#ifndef ENCODE_H
#define ENCODE_H

#include "runtime.h"

void EncodeInteger8(Integer8 value, Byte **bytes);
void EncodeInteger16(Integer16 value, Byte **bytes);
void EncodeInteger32(Integer32 value, Byte **bytes);
void EncodeInteger64(Integer64 value, Byte **bytes);
void EncodeFloat64(Float64 value, Byte **bytes);
void EncodeBool(Bool value, Byte **bytes);

#endif

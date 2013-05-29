#ifndef DATA_H
#define DATA_H

#include "api.h"

Data *DataCreate(Exception *exception);

void DataDealloc(Data *data);

Status DataAppendBytes(Data *data, Byte *bytes, Size size, Exception *exception);

Byte *DataBytes(Data *data);

Size DataSize(Data *data);

#endif

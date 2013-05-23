#ifndef DATA_H
#define DATA_H

#include "api.h"

Data *DataCreate(void);

void DataDealloc(Data *buffer);

Status DataAppend(Data *buffer, Byte *source, Size size);

Byte *DataBytes(Data *buffer);

Size DataSize(Data *buffer);

#endif

#ifndef DATA_H
#define DATA_H

#include "api.h"

Data *DataCreate(Error *error);
void DataDealloc(Data *data);
Status DataAppendBytes(Data *data, Byte *bytes, Size size, Error *error);
Byte *DataBytes(Data *data);
Size DataSize(Data *data);

#endif

#ifndef RT_VALUE
#define RT_VALUE

#include "Runtime.h"

RTBool RTValueEqual();

RTInteger64Bit RTValueHash();

RTBoolean RTValueBooleanBridge(RTValue value);

RTIdentifier RTValueIdentifierBridge(RTValue value);

RTInteger RTValueIntegerBridge(RTValue value);

RTLambda RTValueLambdaBridge(RTValue value);

RTList RTValueListBridge(RTValue value);

RTMap RTValueMapBridge(RTValue value);

RTNil RTValueNilBridge(RTValue value);

RTString RTValueStringBridge(RTValue value);

void RTValueSetFlag(RTValue value, RTFlag flag, RTBool boolean);

RTBool RTValueGetFlag(RTValue value, RTFlag flag);

RTType RTValueGetType(RTValue value);

#endif

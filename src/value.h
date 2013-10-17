#ifndef VALUE_H
#define VALUE_H

#include "runtime.h"

Bool ValueEval(Value *value, Stack *stack);
Value *ValueCreateBinary(Binary *binary);
Value *ValueCreateBoolean(Boolean *boolean);
Value *ValueCreateCase(Case *block);
Value *ValueCreateDo(Do *block);
Value *ValueCreateFloat(Float *fpn);
Value *ValueCreateIdentifier(Identifier *id);
Value *ValueCreateInteger(Integer *integer);
Value *ValueCreateLamda(Lamda *lamda);
Value *ValueCreateList(List *list);
Value *ValueCreateMap(Map *map);
Value *ValueCreateModule(Module *module);
Value *ValueCreateNil(Nil *nil);
Value *ValueCreateRange(Range *range);
Value *ValueCreateResult(Result *result);
Value *ValueCreateSet(Set *set);
Value *ValueCreateString(String *string);
Value *ValueCreateToken(Token *token);
Value *ValueCreateType(Type *type);
Value *ValueCreateWhen(When *block);
Binary *ValueBinaryPrimitive(Value *value);
Boolean *ValueBooleanPrimitive(Value *value);
Case *ValueCasePrimitive(Value *value);
Do *ValueDoPrimitive(Value *value);
Float *ValueFloatPrimitive(Value *value);
Identifier *ValueIdentifierPrimitive(Value *value);
Integer *ValueIntegerPrimitive(Value *value);
Lamda *ValueLamdaPrimitive(Value *value);
List *ValueListPrimitive(Value *value);
Map *ValueMapPrimitive(Value *value);
Module *ValueModulePrimitive(Value *value);
Nil *ValueNilPrimitive(Value *value);
Range *ValueRangePrimitive(Value *value);
Result *ValueResultPrimitive(Value *value);
Set *ValueSetPrimitive(Value *value);
String *ValueStringPrimitive(Value *value);
Token *ValueTokenPrimitive(Value *value);
Type *ValueTypePrimitive(Value *value);
When *ValueWhenPrimitive(Value *value);

#endif

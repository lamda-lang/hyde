#ifndef VALUE_H
#define VALUE_H

#include "runtime.h"

Bool ValueEval(Value *value, Context *context, Stack *stack);
Bool ValueEqual(Value *value, Value *other);
Bool ValueIsTrue(Value *value);
Value *ValueCreateBinary(Binary *binary);
Value *ValueCreateBoolean(Boolean *boolean);
Value *ValueCreateCase(Case *block);
Value *ValueCreateDo(Do *block);
Value *ValueCreateException(Exception *exception);
Value *ValueCreateFloat(Float *fpn);
Value *ValueCreateIdentifier(Identifier *id);
Value *ValueCreateInteger(Integer *integer);
Value *ValueCreateKernel(Kernel *kernel);
Value *ValueCreateLamda(Lamda *lamda);
Value *ValueCreateList(List *list);
Value *ValueCreateMap(Map *map);
Value *ValueCreateModule(Module *module);
Value *ValueCreateNil(Nil *nil);
Value *ValueCreateResult(Result *result);
Value *ValueCreateSet(Set *set);
Value *ValueCreateString(String *string);
Value *ValueCreateToken(Token *token);
Value *ValueCreateWhen(When *block);
Binary *ValueBinaryPrimitive(Value *value);
Boolean *ValueBooleanPrimitive(Value *value);
Case *ValueCasePrimitive(Value *value);
Do *ValueDoPrimitive(Value *value);
Float *ValueFloatPrimitive(Value *value);
Identifier *ValueIdentifierPrimitive(Value *value);
Integer *ValueIntegerPrimitive(Value *value);
Kernel *ValueKernelPrimitive(Value *value);
Lamda *ValueLamdaPrimitive(Value *value);
List *ValueListPrimitive(Value *value);
Map *ValueMapPrimitive(Value *value);
Module *ValueModulePrimitive(Value *value);
Nil *ValueNilPrimitive(Value *value);
Result *ValueResultPrimitive(Value *value);
Set *ValueSetPrimitive(Value *value);
String *ValueStringPrimitive(Value *value);
Token *ValueTokenPrimitive(Value *value);
When *ValueWhenPrimitive(Value *value);

#endif

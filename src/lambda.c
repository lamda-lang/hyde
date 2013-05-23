#include "lambda.h"

struct Lambda {
  Value base;
  Integer8Bit arity;
  Integer32Bit registerCount;
  Integer32Bit instructionCount;
  Integer32Bit contextLength;
  Integer32Bit codeSize;
  Byte *code;
  Value *context[];
};

Value *LambdaValueBridge(Lambda *lambda) {
  return (Value *)lambda;
}

Lambda *LambdaDecode(Byte **code) {
  Integer32Bit registerCount = DecodeVBRInteger32Bit(code);
  Integer32Bit instructionCount = DecodeVBRInteger32Bit(code);
  Integer32Bit contextLength = DecodeVBRInteger32Bit(code);
  Integer32Bit codeSize = DecodeVBRInteger32Bit(code);
  Integer8Bit arity = DecodeInteger8Bit(code);
  Size size = sizeof(struct Lambda) + sizeof(Value) * contextLength;
  Lambda *lambda = MemoryAlloc(size);
  if (lambda == NULL) {
    goto error;
  }
  Byte *buffer = MemoryAlloc(codeSize);
  if (buffer == NULL) {
    goto errorData;
  }
  lambda->base = ValueInit(TypeLambda, FlagNone);
  lambda->arity = arity;
  lambda->registerCount = registerCount;
  lambda->instructionCount = instructionCount;
  lambda->contextLength = contextLength;
  lambda->codeSize = codeSize;
  lambda->code = buffer;
  MemoryCopy(*code, buffer, codeSize);
  *code += codeSize;
  return lambda;

errorData:
  MemoryDealloc(lambda);
error:
  return NULL;
}

void LambdaDealloc(Value *lambda_Lambda) {
  Lambda *lambda = ValueLambdaBridge(lambda_Lambda);
  MemoryDealloc(lambda->code);
  MemoryDealloc(lambda);
}

void LambdaSetContextValueAtIndex(Lambda *lambda, Value *value, Integer32Bit index) {
  lambda->context[index] = value;
}

Integer64Bit LambdaHash(Value *lambda_Lambda) {
  Lambda *lambda = ValueLambdaBridge(lambda_Lambda);
  return lambda->registerCount;
}

Integer32Bit LambdaRegisterCount(Lambda *lambda) {
  return lambda->registerCount;
}

Status LambdaExecute(Lambda *lambda, Stack *stack, Integer8Bit arity) {
  if (arity != lambda->arity) {
    goto error;
  }
  return ExecuteCode(lambda->code, lambda->instructionCount, stack);

error:
  return StatusFailure;
}

void LambdaEnumerate(Value *lambda_Lambda, void (*block)(Value *value)) {
  Lambda *lambda = ValueLambdaBridge(lambda_Lambda);
  for (Integer32Bit index = 0; index < lambda->contextLength; index += 1) {
    block(lambda->context[index]);
  }
}

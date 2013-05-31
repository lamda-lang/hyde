#include "do.h"

struct Do {
  Value base;
  Integer8 contextLength;
  Integer32 registerCount;
  Integer32 instructionCount;
  Byte *code;
  Value *context[];
};

Value *DoValueBridge(Do *block) {
    return (Value *)block;
}

Do *DoDecode(Byte **bytes, Error *error) {
    Integer32 registerCount = DecodeInteger32VLE(bytes);
    Integer32 instructionCount = DecodeInteger32VLE(bytes);
    Integer8 contextLength = DecodeInteger8FLE(bytes);
    Integer32 codeSize = DecodeInteger32VLE(bytes);
    Size size = sizeof(Do) *sizeof(Value *) * contextLength;
    Do *block = MemoryAlloc(size, error);
    if (block == NULL) {
	goto returnError;
    }
    Byte *code = MemoryAlloc(codeSize, error);
    if (code == NULL) {
	goto deallocBlock;
    }
    MemoryCopy(*bytes, code, codeSize);
    *bytes += codeSize;
    block->base = TypeDo;
    block->contextLength = contextLength;
    block->registerCount = registerCount;
    block->instructionCount = instructionCount;
    block->code = code;
    return block;

deallocBlock:
    MemoryDealloc(block);
returnError:
    return NULL;
}

void DoDealloc(Do *block) {
    MemoryDealloc(block->code);
    MemoryDealloc(block);
}

Integer64 DoHash(Do *block) {
    return block->contextLength;
}

#include <builtin/do.h>

typedef struct DoNative DoNative;
typedef struct DoCore DoCore;

struct DoNative {
  Value *type;
  Integer32 count;
  Value *elements[];
};

struct DoCore {
    Value *type;
    Kernel *kernel;
    Integer8 count;
    Value *args[];
};

static DoNative *DoNativeCreate(Integer32 count, Error *error) {
    DoNative *block = MemoryAlloc(sizeof(DoNative) * sizeof(Value *) * count, error);
    if (*error != ErrorNone)
        return NULL;
    block->type = NULL;
    block->count = count;
    return block;
}

static DoCore *DoCoreCreate(Kernel *kernel, Value **args, Integer8 count, Error *error) {
    DoCore *block = MemoryAlloc(sizeof(DoCore) * sizeof(Value *) * count, error);
    if (*error != ErrorNone)
        return NULL;
    block->type = NULL;
    block->count = count;
    block->kernel = kernel;
    MemoryCopy(args, block->args, sizeof(Value *) * count);
    return block;
}

Value *DoDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    DoNative *block = DoNativeCreate(count, error);
    if (*error != ErrorNone) goto returnError;
    for (Integer32 index = 0; index < count; index += 1) {
        block->elements[index] = DecodeValue(bytes, error);
        if (*error != ErrorNone) goto deallocDo;
    }
    return block;

deallocDo:
    MemoryDealloc(block);
returnError:
    return NULL;
}

Value *DoCreate(Kernel *kernel, Value **args, Integer8 count, Error *error) {
    return DoCoreCreate(kernel, args, count, error);
}

void DoDealloc(Value *doValue) {
    MemoryDealloc(doValue);
}

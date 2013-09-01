#include "do.h"

typedef struct {
  VALUE *type;
  Integer32 count;
  VALUE *elements[];
} DoNative;

typedef struct {
    VALUE *type;
    Kernel *kernel;
    Integer8 count;
    VALUE *args[];
} DoCore;

static DoNative *DoNativeCreate(Integer32 count, Error *error) {
    DoNative *block = MemoryAlloc(sizeof(DoNative) * sizeof(VALUE *) * count, error);
    if (*error != ErrorNone) {
        return NULL;
    }
    block->type = NULL;
    block->count = count;
    return block;
}

static DoCore *DoCoreCreate(Kernel *kernel, VALUE **args, Integer8 count, Error *error) {
    DoCore *block = MemoryAlloc(sizeof(DoCore) * sizeof(VALUE *) * count, error);
    if (*error != ErrorNone) {
        return NULL;
    }
    block->type = NULL;
    block->count = count;
    block->kernel = kernel;
    MemoryCopy(args, block->args, sizeof(VALUE *) * count);
    return block;
}

VALUE *DoDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    DoNative *block = DoNativeCreate(count, error);
    if (*error != ErrorNone) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        block->elements[index] = DecodeValue(bytes, error);
        if (*error != ErrorNone) {
            goto deallocDo;
        }
    }
    return block;

deallocDo:
    MemoryDealloc(block);
returnError:
    return NULL;
}

VALUE *DoCreate(Kernel *kernel, VALUE **args, Integer8 count, Error *error) {
    return DoCoreCreate(kernel, args, count, error);
}

void DoDealloc(VALUE *doValue) {
    MemoryDealloc(doValue);
}

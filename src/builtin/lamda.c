#include <builtin/lamda.h>

typedef struct LamdaNative LamdaNative;
typedef struct LamdaCore LamdaCore;

struct LamdaNative {
    Value *type;
    Value *result;
    Integer8 arity;
    Integer8 count;
    Value *upvalues[];
};

struct LamdaCore {
    Value *type;
    Kernel *kernel;
    Integer8 arity;
};

static LamdaNative *LamdaNativeCreate(Value *result, Integer8 arity, Integer8 count, Error *error) {
    LamdaNative *lamda = MemoryAlloc(sizeof(LamdaNative) + sizeof(Value *) * count, error);
    if (*error != ErrorNone)
        return NULL;
    lamda->type = NULL;
    lamda->arity = arity;
    lamda->count = count;
    lamda->result = result;
    return lamda;
}

static LamdaCore *LamdaCoreCreate(Kernel *kernel, Integer8 arity, Error *error) {
    LamdaCore *lamda = MemoryAlloc(sizeof(LamdaCore), error);
    if (*error != ErrorNone)
        return NULL;
    lamda->type = NULL;
    lamda->arity = arity;
    lamda->kernel = kernel;
    return lamda;
}

Value *LamdaDecode(Byte **bytes, Error *error) {
    Integer8 arity = DecodeInteger8(bytes);
    Value *result = DecodeValue(bytes, error);
    if (*error != ErrorNone) goto returnError;
    Integer8 count = DecodeInteger8(bytes);
    LamdaNative *lamda = LamdaNativeCreate(result, arity, count, error);
    if (*error != ErrorNone) goto returnError;
    for (Integer8 index = 0; index < count; index += 1) {
        lamda->upvalues[index] = DecodeValue(bytes, error);
        if (*error != ErrorNone) goto deallocLamda;
    }
    return lamda;

deallocLamda:
    MemoryDealloc(lamda);
returnError:
    return NULL;
}

Value *LamdaCreate(Kernel *kernel, Integer8 arity, Error *error) {
    return LamdaCoreCreate(kernel, arity, error);
}

void LamdaDealloc(Value *lamdaValue) {
    MemoryDealloc(lamdaValue);
}

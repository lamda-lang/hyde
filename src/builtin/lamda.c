#include <builtin/lamda.h>

typedef struct LamdaNative LamdaNative;
typedef struct LamdaCore LamdaCore;

struct LamdaNative {
    VALUE *type;
    VALUE *result;
    Integer8 arity;
    Integer8 count;
    VALUE *upvalues[];
};

struct LamdaCore {
    VALUE *type;
    Kernel *kernel;
    Integer8 arity;
};

static LamdaNative *LamdaNativeCreate(VALUE *result, Integer8 arity, Integer8 count, Error *error) {
    LamdaNative *lamda = MemoryAlloc(sizeof(LamdaNative) + sizeof(VALUE *) * count, error);
    if (*error != ErrorNone) return NULL;
    lamda->type = RuntimeValueForConstant(ConstantLamdaType);
    lamda->arity = arity;
    lamda->count = count;
    lamda->result = result;
    return lamda;
}

static LamdaCore *LamdaCoreCreate(Kernel *kernel, Integer8 arity, Error *error) {
    LamdaCore *lamda = MemoryAlloc(sizeof(LamdaCore), error);
    if (*error != ErrorNone) return NULL;
    lamda->type = RuntimeValueForConstant(ConstantLamdaType);
    lamda->arity = arity;
    lamda->kernel = kernel;
    return lamda;
}

VALUE *LamdaDecode(Byte **bytes, Error *error) {
    Integer8 arity = DecodeInteger8(bytes);
    VALUE *result = DecodeValue(bytes, error);
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

VALUE *LamdaCreate(Kernel *kernel, Integer8 arity, Error *error) {
    return LamdaCoreCreate(kernel, arity, error);
}

void LamdaDealloc(VALUE *lamdaValue) {
    MemoryDealloc(lamdaValue);
}

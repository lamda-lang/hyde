#include "runtime.h"

#define MAJOR 0
#define MINOR 0

static VALUE *RuntimeConstant[25] = {NULL};

Error RuntimeInitialize(void) {
    Error error = ErrorNone;
    RuntimeConstant[ConstantBooleanType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantCaseType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantComprehensionType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantDoType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantElementType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantFloatType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantIntegerType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantLamdaType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantListType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantMapType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantMemberType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantModuleType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantNilType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantProtocolType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantRangeType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantResultType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantSetType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantStringType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantTokenType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantTypeType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantVariableType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantWhenType] = TypeCreate(0, &error);
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantNil] = NULL;
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantTrue] = NULL;
    if (error != ErrorNone) goto deallocConstants;
    RuntimeConstant[ConstantFalse] = NULL;
    if (error != ErrorNone) goto deallocConstants;
    return error;

deallocConstants:
    RuntimeShutdown();
    return error;
}

void RuntimeShutdown(void) {
}

VALUE *RuntimeValueForConstant(Constant constant) {
    return RuntimeConstant[constant];
}

VALUE *RuntimeLoad(Byte *bytes, Error *error) {
    Integer8 major = DecodeInteger8(&bytes);
    Integer8 minor = DecodeInteger8(&bytes);
    if (major != MAJOR || minor < MINOR) return (*error = ErrorInvalidBytecodeVersion, NULL);
    return DecodeValue(&bytes, error);
}

VALUE *RuntimeEval(VALUE *value, Error *error) {
    return NULL;
}

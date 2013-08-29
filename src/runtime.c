#include "runtime.h"

/* global type values */
VALUE *RuntimeBooleanType = NULL;
VALUE *RuntimeCaseType = NULL;
VALUE *RuntimeComprehensionType = NULL;
VALUE *RuntimeDoType = NULL;
VALUE *RuntimeElementType = NULL;
VALUE *RuntimeFloatType = NULL;
VALUE *RuntimeIntegerType = NULL;
VALUE *RuntimeLamdaType = NULL;
VALUE *RuntimeListType = NULL;
VALUE *RuntimeMapType = NULL;
VALUE *RuntimeMemberType = NULL;
VALUE *RuntimeModuleType = NULL;
VALUE *RuntimeNilType = NULL;
VALUE *RuntimeProtocolType = NULL;
VALUE *RuntimeRangeType = NULL;
VALUE *RuntimeResultType = NULL;
VALUE *RuntimeSetType = NULL;
VALUE *RuntimeStringType = NULL;
VALUE *RuntimeTokenType = NULL;
VALUE *RuntimeTypeType = NULL;
VALUE *RuntimeVariableType = NULL;
VALUE *RuntimeWhenType = NULL;

/* global error values */
VALUE *RuntimeOutOfMemoryError = NULL;
VALUE *RuntimeFileOpenError = NULL;
VALUE *RuntimeFileReadError = NULL;
VALUE *RuntimeFileWriteError = NULL;
VALUE *RuntimeFileCloseError = NULL;
VALUE *RuntimeInvalidTypeError = NULL;
VALUE *RuntimeArityMismatchError = NULL;

int RuntimeStart(int argc, char **argv) {
    return 0;
}

#include "global.h"

Value *GlobalNil = NULL;
Value *GlobalBooleanTrue = NULL;
Value *GlobalBooleanFalse = NULL;
Stack *GlobalStack = NULL;
File *GlobalFileStandardInput = NULL;

Status GlobalInit(Error *error) {
    if ((GlobalNil = NilCreate(error)) == NULL) {
	goto deallocGlobal;
    }
    if ((GlobalBooleanTrue = BooleanCreate(true, error)) == NULL) {
	goto deallocGlobal;
    }
    if ((GlobalBooleanFalse = BooleanCreate(false, error)) == NULL) {
	goto deallocGlobal;
    }
    if ((GlobalStack = StackCreate(128, error)) == NULL) {
	goto deallocGlobal;
    }
    if ((GlobalFileStandardInput = FileCreateStandardInput(error)) == NULL) {
	goto deallocGlobal;
    }
    return StatusSuccess;

deallocGlobal:
    GlobalDealloc();
    return StatusFailure;
}

void GlobalDealloc(void) {
    NilDealloc(GlobalNil);
    BooleanDealloc(GlobalBooleanTrue);
    BooleanDealloc(GlobalBooleanFalse);
    StackDealloc(GlobalStack);
    FileDealloc(GlobalFileStandardInput);
}

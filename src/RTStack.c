#include "RTStack.h"

#define HEADER_LENGTH 1
#define RESULT_OFFSET 1
#define ARG_OFFSET 2
#define VALUE_OFFSET 1

typedef struct {
  RTInteger32Bit index;
  RTInteger32Bit length;
} RTFrame;

typedef union {
  RTValue *value;
  RTFrame frame;
} RTElement;

struct RTStack {
  RTElement *root;
  RTFrame top;
  RTFrame next;
  RTInteger32Bit capacity;
};

static inline void RemoveGarbageFlagWithRoot(RTValue *root) {
  if (!RTValueFlagSet(root, RTFlagMark)) {
    RTValueSetFlag(root, RTFlagMark, true);
    RTValueSetFlag(root, RTFlagGarbage, false);
    RTValueEnumerate(root, RemoveGarbageFlagWithRoot);
  }
}

static inline void RemoveMarkFlagWithRoot(RTValue *root) {
  if (RTValueFlagSet(root, RTFlagMark)) {
    RTValueSetFlag(root, RTFlagMark, false);
    RTValueEnumerate(root, RemoveMarkFlagWithRoot);
  }
}

RTStack *RTStackCreate(RTInteger32Bit capacity) {
  RTStack *stack = RTMemoryAlloc(sizeof(RTStack));
  if (stack == NULL) {
    goto error;
  }
  RTElement *root = RTMemoryAlloc(sizeof(RTElement) * capacity);
  if (root == NULL) {
    goto errorRoot;
  }
  stack->capacity = capacity;
  stack->root = root;
  stack->top.index = 0;
  stack->top.length = 0;
  stack->next.index = 0;
  stack->next.length = 0;
  return stack;

errorRoot:
  RTMemoryDealloc(stack);
error:
  return NULL;
}

void RTStackDealloc(RTStack *stack) {
  RTMemoryDealloc(stack->root);
  RTMemoryDealloc(stack);
}

bool RTStackBuildNextFrame(RTStack *stack, RTInteger32Bit count) {
  RTFrame top = stack->top;
  RTInteger32Bit length = HEADER_LENGTH + count;
  if (top.index + top.length + length > stack->capacity) { 
    RTInteger32Bit capacity = stack->capacity * 2;
    RTElement *root = RTMemoryRealloc(stack->root, capacity);
    if (root == NULL) {
      goto error;
    }
    stack->capacity = capacity;
    stack->root = root;
  }
  stack->next.index = top.index + top.length;
  stack->next.length = length;
  return true;

error:
  return false;
}

void RTStackPushNextFrame(RTStack *stack) {
  stack->root[stack->next.index].frame = stack->top;
  stack->top = stack->next;
}

RTValue *RTStackReturnFromTopFrame(RTStack *stack) {
  RTFrame top = stack->top;
  RTValue *result = stack->root[top.index + VALUE_OFFSET].value;
  RemoveGarbageFlagWithRoot(result);
  RemoveMarkFlagWithRoot(result);
  for (RTInteger32Bit index = VALUE_OFFSET; index < top.length; index += 1) {
    RTValue *value = stack->root[top.index + index].value;
    if (RTValueFlagSet(value, RTFlagGarbage)) {
      RTValueDealloc(value);
    }
  }
  stack->top = stack->root[top.index].frame;
  return result;
}

void RTStackSetResultInTopFrame(RTStack *stack, RTValue *result) {
  stack->root[stack->top.index + RESULT_OFFSET].value = result;
}

void RTStackCleanTopFrame(RTStack *stack) {

}

RTValue *RTStackGetValueFromTopFrame(RTStack *stack, RTInteger32Bit index) {
  return stack->root[stack->top.index + VALUE_OFFSET + index].value;
}

void RTStackSetValueInTopFrame(RTStack *stack, RTValue *value, RTInteger32Bit index) {
  stack->root[stack->top.index + VALUE_OFFSET + index].value = value;
}

RTValue *RTStackGetArgFromTopFrame(RTStack *stack, RTInteger8Bit index) {
  return stack->root[stack->top.index + ARG_OFFSET + index].value;
}

void RTStackSetArgInNextFrame(RTStack *stack, RTValue *value, RTInteger8Bit index) {
  stack->root[stack->next.index + ARG_OFFSET + index].value = value;
}

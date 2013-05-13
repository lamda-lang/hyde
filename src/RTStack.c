#include "RTStack.h"

#define RESULT_INDEX 1
#define VALUE_INDEX 1
#define ARG_INDEX 2

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

static inline void UnmarkElements(RTValue *value) {
  if (!RTValueFlagSet(value, RTFlagRetain)) {
    RTValueSetFlag(value, RTFlagRetain, true);
    RTValueSetFlag(value, RTFlagMark, false);
    RTValueEnumerate(value, RTCollectRetainValue);
  }
  if (RTValueFlagSet(value, RTFlagRetain)) {
    RTValueSetFlag(value, RTFlagRetain, false);
    RTValueEnumerate(value, RTCollectReleaseValue);
  }
}

RTStack *RTStackCreate(RTInteger32Bit capacity) {
  RTStack *stack = RTMemoryAlloc(sizeof(RTStack));
  RTElement *root = RTMemoryAlloc(sizeof(RTElement) * capacity);
  if (stack == NULL || root == NULL) {
    RTMemoryDealloc(stack);
    RTMemoryDealloc(root);
    return NULL;
  }
  stack->capacity = capacity;
  stack->root = root;
  stack->top.index = 0;
  stack->top.length = 0;
  stack->next.index = 0;
  stack->next.length = 0;
  return stack;
}

void RTStackDealloc(RTStack *stack) {
  RTMemoryDealloc(stack->root);
  RTMemoryDealloc(stack);
}

RTError RTStackBuildNextFrame(RTStack *stack, RTInteger32Bit length) {
  RTFrame top = stack->top;
  if (top.index + top.length + length > stack->capacity) { 
    RTInteger32Bit capacity = stack->capacity * 2;
    RTElement *root = RTMemoryRealloc(stack->root, capacity);
    if (root == NULL) {
      return RTErrorOutOfMemory;
    }
    stack->capacity = capacity;
    stack->root = root;
  }
  stack->next.index = top.index + top.length;
  stack->next.length = length;
  return RTErrorNone;
}

void RTStackPushNextFrame(RTStack *stack) {
  stack->root[stack->next.index].frame = stack->top;
  stack->top = stack->next;
}

RTValue *RTStackReturnFromTopFrame(RTStack *stack) {
  RTFrame top = stack->top;
  RTValue *result = stack->root[top.index + RESULT_INDEX].value;
  UnmarkElements(result);
  for (RTInteger32Bit index = RESULT_INDEX; index < top.length; index += 1) {
    RTValue *value = stack->root[index].value;
    if (RTValueFlagSet(value, RTFlagMark)) {
      RTValueDealloc(value);
    }
  }
  stack->top = stack->root[top.index].frame;
  return result;
}

RTValue *RTStackGetValueFromTopFrame(RTStack *stack, RTInteger32Bit index) {
  return stack->root[stack->top.index + VALUE_INDEX + index].value;
}

void RTStackSetValueInTopFrame(RTStack *stack, RTValue *value, RTInteger32Bit index) {
  stack->root[stack->top.index + VALUE_INDEX + index].value = value;
}

void RTStackSetArgInNextFrame(RTStack *stack, RTValue *value, RTInteger8Bit index) {
  stack->root[stack->next.index + ARG_INDEX + index].value = value;
}

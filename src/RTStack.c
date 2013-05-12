#include "RTStack.h"

typedef struct RTFrame {
  RTInteger32Bit index;
  RTInteger32Bit length;
} RTFrame;

struct RTStack {
  RTFrame frame;
  RTValue **root;
  RTInteger32Bit capacity;
};

RTStack *RTStackCreate(RTInteger32Bit capacity) {
  RTStack *stack = RTMemoryAlloc(sizeof(RTStack));
  RTValue **root = RTMemoryAlloc(capacity * sizeof(RTValue *));
  if (stack == NULL || root == NULL) {
    RTMemoryDealloc(stack);
    RTMemoryDealloc(root);
    return NULL;
  }
  stack->frame.index = 0;
  stack->frame.length = 0;
  stack->capacity = capacity;
  stack->root = root;
  return stack;
}

void RTStackDealloc(RTStack *stack) {
  RTMemoryDealloc(stack->root);
  RTMemoryDealloc(stack);
}

void RTStackClear(RTStack *stack) {
  stack->frame.index = 0;
  stack->frame.length = 0;
}

RTInteger32Bit RTStackTopFrame(RTStack *stack) {
  return stack->frame.index;
}

RTError RTStackBuildFrame(RTStack *stack, RTInteger32Bit length) {
  RTFrame frame = stack->frame;
  if (frame.index + frame.length + length > stack->capacity) {
    RTInteger32Bit capacity = stack->capacity * 2;
    RTValue **root= RTMemoryRealloc(stack->root, capacity);
    if (root == NULL) {
      return RTErrorOutOfMemory;
    }
    stack->capacity = capacity;
    stack->root = root;
  }
  stack->frame.index += stack->frame.length;
  stack->frame.length = length;
  return RTErrorNone;
}

void RTStackSetValueInFrame(RTStack *stack, RTValue *value, RTInteger32Bit index, RTInteger32Bit frame) {
  stack->root[frame + index] = value;
}

void RTStackSetValueInTopFrame(RTStack *stack, RTValue *value, RTInteger32Bit index) {
  stack->root[stack->frame.index + index] = value;
}

RTValue *RTStackGetValueFromFrame(RTStack *stack, RTInteger32Bit index, RTInteger32Bit frame) {
  return stack->root[frame + index];
}

RTValue *RTStackGetValueFromTopFrame(RTStack *stack, RTInteger32Bit index) {
  return stack->root[stack->frame.index + index];
}

void RTStackSetArgInFrame(RTStack *stack, RTValue *value, RTInteger8Bit index, RTInteger32Bit frame) {
  stack->root[frame + index + 1] = value;
}

void RTStackSetArgInTopFrame(RTStack *stack, RTValue *value, RTInteger8Bit index) {
  stack->root[stack->frame.index + index + 1] = value;
}

RTValue *RTStackResultFromFrame(RTStack *stack, RTInteger32Bit frame) {
  return stack->root[frame];
}

RTValue *RTStackResultFromTopFrame(RTStack *stack) {
  return stack->root[stack->frame.index];
}

void RTStackEnumerateValues(RTStack *stack, RTBlock *block) {
  for (RTInteger32Bit index = 0; index < stack->capacity; index += 1) {
    block(stack->root[index]);
  }
}

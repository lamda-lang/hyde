#include "Stack.h"

#define HEADER_LENGTH 1
#define RESULT_OFFSET 1
#define ARG_OFFSET 2
#define VALUE_OFFSET 1

typedef struct {
  Integer32Bit index;
  Integer32Bit length;
} Frame;

typedef union {
  Value *value;
  Frame frame;
} Element;

struct Stack {
  Element *root;
  Frame top;
  Frame next;
  Integer32Bit capacity;
};

static inline void RemoveGarbageFlagWithRoot(Value *root) {
  if (!ValueFlagSet(root, FlagMark)) {
    ValueSetFlag(root, FlagMark, true);
    ValueSetFlag(root, FlagGarbage, false);
    ValueEnumerate(root, RemoveGarbageFlagWithRoot);
  }
}

static inline void RemoveMarkFlagWithRoot(Value *root) {
  if (ValueFlagSet(root, FlagMark)) {
    ValueSetFlag(root, FlagMark, false);
    ValueEnumerate(root, RemoveMarkFlagWithRoot);
  }
}

Stack *StackCreate(Integer32Bit capacity) {
  Stack *stack = MemoryAlloc(sizeof(Stack));
  if (stack == NULL) {
    goto error;
  }
  Element *root = MemoryAlloc(sizeof(Element) * capacity);
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
  MemoryDealloc(stack);
error:
  return NULL;
}

void StackDealloc(Stack *stack) {
  MemoryDealloc(stack->root);
  MemoryDealloc(stack);
}

bool StackBuildNextFrame(Stack *stack, Integer32Bit count) {
  Frame top = stack->top;
  Integer32Bit length = HEADER_LENGTH + count;
  if (top.index + top.length + length > stack->capacity) { 
    Integer32Bit capacity = stack->capacity * 2;
    Element *root = MemoryRealloc(stack->root, capacity);
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

void StackPushNextFrame(Stack *stack) {
  stack->root[stack->next.index].frame = stack->top;
  stack->top = stack->next;
}

Value *StackReturnFromTopFrame(Stack *stack) {
  Frame top = stack->top;
  Value *result = stack->root[top.index + VALUE_OFFSET].value;
  RemoveGarbageFlagWithRoot(result);
  RemoveMarkFlagWithRoot(result);
  for (Integer32Bit index = VALUE_OFFSET; index < top.length; index += 1) {
    Value *value = stack->root[top.index + index].value;
    if (ValueFlagSet(value, FlagGarbage)) {
      ValueDealloc(value);
    }
  }
  stack->top = stack->root[top.index].frame;
  return result;
}

void StackSetResultInTopFrame(Stack *stack, Value *result) {
  stack->root[stack->top.index + RESULT_OFFSET].value = result;
}

void StackCleanTopFrame(Stack *stack) {

}

Value *StackGetValueFromTopFrame(Stack *stack, Integer32Bit index) {
  return stack->root[stack->top.index + VALUE_OFFSET + index].value;
}

void StackSetValueInTopFrame(Stack *stack, Value *value, Integer32Bit index) {
  stack->root[stack->top.index + VALUE_OFFSET + index].value = value;
}

Value *StackGetArgFromTopFrame(Stack *stack, Integer8Bit index) {
  return stack->root[stack->top.index + ARG_OFFSET + index].value;
}

void StackSetArgInNextFrame(Stack *stack, Value *value, Integer8Bit index) {
  stack->root[stack->next.index + ARG_OFFSET + index].value = value;
}

#include "RTPool.h"

typedef struct RTNode *RTNode;

struct RTNode {
  RTValue value;
  RTNode next;
};

struct RTPool {
  RTNode root;
};

static inline RTNode Node(RTValue value, RTNode next) {
  RTSize size = sizeof(struct RTNode);
  RTNode node = RTMemoryAlloc(size);
  if (node == NULL) {
    return NULL;
  }
  node->value = value;
  node->next = next;
  return node;
}

RTPool RTPoolBuild(void) {
  RTSize size = sizeof(struct RTPool);
  RTPool pool = RTMemoryAlloc(size);
  if (pool == NULL) {
    return NULL;
  }
  pool->root = NULL;
  return pool;
}

RTValue RTPoolNewValue(RTPool pool) {
  RTValue value = RTValueCreate();
  if (value == NULL) {
    return NULL;
  }
  RTNode node = Node(value, pool->root);
  if (node == NULL) {
    RTValueDealloc(value);
    return NULL;
  }
  pool->root = node;
  return value;
}

void RTPoolDrain(RTPool pool, RTValue root) {
  RTValueMark(root);
  while (pool->root != NULL) {
    RTNode node = pool->root;
    pool->root = node->next;
    if (RTValueResetMark(node->value) == FALSE) {
      RTValueDealloc(node->value);
    }
    RTMemoryDealloc(node);
  } 
}

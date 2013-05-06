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

static inline void DeallocValue(RTValue value) {
  value = NULL;
}

RTPool RTPoolCreate(void) {
  RTSize size = sizeof(struct RTPool);
  RTPool pool = RTMemoryAlloc(size);
  if (pool == NULL) {
    return NULL;
  }
  pool->root = NULL;
  return pool;
}

void RTPoolDealloc(RTPool pool) {
  while (pool->root != NULL) {
    RTNode node = pool->root;
    pool->root = node->next;
    RTMemoryDealloc(node);
  }
  RTMemoryDealloc(pool);
}

RTValue RTPoolAddValue(RTPool pool, RTValue value) {
  RTNode node = Node(value, pool->root);
  if (node == NULL) {
    DeallocValue(value);
    return NULL;
  }
  pool->root = node;
  return value;
}

void RTPoolDrain(RTPool pool, RTValue root) {
  RTValueSetFlag(root, RTFlagMark, TRUE);
  while (pool->root != NULL) {
    RTNode node = pool->root;
    RTValue value = node->value;
    pool->root = node->next;
    if (RTValueGetFlag(value, RTFlagMark) == FALSE) {
      DeallocValue(value);
    } else {
      RTValueSetFlag(value, RTFlagMark, FALSE);
    }
    RTMemoryDealloc(node);
  } 
}

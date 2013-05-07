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
  RTType type = RTValueGetType(value);
  switch (type) {
  case RTTypeBoolean: {
      RTBoolean boolean = RTValueBooleanBridge(value);
      RTBooleanDealloc(boolean);
      break;
    }
  case RTTypeIdentifier: {
      RTIdentifier id = RTValueIdentifierBridge(value);
      RTIdentifierDealloc(id);
      break;
    }
  case RTTypeLambda: {
      RTLambda lambda = RTValueLambdaBridge(value);
      RTLambdaDealloc(lambda);
      break;
    }
  case RTTypeList: {
      RTList list = RTValueListBridge(value);
      RTListDealloc(list);
      break;
    }
  case RTTypeMap: {
      RTMap map = RTValueMapBridge(value);
      RTMapDealloc(map);
      break;
    }
  case RTTypeNil: {
      RTNil nil = RTValueNilBridge(value);
      RTNilDealloc(nil);
      break;
    }
  case RTTypeString: {
      RTString string = RTValueStringBridge(value);
      RTStringDealloc(string);
      break;
    }
  }
}

static inline void EnumerateBlock(RTValue value, RTBlock block) {
  RTType type = RTValueGetType(value);
  switch (type) {
  case RTTypeLambda: {
      RTLambda lambda = RTValueLambdaBridge(value);
      RTLambdaEnumerateContext(lambda, block);
      break;
    }
  case RTTypeList: {
      RTList list = RTValueListBridge(value);
      RTListEnumerateValues(list, block);
      break;
    }
  case RTTypeMap: {
      RTMap map = RTValueMapBridge(value);
      RTMapEnumerateKeys(map, block);
      RTMapEnumerateValues(map, block);
      break;
    }
  }
}

static inline void MarkValue(RTValue value) {
  if (RTValueGetFlag(value, RTFlagMark) == TRUE) {
    return;
  }
  RTValueSetFlag(value, RTFlagMark, TRUE);
  EnumerateBlock(value, MarkValue);
}

static inline void UnmarkValue(RTValue value) {
  if (RTValueGetFlag(value, RTFlagMark) == FALSE) {
    return;
  }
  RTValueSetFlag(value, RTFlagMark, FALSE);
  EnumerateBlock(value, UnmarkValue);
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

RTBool RTPoolAddValue(RTPool pool, RTValue value) {
  RTNode node = Node(value, pool->root);
  if (node == NULL) {
    return FALSE;
  }
  pool->root = node;
  return TRUE;
}

void RTPoolDrain(RTPool pool, RTValue root) {
  MarkValue(root);
  while (pool->root != NULL) {
    RTNode node = pool->root;
    RTValue value = node->value;
    pool->root = node->next;
    if (RTValueGetFlag(value, RTFlagMark) == FALSE) {
      DeallocValue(value);
    }
    RTMemoryDealloc(node);
  }
  UnmarkValue(root);
}

#include "RTNil.h"

struct RTNil {
  RTBase base;
};

static struct RTNil Singleton = {
  .base = 0
};

const RTNil RTNilSingleton = &Singleton;

#include "runtime.h"

void RuntimeMain(int argc, char **argv) {
    ArgInit(argv, (Integer8)argc);
    ProcessExitSuccess();
}

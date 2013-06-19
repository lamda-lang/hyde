#include "api.h"

int main(int argc, char **argv) {
    ArgInit(argv, argc & 0XF);
    Char *path = ArgFile();
    Char *main = ArgMain();
    Char **args = ArgArgs();
    Integer8 count = ArgArgsCount();
    Error error = 0;
    if (RuntimeMain(path, main, args, count, &error) == StatusFailure) {
	goto printError;
    }
    ProcessExitSuccess();

printError:
    ErrorPrint(error);
    ProcessExitFailure();
}

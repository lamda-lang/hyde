#include <unistd.h>
#include <stdio.h>
#include "arg.h"

typedef struct {
    Char *main;
    Char *file;
    Char **args;
    Integer8 count;
} Arg;

static Arg argSingleton = {
    .main = "main",
    .file = NULL,
    .args = NULL
};

static Char *usage = "usage: lamda [-v] [-h] [-m main] file [arg ...]";

static void SetMain(void) {
    argSingleton.main = optarg;
}

static void ShowVersion(void) {
    fprintf(stdout, "lamda 0.0.0\n");
    ProcessExitSuccess();
}

static void ShowHelp(void) {
    fprintf(stdout, "%s\n", usage);
    ProcessExitSuccess();
}

static void InvalidOption(void) {
    fprintf(stderr, "invalid option -%c\n%s\n", optopt, usage);
    ProcessExitFailure();
}

static void MissingArgument(void) {
    fprintf(stderr, "option -%c requires an argument\n%s\n", optopt, usage);
    ProcessExitFailure();
}

static void MissingFile(void) {
    fprintf(stderr, "missing input file\n%s\n", usage);
    ProcessExitFailure();
}

static void (*branch[])(void) = {
    ['m'] = SetMain,
    ['v'] = ShowVersion,
    ['h'] = ShowHelp,
    ['?'] = InvalidOption,
    [':'] = MissingArgument
};

void ArgInit(Char **args, Integer8 count) {
    int option = 0;
    while ((option = getopt(count, args, ":r:hv")) != -1) {
        branch[option]();
    }
    if (count <= optind) {
        MissingFile();
    }
    argSingleton.file = args[optind];
    argSingleton.args = &args[optind + 1];
    argSingleton.count = count - (Integer8)optind - 1;
}

Char *ArgMain(void) {
    return argSingleton.main;
}

Char *ArgFile(void) {
    return argSingleton.file;
}

Char **ArgArgs(void) {
    return argSingleton.args;
}

Integer8 ArgArgsCount(void) {
    return argSingleton.count;
}

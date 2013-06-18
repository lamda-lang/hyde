#include <unistd.h>
#include <stdio.h>
#include "arg.h"

typedef struct {
    Char *root;
    Char *file;
    Char **args;
    Integer8 count;
} Arg;

static Arg argSingleton = {
    .root = "main",
    .file = NULL,
    .args = NULL
};

static Char *usage = "usage: lamda [-v] [-h] [-r root] file [arg ...]";

static void SetRoot(void) {
    argSingleton.root = optarg;
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
    ['r'] = SetRoot,
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

Char *ArgRoot(void) {
    return argSingleton.root;
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

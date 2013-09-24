#include "runtime.h"

int main(int argc, char **argv) {
    Error status = ERROR_NONE;
    Error *error = &status;
    if (argc != 2)
        return EXIT_FAILURE;
    File file = FileOpen(argv[1], error);
    if (ERROR(error))
        return EXIT_FAILURE;
    Size size = FileSize(file, error);
    if (ERROR(error))
        goto file;
    Byte *buffer = MemoryAlloc(size, error);
    if (ERROR(error))
        goto file;
    FileRead(file, buffer, size, error);
    if (ERROR(error))
        goto buffer;
    Byte *bytes = buffer;
    Value *decoded = ValueDecode(&bytes, error);
    if (ERROR(error))
        goto buffer;
    Value *evaluated = ValueEval(decoded, NULL, error);
    if (ERROR(error))
        goto buffer;
    MemoryDealloc(buffer);
    FileClose(file, error);
    if (ERROR(error))
        goto out;
    return EXIT_SUCCESS;

buffer:
    MemoryDealloc(buffer);
file:
    FileClose(file, NULL);
out:
    return EXIT_FAILURE;
}

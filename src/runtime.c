#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "runtime.h"

int main(int argc, char **argv) {
    /*
    if (argc != 2)
        return EXIT_FAILURE;
    int file = open(argv[1], O_RDONLY);
    if (file == -1)
        return EXIT_FAILURE;
    struct stat status = {0};
    if (fstat(file, &status) == -1)
        return close(file), EXIT_FAILURE;
    Byte *buffer = malloc(status.st_size * sizeof(Byte));
    if (buffer == NULL)
        return close(file), EXIT_FAILURE;
    if (read(file, buffer, status.st_size) != status.st_size)
        return close(file), free(buffer), EXIT_FAILURE;
    Byte *bytes = buffer;
    Value *decoded = ValueDecode(&bytes);
    if (decoded == NULL)
        return close(file), free(buffer), EXIT_FAILURE;
    Value *evaluated = ValueEval(decoded, NULL);
    if (evaluated == NULL)
        return close(file), free(buffer), EXIT_FAILURE;
    free(buffer);
    if (close(file) == -1)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
    */
}

#include <fcntl.h>
#include <unistd.h>
#include "file.h"

File FileOpen(Char *path, VALUE **error) {
    int file = open(path, O_RDWR);
    if (file == -1) {
        *error = TokenFileOpenError;
    }
    return file;
}

void FileClose(File file, VALUE **error) {
    if (close(file) == -1) {
        *error = TokenFileCloseError;
    }
}

Size FileRead(File file, void *buffer, Size size, VALUE **error) {
    ssize_t consumed = read(file, buffer, size);
    if (consumed == -1) {
        *error = TokenFileReadError;
        return 0;
    }
    return (Size)consumed;
} 

Size FileWrite(File file, void *buffer, Size size, VALUE **error) {
    ssize_t written = write(file, buffer, size);
    if (written == -1) {
        *error = TokenFileWriteError;
        return 0;
    }
    return (Size)written;
}

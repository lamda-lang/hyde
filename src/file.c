#include <fcntl.h>
#include <unistd.h>
#include "file.h"

File FileOpen(Char *path, VALUE **error) {
    int file = open(path, O_RDWR);
    if (file == -1) {
        *error = RuntimeFileOpenError;
    }
    return file;
}

void FileClose(File file, VALUE **error) {
    if (close(file) == -1) {
        *error = RuntimeFileCloseError;
    }
}

Size FileRead(File file, void *buffer, Size size, VALUE **error) {
    ssize_t consumed = read(file, buffer, size);
    if (consumed == -1) {
        *error = RuntimeFileReadError;
    }
    return (Size)consumed;
} 

Size FileWrite(File file, void *buffer, Size size, VALUE **error) {
    ssize_t written = write(file, buffer, size);
    if (written == -1) {
        *error = RuntimeFileWriteError;
    }
    return (Size)written;
}

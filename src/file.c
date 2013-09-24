#include "file.h"

File FileOpen(Char *path, Error *error) {
    int file = open(path, O_RDWR);
    if (file == -1)
        goto error;
    return file;

error:
    *error = ERROR_FILE_OPEN;
    return file;
}

void FileClose(File file, Error *error) {
    if (close(file) == -1)
        *error = ERROR_FILE_CLOSE;
}

Size FileRead(File file, void *buffer, Size size, Error *error) {
    ssize_t consumed = read(file, buffer, size);
    if (consumed == -1)
        goto error;
    return consumed;

error:
    *error = ERROR_FILE_READ;
    return 0;
}

Size FileWrite(File file, void *buffer, Size size, Error *error) {
    ssize_t written = write(file, buffer, size);
    if (written == -1)
        goto error;
    return written;

error:
    *error = ERROR_FILE_WRITE;
    return 0;
}

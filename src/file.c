#include <fcntl.h>
#include <unistd.h>
#include "file.h"

struct File {
    int handle;
    Byte buffer[256];
};

File *FileOpen(Char *path, Error *error) {
    File *file = MemoryAlloc(sizeof(File), error);
    if (file == NULL) {
        goto returnError;
    }
    int handle = open(path, O_RDWR);
    if (handle == -1) {
	*error = ErrorFileOpen;
        goto deallocFile;
    }
    file->handle = handle;
    return file;

deallocFile:
    MemoryDealloc(file);
returnError:
    return NULL;
}

Status FileClose(File *file, Error *error) {
    if (close(file->handle) == -1) {
	*error = ErrorFileClose;
        goto returnError;
    }
    MemoryDealloc(file);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

Status FileRead(File *file, Data *data, Error *error) {
    ssize_t consumed = 0;
    do {
        consumed = read(file->handle, file->buffer, sizeof(file->buffer));
        if (consumed == -1) {
	    *error = ErrorFileRead;
            goto returnError;
        }
        if (DataAppendBytes(data, file->buffer, (Size)consumed, error) == StatusFailure) {
            goto returnError;
        }
    } while (consumed > 0);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

Status FileWrite(File *file, Data *data, Error *error) {
    Byte *bytes = DataBytes(data);
    Size size = DataSize(data);
    ssize_t written = write(file->handle, bytes, size);
    if (written == -1 || (Size)written != size) {
	*error = ErrorFileWrite;
        goto returnError;
    }
    return StatusSuccess;

returnError:
    return StatusFailure;
}

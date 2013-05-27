#include <fcntl.h>
#include <unistd.h>
#include "file.h"

struct File {
    int handle;
    Byte buffer[256];
};

File *FileOpen(Char *path, Exception *exception) {
    File *file = MemoryAlloc(sizeof(File), exception);
    if (file == NULL) {
        goto returnError;
    }
    int handle = open(path, O_RDWR);
    if (handle == -1) {
	ExceptionRaise(exception, ErrorFileOpen);
        goto deallocFile;
    }
    file->handle = handle;
    return file;

deallocFile:
    MemoryDealloc(file);
returnError:
    return NULL;
}

Status FileClose(File *file, Exception *exception) {
    if (close(file->handle) == -1) {
	ExceptionRaise(exception, ErrorFileClose);
        goto returnError;
    }
    MemoryDealloc(file);
    return StatusSuccess;

returnError:
    return StatusFailure;
}

Data *FileRead(File *file, Exception *exception) {
    Data *data = DataCreate(exception);
    if (data == NULL) {
        goto returnError;
    }
    ssize_t consumed = 0;
    do {
        consumed = read(file->handle, file->buffer, sizeof(file->buffer));
        if (consumed == -1) {
	    ExceptionRaise(exception, ErrorFileRead);
            goto deallocData;
        }
        if (DataAppendBytes(data, file->buffer, (Size)consumed, exception) == StatusFailure) {
            goto deallocData;
        }
    } while (consumed > 0);
    return data;

deallocData:
    DataDealloc(data);
returnError:
    return NULL;
}

Status FileWrite(File *file, Data *data, Exception *exception) {
    Byte *bytes = DataBytes(data);
    Size size = DataSize(data);
    ssize_t written = write(file->handle, bytes, size);
    if (written == -1 || (Size)written != size) {
	ExceptionRaise(exception, ErrorFileWrite);
        goto returnError;
    }
    return StatusSuccess;

returnError:
    return StatusFailure;
}

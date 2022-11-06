#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

int so_fseek(SO_FILE* stream, long offset, int whence) {
    if (stream->_canRead == 0){
        so_fflush(stream);
    }
    else{
        stream->_buffer_pointer_pos = 0;
        stream->_feof = 0;
        memset(stream->_buffer, 0, SO_BUFFER_SIZE);
        return 0;
    }

    if(lseek(stream->_fHandle, offset, whence) == -1){
        stream->_ferror = 1;
        return SO_EOF;
    }

    return 0;
}
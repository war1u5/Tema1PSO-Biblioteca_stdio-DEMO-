#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

int so_fseek(SO_FILE* stream, long offset, int whence) {
    int ls = lseek(stream->_fHandle, offset, whence);
    stream->_file_pointer_pos = ls;

    if(ls<0){
        return SO_EOF;
    }

    return ls;
}
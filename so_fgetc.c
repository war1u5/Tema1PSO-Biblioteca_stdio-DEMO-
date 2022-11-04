#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

int so_fgetc(SO_FILE* stream){
    int readChars;

    if(stream->_canRead==SO_FALSE){
        return SO_EOF;
    }
    
    if(stream->_buffer_pointer_pos == 0){
        readChars = read(stream->_fHandle, stream->_buffer, sizeof(stream->_buffer));
        stream->readChars = readChars;
    }

    if(stream->_buffer_pointer_pos == stream->readChars) {
        stream->_buffer_pointer_pos = 0;
        stream->readChars = 0;
        memset(stream->_buffer, 0, SO_BUFFER_SIZE);
        readChars = read(stream->_fHandle, stream->_buffer, sizeof(stream->_buffer));
        stream->readChars = readChars;

        if(readChars == 0){
            stream->_feof = 1;
            return SO_EOF;
        }
    }

    int ch = stream->_buffer[stream->_buffer_pointer_pos];
    stream->_buffer_pointer_pos++;
    stream->_file_pointer_pos++;

    return ch;
}
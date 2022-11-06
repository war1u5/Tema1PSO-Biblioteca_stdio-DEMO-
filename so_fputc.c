#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

int so_fputc(int c, SO_FILE* stream) {
    if (stream==NULL){
        stream->_ferror = SO_TRUE;
        return SO_EOF;
    }

    int check = 0;
    int count = 0;
    
    if (stream->_canRead == SO_TRUE && stream->_update == SO_FALSE){
        check = 1;
        return SO_EOF;
    }

    if(stream->_append==SO_TRUE){
        so_fseek(stream, 0, SEEK_END);
    }

    if(stream->_buffer_pointer_pos >= SO_BUFFER_SIZE){
        so_fflush(stream);
        stream->_buffer_pointer_pos = 0;
        memset(stream->_buffer, 0, sizeof(stream->_buffer));
    }

    
    stream->_buffer[stream->_buffer_pointer_pos++] = (char) c;
    stream->_file_pointer_pos++;
    stream->writeChars++;

    if(stream->_buffer_pointer_pos == SO_BUFFER_SIZE)
        so_fflush(stream);

    return c;
}
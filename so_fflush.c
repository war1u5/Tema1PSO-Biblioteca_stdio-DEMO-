#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

#if defined(__linux__)

int so_fflush(SO_FILE* stream){
    //fflush are sens doar pentru file-urile care au fost deschise pt citire
    if(stream==NULL || stream->_canWrite==SO_FALSE){
        printf("so_fflush: error!\n");
        return SO_EOF;
    }

    if(stream->_append == SO_TRUE){
        int fs = so_fseek(stream, 0, SEEK_END);
    }

    if(stream->_canWrite==SO_TRUE && stream->_update == SO_FALSE){
        int wrBytes = write(stream->_fHandle, stream->_buffer, stream->writeChars);
        if(wrBytes==0){
            return 0;
        }
    }
}

#elif defined(_WIN32)
        //todo
#endif
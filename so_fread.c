#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream){
    if(stream->_canRead==SO_FALSE){
        return SO_EOF;
    }

    unsigned char* buffer = (unsigned char*)malloc(size*sizeof(unsigned char));

    int count = 0;
    for(int i = 0; i<nmemb || stream->_feof == 1; i++){
        buffer[i] = so_fgetc(stream);
        count++;
    }

    ptr = buffer;
    return count;

}
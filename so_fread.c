#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream){
    if(stream->_canRead==SO_FALSE){
        return SO_EOF;
    }


    if(stream->_feof == 1){
        return SO_EOF;
    }

    int count = 0;
    
    for(int i = 0; i<nmemb; i++){
        
        int character = so_fgetc(stream);
        
        if(character== SO_EOF){
            break;
        }

        *(char*)(ptr) = character;
        (char*)(ptr)++;
        count++;
    }

    return count;

}
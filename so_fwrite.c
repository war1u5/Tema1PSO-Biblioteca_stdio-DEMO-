#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

size_t so_fwrite(const void* ptr, size_t size, size_t nmemb, SO_FILE* stream) {
    unsigned int number_of_chars = 0;               //cate caract vrem sa scriem
    unsigned char chr;                              //the char itself
    unsigned int chars_actually_written = 0;        //cate caract am scris de fapt
    unsigned char *source;
   
    number_of_chars = nmemb;
    source = (unsigned char*) ptr;

    for(int i = 0; i<number_of_chars; i++){
      
        if(source[i] == '\0')
        {
            break;
        }
      
        chr = so_fputc(source[i], stream);

        if(chr == SO_EOF){
            return chars_actually_written;
        }
        chars_actually_written = i;

        if(stream->_ferror == SO_FALSE){
            continue;
        }
        else{
            return chars_actually_written;
        }
    }

    return chars_actually_written;
}
#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

int so_fflush(SO_FILE* stream){
    //fflush are sens doar pentru file-urile care au fost deschise pt citire
    if(stream==NULL || stream->_canWrite==SO_FALSE){
        printf("so_fflush: error!\n");
        return SO_EOF;
    }

    if(stream->_canWrite==SO_TRUE){
        int number_of_bytes_written = 0;
        int number_of_bytes_written_in_total = 0;
        int number_of_bytes_to_write = stream->_write_ptr - stream->_buffer_base;

        if(number_of_bytes_to_write==0){
            return 0;
        }
        
#if defined(__linux__)
        do{
            number_of_bytes_written = write(stream->_fHandle, stream->_buffer_base+number_of_bytes_written_in_total, number_of_bytes_to_write - number_of_bytes_written_in_total);
            if(number_of_bytes_written == -1){
                printf("so_fflush: error!\n");
                return SO_EOF;
            }
            
        } while (number_of_bytes_written_in_total < number_of_bytes_to_write);

#elif defined(_WIN32)
        //todo
#endif
    }

    //verificam daca suntem in append mode, iar daca da folosim lseek ca sa ne mutam la finalul file-ului
    if((stream->_append==SO_TRUE) || (stream->_append==SO_TRUE && stream->_canRead==SO_TRUE)){
        lseek(stream->_fHandle, 0, SEEK_END);
    }

    if(stream->_update == SO_TRUE){
        stream->_canRead = SO_TRUE;
        stream->_canWrite = SO_TRUE;
    }

    stream->_buffer_pointer_pos = 0;
    memset(stream->_buffer, 0, sizeof(stream->_buffer));

    stream->_write_ptr = stream->_buffer_base;
    stream->_write_ptr_end = stream->_buffer_end;
    stream->_buffer_pointer_pos = 0;

    stream->_read_ptr = stream->_buffer_base;
    stream->_read_ptr_end = stream->_read_ptr;
    stream->_buffer_pointer_pos = 0;
    
    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

int so_fclose(SO_FILE* stream){

    if(stream!=NULL)
    {
        int check = so_fflush(stream);
        return close(stream->_fHandle);
    }
    stream->_feof = SO_FALSE;
    stream->_ferror = SO_FALSE;
    stream->_errno = SO_FALSE;
    stream->_buffer_pointer_pos = 0;
    stream->_file_pointer_pos = 0;

    #if defined(__linux__)
	int cl = close(stream->_fHandle);
    
    free(stream);
    stream = NULL;

    #elif defined(_WIN32)
	//todo
    #endif

 
	//stream = NULL;

	return cl; //success
}
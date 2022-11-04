#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

int so_fclose(SO_FILE* stream){
    stream->_buffer_base = NULL; 
    stream->_read_ptr = NULL;
    stream->_write_ptr = NULL;
    stream->_buffer_end = NULL;

    #if defined(__linux__)
	int cl = close(stream->_fHandle);

    #elif defined(_WIN32)
	//todo
    #endif

	stream = NULL;

	return cl; //success
}
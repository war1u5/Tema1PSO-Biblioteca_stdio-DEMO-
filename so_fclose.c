#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

#if defined(__linux__)
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#elif defined(_WIN32)
#include <fileapi.h>

#else
#error "Unknown platform"
#endif

#include <string.h>

int so_fclose(SO_FILE* stream){
    if(stream->_fHandle == NULL){
        printf("deja inchis\n");
        return -1; //error
    }

    free(stream->_buffer_base); //folosim free() pt ca am utilizat malloc()
    stream->_read_ptr = NULL;
    stream->_write_ptr = NULL;
    stream->_buffer_end = NULL;

    #if defined(__linux__)
	close(stream->_fHandle);

    #elif defined(_WIN32)
	//todo
    #endif

	free(stream);
	stream = NULL;

	return 0; //success
}
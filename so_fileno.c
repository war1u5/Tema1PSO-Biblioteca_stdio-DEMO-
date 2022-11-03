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


#if defined(__linux__)
int so_fileno(SO_FILE* stream) {
    if (stream == NULL){
        printf("invalid stream!\n");
        //stream->_errno = SO_TRUE;
        return -1;
    }

	return stream->_fHandle;
}

#elif defined(_WIN32)
//todo

#endif
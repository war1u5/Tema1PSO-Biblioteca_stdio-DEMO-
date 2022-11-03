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

SO_FILE* so_fopen(const char* pathname, const char* mode) {
	int flags = -1;//O_RDONLY;
	int plus = 0;
	int fd;
	SO_FILE* file = NULL;

	if(strcmp(mode,"r")==0){
		file = (SO_FILE*)malloc(sizeof(SO_FILE)); 
		flags = O_RDONLY;
		file->_canRead = SO_TRUE;
		file->_canWrite = SO_FALSE;
		file->_append = SO_FALSE;
		file->_update = SO_FALSE;
	}
	else if(strcmp(mode,"w")==0){
		file = (SO_FILE*)malloc(sizeof(SO_FILE)); 
		flags = O_WRONLY | O_TRUNC | O_CREAT;
		file->_canRead = SO_FALSE;
		file->_canWrite = SO_TRUE;
		file->_append = SO_FALSE;
		file->_update = SO_FALSE;
	}
	else if(strcmp(mode,"a")==0){
		file = (SO_FILE*)malloc(sizeof(SO_FILE)); 
		flags = O_APPEND | O_WRONLY | O_CREAT;
		file->_canRead = SO_FALSE;
		file->_canWrite = SO_TRUE;
		file->_append = SO_TRUE;
		file->_update = SO_FALSE;
	}
	else if(strcmp(mode,"r+")==0){
		file = (SO_FILE*)malloc(sizeof(SO_FILE)); 
		flags = O_RDWR;
		file->_canRead = SO_TRUE;
		file->_canWrite = SO_TRUE;
		file->_append = SO_FALSE;
		file->_update = SO_TRUE;
	}
	else if(strcmp(mode,"w+")==0){
		file = (SO_FILE*)malloc(sizeof(SO_FILE)); 
		flags = O_RDWR | O_TRUNC | O_CREAT;
		file->_canRead = SO_TRUE;
		file->_canWrite = SO_TRUE;
		file->_append = SO_FALSE;
		file->_update = SO_TRUE;
	}
	else if(strcmp(mode,"a+")==0){
		file = (SO_FILE*)malloc(sizeof(SO_FILE)); 
		flags = O_APPEND | O_RDWR | O_CREAT;
		file->_canRead = SO_TRUE;
		file->_canWrite = SO_TRUE;
		file->_append = SO_TRUE;
		file->_update = SO_TRUE;
	}
	else{
		printf("NO SUCH MODE!\n");
		//file->_errno = SO_TRUE;
		return NULL;
	}


	#if defined(__linux__)
		file->_fHandle = open(pathname, flags, 0644);
	
	#elif defined(_WIN32)
	//todo
	#endif

	if (file != NULL) {
		file->_buffer_base = (char*)malloc(sizeof(char) * SO_BUFFER_SIZE);
		file->_buffer_end = file->_buffer_base + SO_BUFFER_SIZE;

		file->_read_ptr = file->_buffer_base;
		file->_read_ptr_end = file->_read_ptr;

		file->_write_ptr = file->_buffer_base;
		file->_write_ptr_end = file->_buffer_end;

		file->_feof = SO_FALSE;

		file->_file_pointer_pos = 0;	
	}

	return file;
}
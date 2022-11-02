#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
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

//definire valori true/false
#define SO_TRUE 1
#define SO_FALSE 0

//definire buffer
#define SO_BUFFER_SIZE 4096

//handle-ul fisierului pe care dorim sa-l deschidem are o structura anume
//see README.md section Structura handle
struct _so_file {

#if defined(__linux__)
    int _fHandle;

#elif defined(_WIN32)
    HANDLE _fHandle;

#else
#error "Unknown platform"

#endif

    //cursor pt citire
    char* _read_ptr;          // Current read pointer (in cadrul buffer-ului intern)
    char* _read_ptr_end;      // End of get area (buffer intern)
    //char* _read_ptr_base;     // Start of putback+get area

    //cursor pt scriere
    char* _write_ptr;         // Current put pointer
    char* _write_ptr_end;     // End of put area
    //char* _write_ptr_base;    // Start of put area

    //reserved area pointers
    char* _buffer_base;       // Start of reserve area
    char* _buffer_end;        // End of reserve area

    //flags
    int _canRead;             // False when open to write
    int _canWrite;            // False when open to read
    int _update;              // True when open in update mode
    int _append;              // True when open in append mode
    
    int _feof;                // verifica daca caller-ul a incercat sa citeasca/scrie dincolo de end of file
    int _ferror;              // Test for read and write errors

    long _file_pointer_pos;
};

static SO_FILE* OpenFileModeReadUpdate(const char* pathname);		// r+
static SO_FILE* OpenFileModeWriteUpdate(const char* pathname);		// w+
static SO_FILE* OpenFileModeAppendUpdate(const char* pathname);		// a+



SO_FILE* so_fopen(const char* pathname, const char* mode) {

	SO_FILE* file = NULL;
//------------------------------r---------------------------------------
	if (strcmp(mode, "r") == 0) {
		SO_FILE* file = (SO_FILE*)malloc(sizeof(SO_FILE));
		if (file == NULL) {
			printf("eroare malloc\n");
			return NULL;
		}
	#if defined(__linux__)
		file->_fHandle = open(pathname, O_RDONLY);
		if(file->_fHandle == -1) {
			printf("open\n");
			free(file);
			return NULL;
		}

	#elif defined(_WIN32)
	//todo

	#endif
		file->_canRead = SO_TRUE;
		file->_canWrite = SO_FALSE;
		file->_append = SO_FALSE;
		file->_update = SO_FALSE;
	}

//------------------------------w---------------------------------------
	else if (strcmp(mode, "w") == 0) {
		SO_FILE* file = (SO_FILE*)malloc(sizeof(SO_FILE));
		if (file == NULL) {
			printf("eroare malloc\n");
			return NULL;
		}
	#if defined(__linux__)
		file->_fHandle = open(pathname, O_WRONLY | O_TRUNC | O_CREAT, 0664);
		if(file->_fHandle == -1) {
			printf("open\n");
			free(file);
			return NULL;
		}
	#elif defined(_WIN32)
	//todo

	#endif
		file->_canRead = SO_FALSE;
		file->_canWrite = SO_TRUE;
		file->_append = SO_FALSE;
		file->_update = SO_FALSE;
	}



//------------------------------a---------------------------------------
	else if (strcmp(mode, "a") == 0) {
		SO_FILE* file = (SO_FILE*)malloc(sizeof(SO_FILE));
		if (file == NULL) {
			printf("eroare malloc\n");
			return NULL;
		}
	#if defined(__linux__)
		file->_fHandle = open(pathname, O_APPEND | O_WRONLY | O_CREAT, 0644);
		if(file->_fHandle == -1) {
			printf("open\n");
			free(file);
			return NULL;
		}
	#elif defined(_WIN32)
	//todo

	#endif
		file->_canRead = SO_FALSE;
		file->_canWrite = SO_TRUE;
		file->_append = SO_TRUE;
		file->_update = SO_FALSE;	
	}



//------------------------------r+---------------------------------------
	else if (strcmp(mode, "r+") == 0) {
		SO_FILE* file = (SO_FILE*)malloc(sizeof(SO_FILE));
		if (file == NULL) {
			printf("eroare malloc\n");
			return NULL;
		}
	#if defined(__linux__)
		file->_fHandle = open(pathname, O_RDWR);
		if(file->_fHandle == -1) {
			printf("open\n");
			free(file);
			return NULL;
		}
	#elif defined(_WIN32)
	//todo

	#endif
		file->_canRead = SO_TRUE;
		file->_canWrite = SO_TRUE;
		file->_append = SO_FALSE;
		file->_update = SO_TRUE;	
	}



//------------------------------w+---------------------------------------
	else if (strcmp(mode, "w+") == 0) {
		SO_FILE* file = (SO_FILE*)malloc(sizeof(SO_FILE));
		if (file == NULL) {
			printf("eroare malloc\n");
			return NULL;
		}
	#if defined(__linux__)
		file->_fHandle = open(pathname, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if(file->_fHandle == -1) {
			printf("open\n");
			free(file);
			return NULL;
		}
	#elif defined(_WIN32)
	//todo

	#endif
		file->_canRead = SO_TRUE;
		file->_canWrite = SO_TRUE;
		file->_append = SO_FALSE;
		file->_update = SO_TRUE;		
	}


//------------------------------a+---------------------------------------
	else if (strcmp(mode, "a+") == 0) {
		SO_FILE* file = (SO_FILE*)malloc(sizeof(SO_FILE));
		if (file == NULL) {
			printf("eroare malloc\n");
			return NULL;
		}
	#if defined(__linux__)
		file->_fHandle = open(pathname, O_APPEND | O_RDWR | O_CREAT, 0644);
		if(file->_fHandle == -1) {
			printf("open\n");
			free(file);
			return NULL;
		}
	#elif defined(_WIN32)
	//todo

	#endif
		file->_canRead = SO_TRUE;
		file->_canWrite = SO_TRUE;
		file->_append = SO_TRUE;
		file->_update = SO_TRUE;			
	}

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

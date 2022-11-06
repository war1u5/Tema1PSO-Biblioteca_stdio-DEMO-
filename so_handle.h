#define _CRT_SECURE_NO_WARNINGS
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
    int _canRead;            // False when open to write
    int _canWrite;            // False when open to read
    int _update;              // True when open in update mode
    int _append;              // True when open in append mode
    
    int _feof;                // verifica daca caller-ul a incercat sa citeasca/scrie dincolo de end of file
    int _ferror;              // Test for read and write errors
    int _errno;               // test pentru so_fileno(), so_fflush()...

    unsigned int _file_pointer_pos;
    unsigned int _buffer_pointer_pos;
    unsigned char _buffer[SO_BUFFER_SIZE];
    int readChars;
    int writeChars;
};
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

    //flagsso_fopen failed
    int _canRead;             // False when open to write
    int _canWrite;            // False when open to read
    int _update;              // True when open in update mode
    int _append;              // True when open in append mode
    
    int _feof;                // verifica daca caller-ul a incercat sa citeasca/scrie dincolo de end of file
    int _ferror;              // Test for read and write errors

    long _file_pointer_pos;
};
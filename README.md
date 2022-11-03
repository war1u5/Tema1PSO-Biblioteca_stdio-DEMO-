# Tema 1 PSO: _Biblioteca stdio_
_Prelipcean Marius_<br/>
_Grupa: C113D_

## Obiectivele temei
* Familiarizarea cu modul de funcționare al bibliotecii standard input/​output (stdio)
* Aprofundarea conceptelor de:
  * I/O buffering
  * Crearea de procese și rularea de fișiere executabile
  * Redirectearea intrărilor și ieșirilor standard
  * Generarea de biblioteci dinamice

## Enunt
Să se realizeze o implementare minimală a bibliotecii stdio, care să permită lucrul cu fișiere. Biblioteca va trebui să implementeze structura SO_FILE (similar cu FILE din biblioteca standard C), împreună cu funcțiile de citire/scriere. De asemenea, va trebui să ofere funcționalitatea de buffering. <br/>
Rezolvarea temei va trebui să genereze o bibliotecă dinamică numită libso_stdio.so/so_stdio.dll care implementează funcțiile declarate în header-ul [so_stdio.h](https://github.com/systems-cs-pub-ro/so/blob/master/assignments/2-stdio/util/so_stdio.h).

## Rezolvare
### Elemente necesare:
#### so_handle.h
Contine macro-uri, handle/file descriptor, structura _so_file<br/>
```c++
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

    //flagsso_fopen failed
    int _canRead;             // False when open to write
    int _canWrite;            // False when open to read
    int _update;              // True when open in update mode
    int _append;              // True when open in append mode
    
    int _feof;                // verifica daca caller-ul a incercat sa citeasca/scrie dincolo de end of file
    int _ferror;              // Test for read and write errors
    int _errno;               // test pentru so_fileno()

    long _file_pointer_pos;   
};
```

## Surse
* Structura program
   * https://github.com/TritonDataCenter/syslinux/blob/master/com32/lib/fopen.c

* System calls
   * https://en.wikipedia.org/wiki/System_call
   * https://wiki.mta.ro/c/3/pso/lab/02
   * https://0xax.gitbooks.io/linux-insides/content/SysCall/
   * https://www.tutorialspoint.com/system-calls-in-unix-and-windows#:~:text=System%20calls%20in%20Windows%20are,system%20using%20the%20system%20calls.
   * https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/

* LINUX 
  * Structura handle
    * https://stackoverflow.com/questions/33536061/file-descriptors-and-file-handles-and-c#:~:text=File%20handle%20is%20a%20type,is%20the%20file%20descriptor)%3F
    * https://en.wikipedia.org/wiki/File_descriptor
    * [feof() flag](https://stackoverflow.com/questions/12337614/how-feof-works-in-c)
    * [ferror() flag](https://www.ibm.com/docs/en/zos/2.3.0?topic=functions-ferror-test-read-write-errors)
    *

  * so_fopen() -> open() syscall
    * https://0xax.gitbooks.io/linux-insides/content/SysCall/linux-syscall-5.html
    * https://github.com/torvalds/linux/blob/master/fs/open.c
    * https://www.thinkage.ca/gcos/expl/c/lib/open.html
    *

  * so_fclose() -> close() syscall
    * http://codewiki.wikidot.com/c:system-calls:close
    * 

  * so_fileno()
    * fileno - map a stream pointer to a file descriptor
    * https://pubs.opengroup.org/onlinepubs/009604599/functions/fileno.html
    *


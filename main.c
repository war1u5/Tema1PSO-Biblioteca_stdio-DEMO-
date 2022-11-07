#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "so_stdio.h"
#include "so_handle.h"

int main()
{
    //------------------test so_fopen()-------------------
    SO_FILE *file = so_fopen("file.txt", "r");
    printf("so_fgetc in while: ");

    int readChars = so_fgetc(file);
    while (readChars != SO_EOF)
    {

        char litera = readChars;
        if (litera != SO_EOF)
        {
            printf("%c", litera);
        }
        else
        {
            break;
        }
        readChars = so_fgetc(file);
    }
    printf("\n");

    //------------------test so_fileno()-------------------
    int file_desc = so_fileno(file);
    if (file_desc == -1)
    {
        printf("so_fileno: invalid stream!\n");
    }
    else
    {
        printf("so_fileno: success!\nfile descriptor: %d\n", file_desc);
    }

    if (file == NULL)
    {
        printf("so_fopen failed\n");
        exit(0);
    }
    else
    {
        printf("so_fopen: success!\n");
        int feof = so_feof(file);
        printf("so_feof: feof: %d\n", feof);
        int pos = so_ftell(file);
        printf("so_ftell: pos cursor: %d\n", pos);
    }

    //------------------test so_fclose()-------------------
    int a = so_fclose(file);

    if (!(a < 0))
    {
        printf("so_fclose nr1: success!\n");
    }
    else
    {
        printf("eroare\n");
    }

    int check = so_fclose(file);

    if (check < 0)
    {
        printf("so_fclose: file already closed\n");
        // exit(0);
    }
    else if (check == 0)
    {
        printf("so_fclose: success!\n");
    }
    else
    {
        printf("so_fclose: failed!\n");
        exit(0);
    }

    so_fflush(file);

    SO_FILE *file1 = so_fopen("file.txt", "r+");

    char buff[5];
    int nr = so_fread(buff, 1, 4, file1);

    while (nr != 0)
    {

        if(nr == SO_EOF)
        {
            break;
        }
        printf("so_fread: %s\n", buff);
        nr = so_fread(buff, 1, 4, file1);

    }

    int var = so_fclose(file1);
    if (var == 0)
    {
        printf("so_fclose(file1): success!\n");
    }

    SO_FILE *file2 = so_fopen("file1.txt", "w");
    printf("file2 open\n");
    int chr = 50;
    //so_fputc(chr, file2);

    char buffWrite[] = "buna seara";
    int writeChar = so_fwrite(buffWrite, 1, sizeof(buffWrite), file2);

    int close = so_fclose(file2);


    // SO_FILE *file3 = so_fopen("file.txt", "w+");
    // so_fread(file3->_buffer, 0, 1, file3);
    // printf("so_fread: %s\n", file3->_buffer);
    // int close2 = so_fclose(file3);

    return 0;
}
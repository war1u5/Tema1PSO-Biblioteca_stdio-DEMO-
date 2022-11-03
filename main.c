#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "so_stdio.h"

int main(){
//------------------test so_fopen()-------------------
    SO_FILE* file = so_fopen("file.txt", "c+");
//------------------test so_fileno()-------------------
    int file_desc = so_fileno(file);
    if(file_desc==-1){
        printf("invalid stream!\n");
    }
    else if(file_desc > 1024){
        printf("invalid stream!\n");
    }
    else{
        printf("file descriptor: %d\n", file_desc);
    }

    if (file == NULL) {
		printf("so_fopen failed\n");
		exit(0);
	}
    else{
        printf("so_fopen: success!\n");
    }

//------------------test so_fclose()-------------------
    int a = so_fclose(file);
    printf("so_fclose nr1\n");
    if(a==1){
        printf("so_fclose nr1: success!");
    }
    int check = so_fclose(file);
    if (check == -1) {
		printf("file already closed\n");
		exit(0);
	}
    else if (check == 0){
        printf("so_fclose: success!\n");
    }
    else{
        printf("so_fclose: failed!");
        exit(0);
    }

    return 0;
}
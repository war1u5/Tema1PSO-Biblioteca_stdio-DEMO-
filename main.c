#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "so_stdio.h"
#include "so_handle.h"

int main(){
//------------------test so_fopen()-------------------
    SO_FILE* file = so_fopen("file.txt", "r+");
//------------------test so_fileno()-------------------
    int file_desc = so_fileno(file);
    if(file_desc==-1){
        printf("invalid stream!\n");
    }
    else{
        printf("so_fileno: success!\nfile descriptor: %d\n", file_desc);
    }

    if (file == NULL) {
		printf("so_fopen failed\n");
		exit(0);
	}
    else{
        printf("so_fopen: success!\n");
        int feof = so_feof(file);
        printf("feof: %d\n", feof);
        int pos = so_ftell(file);
        printf("pos cursor: %d\n", pos);
    }

//------------------test so_fclose()-------------------
    int a = so_fclose(file);
    printf("so_fclose nr1\n");
    if(!(a<0)){
        printf("so_fclose nr1: success!\n");
    }
    int check = so_fclose(file);
    if (check < 0) {
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
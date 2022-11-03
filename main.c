#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "so_stdio.h"

int main(){
    SO_FILE* file = so_fopen("file.txt", "a+");
    if (file == NULL) {
		printf("so_fopen failed\n");
		exit(0);
	}
    else{
        printf("so_fopen: success!\n");
    }
    
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
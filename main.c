#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "so_stdio.h"

int main(){
    SO_FILE* file = so_fopen("file.txt", "x+");
    if (file == NULL) {
		printf("so_fopen failed\n");
		exit(0);
	}
    else{
        printf("succes!\n");
    }

    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "so_stdio.h"

int main(){
    SO_FILE* file = so_fopen("file.txt", "a+");
    if (file == NULL) {
		printf("so_fopen failed");
		exit(0);
	}


    return 0;
}
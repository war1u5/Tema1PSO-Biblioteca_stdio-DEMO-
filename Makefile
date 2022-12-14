main: main.c libso_stdio.so path
	gcc -g -Wall main.c -o main libso_stdio.so

path:
	export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
	
libso_stdio.so: so_fopen.c so_fclose.c so_fileno.c so_fflush.c so_feof.c so_ferror.c so_ftell.c so_fgetc.c so_fread.c so_fputc.c so_fwrite.c so_fseek.c
	gcc -g -fPIC $? -shared -o libso_stdio.so

clean:
	rm -f *.o *~ main *.so
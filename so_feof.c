#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

int so_feof(SO_FILE* stream) {
	return stream->_feof;
}
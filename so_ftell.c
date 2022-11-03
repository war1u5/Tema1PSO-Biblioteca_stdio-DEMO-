#define _CRT_SECURE_NO_WARNINGS
#include "so_stdio.h"
#include "so_handle.h"
#define _DEBUG_

long so_ftell(SO_FILE* stream) {

	return stream->_file_pointer_pos;
}
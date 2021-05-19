#pragma once

enum MESSEGES {
	MEM_ALLOC_ERROR,
	MEM_FILE_ERROR,
	PUSH_ERR,
	STACK_UNDERFLOW,
	MESS_TOTAL
};

void mess_fun(enum MESSEGES mess);
void file_error(FILE* file, __int64* fdesc);
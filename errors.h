#pragma once

enum MESSEGES {
	MEM_ALLOC_ERROR,
	MEM_FILE_ERROR,
	PUSH_ERR,
	MESS_TOTAL
};

void mess_fun(enum MESSEGES mess);
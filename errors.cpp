#include<errors.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stos.h"

static const char* messege_string[]{
	"E memory alloc error",
	"W couldnt open file"
	"W push error"
};

void mess_fun(enum MESSEGES mess) {
	puts(messege_string[mess] + 1);

	if (messege_string[mess][0] == 'E') {
		system("pause");
		STOS_free();
		exit(1);
	}
}
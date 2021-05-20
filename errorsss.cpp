#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stos.h"
#include "errorsss.h"


static const char* messege_string[]{
	"E blad przy allokowaniu pamieci",
	"E problem z dostepem do pliku",
	"W blad podczas wykonywania push",
	"W stos jest pusty"
};

void mess_fun(enum MESSEGES mess) {

	printf("%s\n", messege_string[mess] + 1);

	if (messege_string[mess][0] == 'E') {
		system("pause");
		STOS_free();
		exit(1);
	}
}

void file_error(FILE* file, __int64* fdesc) {

	if (file)
		fclose(file);
	if (fdesc)
		free(fdesc);
	mess_fun(MEM_FILE_ERROR);
}
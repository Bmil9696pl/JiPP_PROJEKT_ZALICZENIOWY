#include "student.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "errors.h"
#include <iostream>
using namespace std;

bool MY_STUDENT_save(void* tmp) {
	STUDENT* pSt = (STUDENT*)malloc(sizeof(STUDENT));

	if(!pSt)
		mess_fun(MEM_ALLOC_ERROR);

	pSt = (STUDENT*)tmp;

	size_t ret;
	
	FILE* file = fopen("DataFile.bin", "wb");
	if (!file)
		return false;

	if ((ret = fwrite((const void*)&pSt->rok, sizeof(int), 1, file)) != 1)
		return false;

	if ((ret = fwrite((const void*)&pSt->dl_nazw, sizeof(size_t), 1, file)) != 1)
		return false;

	if ((ret = fwrite((const void*)&pSt->kierunek, sizeof(int), 1, file)) != 1)
		return false;

	if ((ret = fwrite((const void*)&pSt->nazwisko, pSt->dl_nazw + 1, 1, file)) != 1)
		return false;

	fclose(file);
	free(pSt);
	pSt = NULL;
	return true;
}

void* MY_STUDENT_read(FILE* file) {
	STUDENT *ptr = (STUDENT*)malloc(sizeof(STUDENT));
	size_t ret;

	if (!ptr)
		mess_fun(MEM_ALLOC_ERROR);

	//fread((void*)ptr, sizeof(STUDENT), 1, file);
	if ((ret = fscanf(file, "%d", ptr->rok)) !=1)
		return false;
	if ((ret = fscanf(file, "%d", ptr->dl_nazw)) != 1)
		return false;
	if ((ret = fscanf(file, "%d", ptr->kierunek)) != 1)
		return false;

	ptr->nazwisko = (char*)malloc((ptr->dl_nazw + 1) * sizeof(char));
	if ((ret = fscanf(file, "%s", ptr->nazwisko)) != 1)
		return false;
	//fread(ptr->nazwisko, sizeof(char), ptr->dl_nazw + 1, file);

	return (void*)ptr;
}

void MY_STUDENT_print(void* ptr) {
	STUDENT* pom = (STUDENT*)ptr;
	cout << pom->nazwisko << endl;
	cout << pom->rok << endl;
	cout << pom->kierunek << endl;
}

void *MY_STUDENT_init(char* nazwisko, int rok, KIERUNEK kierunek) {
	STUDENT* pdat = (STUDENT*)malloc(sizeof(STUDENT));
	if(!pdat)
		mess_fun(MEM_ALLOC_ERROR);
	pdat->dl_nazw = strlen(nazwisko);
	pdat->nazwisko = (char*)malloc(sizeof(pdat->dl_nazw + 1));
	if (pdat)
	{
		strcpy(pdat->nazwisko, nazwisko);
		pdat->rok = rok;
		pdat->kierunek = kierunek;
	}
	return (void*)(pdat);
}

void MY_STUDENT_free(void* ptr) {
	STUDENT* pDat = (STUDENT*)ptr;
	if (pDat)
		free(pDat);
}

void * MY_STUDENT_push(char* nazwisko, int rok, KIERUNEK kierunek) {
	return MY_STUDENT_init(nazwisko, rok, kierunek);
}

int MY_STUDENT_comp(void* pCurData, void* pSearchData) {
	STUDENT* pcur = (STUDENT*)pCurData;
	STUDENT* psearch = (STUDENT*)pSearchData;

	if (strcmp(pcur->nazwisko, psearch->nazwisko) == 0)
		return 1;

	return 0;
}
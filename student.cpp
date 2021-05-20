#include "student.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "errorsss.h"
#include <iostream>
using namespace std;

#pragma warning (disable : 4996)

bool MY_STUDENT_save(void* tmp, FILE* file) {
	STUDENT* pSt = (STUDENT*)tmp;
	//SF Sizeof(STUDENT) nie zawsze jest rowny sumie sizeof(poszczegolna skladowa).
	//zalezy to od wyrownania na granice slowa. W tym przypadku kiedy sizeof(STUDENT) != suma{sizeof(skladowe)}
	//bufor pSt nie pozostanie w cale zapisany, to bedzie blad.
	if (fwrite(pSt, sizeof(STUDENT), 1, file) != 1)
		return false;

	if (fwrite(pSt->nazwisko, sizeof(pSt->nazwisko) * (pSt->dl_nazw), 1, file) != 1) 
		return false;
	

	return true;
}

void* MY_STUDENT_read(FILE* file) {
	//SF tu powstaje dynamicznie obiekt STUDENT
	STUDENT *ptr = (STUDENT*)malloc(sizeof(STUDENT));
	if (!ptr)
		mess_fun(MEM_ALLOC_ERROR);
	memset(ptr, 0, sizeof(STUDENT));

	//SF to samo, co i w poprzedniej funkcji.
	if (fread(ptr, sizeof(STUDENT), 1, file) !=1)
		return 0;

	ptr->nazwisko = (char*)malloc((ptr->dl_nazw)  * sizeof(char));
	if (fread(ptr->nazwisko, sizeof(char) * (ptr->dl_nazw), 1, file) != 1)
		return 0;

	//SF Funkcja MY_STUDENT_push tez tworzy obiekt STUDENT - powstaje dublowanie tego samego obiektu.
	//Pytanie: po co tworzymy jeszcze jedna kopie, jesli juz wszystkie dane sa odczytane do ptr?
	//void* data = MY_STUDENT_push(ptr->nazwisko, ptr->rok, ptr->kierunek);

	return (void*)ptr;
}

void MY_STUDENT_print(void* ptr) {
	STUDENT* pom = (STUDENT*)ptr;
	if (pom) {
		cout << pom->nazwisko << endl;
		cout << pom->rok << endl;
		switch (pom->kierunek) {
		case informatyka:
			cout << "informatyka" << endl;
			break;
		case elektronika_i_telekomunikacja:
			cout << "elektronika i telekomunikacja" << endl;
			break;
		case automatyka_i_robotyka:
			cout << "automatyka i robotyka" << endl;
			break;
		}
	}
}

void* MY_STUDENT_init(char* nazwisko, int rok, KIERUNEK kierunek) {
	STUDENT* pdat = (STUDENT*)malloc(sizeof(STUDENT));
	if (!pdat){
		mess_fun(MEM_ALLOC_ERROR);
		return NULL;
	}

	if (pdat)
	{
		size_t dlugosc = strlen(nazwisko) + 1;

		pdat->dl_nazw = dlugosc;

		pdat->nazwisko = (char*)malloc(dlugosc * sizeof(char));
		if (!pdat->nazwisko) {
			mess_fun(MEM_ALLOC_ERROR);
			return NULL;
		}
		strcpy(pdat->nazwisko, nazwisko);

		pdat->rok = rok;

		pdat->kierunek = kierunek;
	}
	return (void*)(pdat);
}

void MY_STUDENT_free(void* ptr) {
	STUDENT* pDat = (STUDENT*)ptr;
	if (pDat){
		free(pDat->nazwisko);
		pDat->nazwisko = NULL;
		free(pDat);
		pDat = NULL;
	}
}

void * MY_STUDENT_push(char* nazwisko, int rok, KIERUNEK kierunek) {
	return MY_STUDENT_init(nazwisko, rok, kierunek);
}

bool MY_STUDENT_comp_nazw(void* pCurData, void* pSearchData) {
	STUDENT* pcur = (STUDENT*)pCurData;
	STUDENT* psearch = (STUDENT*)pSearchData;

	if (strcmp(pcur->nazwisko, psearch->nazwisko) == 0)
		return 1;

	return 0;
}

bool MY_STUDENT_comp_rok(void* pCurData, void* pSearchData) {
	STUDENT* pcur = (STUDENT*)pCurData;
	STUDENT* psearch = (STUDENT*)pSearchData;

	if (pcur->rok == psearch->rok)
		return 1;

	return 0;
}

bool MY_STUDENT_comp_kier(void* pCurData, void* pSearchData) {
	STUDENT* pcur = (STUDENT*)pCurData;
	STUDENT* psearch = (STUDENT*)pSearchData;

	if (pcur->kierunek == psearch->kierunek)
		return 1;

	return 0;
}
#include "student.h"
#include "stos.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "errorsss.h"
using namespace std;

#pragma warning (disable : 4996)

static const char* kierunki[]{
	"0 - informatyka",
	"1 - elektronika i telekomunikacja",
	"2 - automatyka_i_robotyka"
};

static const char *strtab[] =
{
	"0 - push",
	"1 - pop",
	"2 - clear",
	"3 - find",
	"4 - save",
	"5 - read",
	"6 - print",
	"7 - stop"
};

void menu() {
	size_t it;
	for (it = 0; it < INTERF_TOT; ++it)
	{
		printf("%s\n", strtab[it]);
	}
}

void push() {
	KIERUNEK k;
	char nazw[512];
	int rok;
	int kierunek;
	size_t it;
	cout << "nazwisko, rok, kierunek" << endl;
	cin >> nazw;
	cin >> rok;
	for (it = 0; it < KIER_TOT; ++it)
	{
		printf("%s\n", kierunki[it]);
	}
	cin >> kierunek; 
	k = static_cast<KIERUNEK>(kierunek);

	void* pdat = MY_STUDENT_push(nazw, rok, k);
	if (!STOS_push(pdat))
		mess_fun(PUSH_ERR);
}
void pop() {
	STOS tmp = STOS_pop();
	MY_STUDENT_print(tmp.pData);
	MY_STUDENT_free(tmp.pData);
}

void clear() {
	STOS_free();
}

void find() {
	size_t switch_val;
	cout << "po czym chcesz szukac?\n1-nazwisko\n2-rok\n3-kierunek" << endl;
	cin >> switch_val;
	switch (switch_val) {
	case 1:
		find_nazw();
		break;
	case 2:
		find_rok();
		break;
	case 3:
		find_kier();
		break;
	default: cout << "nie ma takiej opcji" << endl;
	}
}

void save() {
	STOS_save();
}

void read() {
	STOS_read();
}

void print() {
	STOS_print();
}

void find_nazw() {
	char str[128];
	cout << "wprowadŸ szukane nazwisko" << endl;
	cin >> str;
	STUDENT* sDat = (STUDENT*)malloc(sizeof(STUDENT));
	if (!sDat) {
		mess_fun(MEM_ALLOC_ERROR);
		return;
	}

	memset(sDat, 0, sizeof(STUDENT));
	size_t size = strlen(str) + 1;
	sDat->nazwisko = (char*)malloc(size * sizeof(char));
	if (!sDat->nazwisko) {
		mess_fun(MEM_ALLOC_ERROR);
		return;
	}
	strcpy(sDat->nazwisko, str);

	void* pDat = STOS_search(sDat, MY_STUDENT_comp_nazw, 1);

	if (pDat) {
		cout << "znaleziono:" << endl;
		MY_STUDENT_print(pDat);
	}

	while (pDat) {
		pDat = STOS_search(sDat, MY_STUDENT_comp_nazw, 0);
		if (pDat) {
			cout << "znaleziono:" << endl;
			MY_STUDENT_print(pDat);
		}
	}
}

void find_rok() {
	int szuk;
	cout << "wprowadŸ szukany rok" << endl;
	cin >> szuk;
	STUDENT* sDat = (STUDENT*)malloc(sizeof(STUDENT));
	if (!sDat) {
		mess_fun(MEM_ALLOC_ERROR);
		return;
	}

	memset(sDat, 0, sizeof(STUDENT));
	sDat->rok = szuk;

	void* pDat = STOS_search(sDat, MY_STUDENT_comp_rok, 1);

	if (pDat) {
		cout << "znaleziono:" << endl;
		MY_STUDENT_print(pDat);
	}

	while (pDat) {
		pDat = STOS_search(sDat, MY_STUDENT_comp_rok, 0);
		if (pDat) {
			cout << "znaleziono:" << endl;
			MY_STUDENT_print(pDat);
		}
	}
}
void find_kier() {
	int szuk;
	cout << "wprowadŸ szukany kierunek" << endl;
	for (int it = 0; it < KIER_TOT; ++it)
	{
		printf("%s\n", kierunki[it]);
	}
	cin >> szuk;
	STUDENT* sDat = (STUDENT*)malloc(sizeof(STUDENT));
	if (!sDat) {
		mess_fun(MEM_ALLOC_ERROR);
		return;
	}

	memset(sDat, 0, sizeof(STUDENT));
	sDat->kierunek = static_cast<KIERUNEK>(szuk);

	void* pDat = STOS_search(sDat, MY_STUDENT_comp_kier, 1);

	if (pDat) {
		cout << "znaleziono:" << endl;
		MY_STUDENT_print(pDat);
	}

	while (pDat) {
		pDat = STOS_search(sDat, MY_STUDENT_comp_kier, 0);
		if (pDat) {
			cout << "znaleziono:" << endl;
			MY_STUDENT_print(pDat);
		}
	}
}
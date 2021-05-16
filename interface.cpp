#include "student.h"
#include "stos.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "errors.h"
using namespace std;

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
	for (it = 0; it < INTERF_TOT; ++it)
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

void clear();
void menu();
void find();
void save();
void read();
void print();

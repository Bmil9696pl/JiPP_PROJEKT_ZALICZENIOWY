#include <cstdio>

#ifndef STUDENT_H
#define STUDENT_H

typedef enum KIERUNEK {
	informatyka,
	elektronika_i_telekomunikacja,
	automatyka_i_robotyka,
	KIER_TOT
};

struct STUDENT {
	char* nazwisko;
	int rok;
	KIERUNEK kierunek;
	size_t dl_nazw;
};

bool MY_STUDENT_save(void* tmp, FILE *file);
void *MY_STUDENT_read(FILE *file);
void MY_STUDENT_print(void *ptr);
void *MY_STUDENT_init(char *nazwisko, int rok, KIERUNEK kierunek);
void MY_STUDENT_free(void* ptr);
void * MY_STUDENT_push(char* nazwisko, int rok, KIERUNEK kierunek);
int MY_STUDENT_comp_nazw(void* pCurData, void* pSearchData);
int MY_STUDENT_comp_rok(void* pCurData, void* pSearchData);
int MY_STUDENT_comp_kier(void* pCurData, void* pSearchData);


#endif
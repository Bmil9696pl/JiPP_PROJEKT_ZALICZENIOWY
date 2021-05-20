#include <cstdio>
#ifndef STOS_H
#define STOS_H

struct STOS {
	void* pData;
	STOS* next;
};

typedef void (*FreeData)(void* pdat);
typedef void (*Print)(void* pdat);
typedef bool (*Save)(void* pdat, FILE* file);
typedef void* (*Load)(FILE* file);
typedef bool (Find)(void* pcurData, void* pSearchData);

void STOS_init(FreeData pFreeDat, Print print, Save save, Load load);
void STOS_free();
STOS * STOS_push(void* pdat);
STOS STOS_pop();
void * STOS_search(void* pSearchDat, Find ptr_comp_fun, int FirstEntry);
void STOS_save();
void STOS_read();
void STOS_print();

#endif
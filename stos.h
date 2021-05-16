#ifndef STOS_H
#define STOS_H

struct STOS {
	void* pData;
	STOS* next;
};

typedef void (*FreeData)(void* pdat);
typedef int (CompData)(void* pcurData, void* pSearchData);

void STOS_init(FreeData pFreeDat);
void STOS_free();
STOS * STOS_push(void* pdat);
STOS STOS_pop();
void * STOS_search(void* pSearchDat, CompData ptr_comp_fun, int FirstEntry);
bool STOS_save();
STOS STOS_read();
void STOS_print();

#endif
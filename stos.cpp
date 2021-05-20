#include "stos.h"
#include <stdlib.h>
#include <stdio.h>
#include "student.h"
#include "errorsss.h"
#include <iostream>
using namespace std;

#pragma warning (disable : 4996)

static STOS* head = NULL;
FreeData freeData;
Print print;
Save save;
Load load;

void STOS_init(FreeData _freeData, Print _print, Save _save, Load _load) {
	head = NULL;
	freeData = _freeData;
	print = _print;
	save = _save;
	load = _load;
}

void STOS_free() {
	STOS* p = head, * ptmp = NULL;

	while (p) {
		(*freeData)(p->pData);
		ptmp = p;
		p = p->next;
		free(ptmp);
	}

	head = NULL;
}

STOS* STOS_push(void* pdat) {
	STOS* current = (STOS*)malloc(sizeof(STOS));
	if (!current){
		mess_fun(MEM_ALLOC_ERROR);
		return NULL;
	}

	current->pData = pdat;
	current->next = head;
	
	head = current;

	return current;
}

STOS STOS_pop() {
	STOS rv;
	if (!head)
	{
		rv.pData = NULL;
		rv.next = NULL;
	}
	else {
		STOS* next = head->next;
		rv.pData = head->pData;
		rv.next = NULL;
		free(head);
		head = next;
	}
	return rv;
}

void * STOS_search(void* pSearchDat, Find find, int FirstEntry) {
	static STOS* p;
	STOS* ptmp = NULL;

	if (FirstEntry)
		p = head;

	while (p)
	{
		if (!(*find)(p->pData, pSearchDat))
		{
			p = p->next;
		}
		else
		{
			ptmp = p;
			p = p->next;  
			return ptmp->pData;  
		}
	}

	return NULL;
}

void STOS_save() {
	STOS* current = head;
	if (current == NULL) {
		mess_fun(STACK_UNDERFLOW);
		return;
	}

	size_t count = 0, items_t = 0;
	while (current != NULL) {
		count++;
		current = current->next;
	}
	current = head;

	unsigned int items = (unsigned int)count;
	__int64* fdesc = (__int64*)malloc((items + 1) * sizeof(__int64));
	if (!fdesc) {
		file_error(NULL, fdesc);
	}

	FILE* file = fopen("DataFile.bin", "wb");
	if (!file){
		file_error(file, fdesc);
		return;
	}

	if (fwrite(&items, sizeof(unsigned int), 1, file) != 1)
	{
		file_error(file, fdesc);
	}

	_fseeki64(file, (count + 1) * sizeof(__int64), SEEK_CUR);

	while (current != NULL) {
		fdesc[items_t] = ftell(file);
		items_t++;
		if (save(current->pData, file) != true) {
			file_error(file, fdesc);
		}
		current = current->next;
	}
	
	fdesc[items_t] = ftell(file);

	_fseeki64(file, sizeof(unsigned int), SEEK_SET);
	if (fwrite(fdesc, sizeof(__int64), count + 1, file) != count + 1)
		file_error(file, fdesc);

	if (file) {
		fclose(file);
		file = NULL;
	}
	if(fdesc) {
		free(fdesc);
		fdesc = NULL;
	}
}

void STOS_read() {
	STOS_free();

	__int64* fdesc = NULL;
	unsigned int items = 0, itemss, record;

	FILE* file = fopen("DataFile.bin", "rb");
	if (!file) {
		file_error(file, fdesc);
	}

	if (fread(&items, sizeof(unsigned int), 1, file) != 1) {
		file_error(file, fdesc);
	}

	fdesc = (__int64*)malloc((items + 1) * sizeof(__int64));
	if (!fdesc) {
		file_error(file, fdesc);
	}

	if (fread(fdesc, sizeof(fdesc[0]), items + 1, file) != items + 1) {
		file_error(file, fdesc);
	}

	for (itemss = 0; itemss < items; ++itemss) {
		record = items - itemss - 1;
		_fseeki64(file, fdesc[record], SEEK_SET);
		
		void* pDat = load(file);
		if (!STOS_push(pDat)) {
			file_error(file, fdesc);
		}
	}

	if (file) {
		fclose(file);
		file = NULL;
	}

	if (fdesc) {
		free(fdesc);
		fdesc = NULL;
	}
}

void STOS_print() {
	STOS* current = head;
	if (current != NULL) {
		while (current != NULL) {
			MY_STUDENT_print(current->pData);
			current = current->next;
		}
	}
	else mess_fun(STACK_UNDERFLOW);
}
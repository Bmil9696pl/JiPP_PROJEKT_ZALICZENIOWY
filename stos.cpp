#include "stos.h"
#include <stdlib.h>
#include <stdio.h>
#include "student.h"
#include "errors.h"

static STOS* head = NULL;
FreeData ptr_free_dat;

void STOS_init(FreeData pFreeDat) {
	head = NULL;
	ptr_free_dat = pFreeDat;
}

void STOS_free() {
	STOS* p = head, * ptmp = NULL;

	while (p) {
		(*ptr_free_dat)(p->pData);
		ptmp = p;
		p = p->next;
		free(ptmp);
	}

	head = NULL;
}

STOS * STOS_push(void* pdat) {
	STOS* current = (STOS*)malloc(sizeof(STOS));
	if (!current)
		mess_fun(MEM_ALLOC_ERROR);
		return NULL;

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
}

void * STOS_search(void* pSearchDat, CompData ptr_comp_fun, int FirstEntry) {
	static STOS* p;
	STOS* ptmp = NULL;

	if (FirstEntry)
		p = head;

	while (p)
	{
		if (!(*ptr_comp_fun)(p->pData, pSearchDat))
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

bool STOS_save() {
	STOS* current = head;
	STOS* tmp = NULL;
	while (current != NULL) {
		if (!MY_STUDENT_save(current))
			mess_fun(MEM_FILE_ERROR);
		tmp = current->next;
		current = tmp;
	}
}
STOS STOS_read() {
	bool pom = 1;
	void* ret;
	FILE* file = fopen("DataFile.bin", "wb");
	if(!file)
		mess_fun(MEM_FILE_ERROR);

	if (head != NULL) {
		STOS_free();
	}

	while(pom != 0) {
		if ((ret = MY_STUDENT_read(file)) != false)
			STOS_push(ret);
		else
			pom = 0;
	}
}

void STOS_print() {
	STOS* current = head;
	STOS* tmp = NULL;
	while (current != NULL) {
		MY_STUDENT_print(current->pData);
		tmp = current->next;
		current = tmp;
	}
}
#include "student.h"
#include "stos.h"
#include "interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;



int main() {
	STOS_init(MY_STUDENT_free, MY_STUDENT_print, MY_STUDENT_save, MY_STUDENT_read);
	size_t op = 0;
	while (op >= INTERF_PUSH && op <= INTERF_STOP) {
		menu();
		cin >> op;
		switch (op) {
		case INTERF_PUSH: push();
			break;
		case INTERF_POP: pop();
			break;
		case INTERF_CLEAR: clear();
			break;
		case INTERF_FIND: find();
			break;
		case INTERF_SAVE: save();
			break;
		case INTERF_READ: read();
			break;
		case INTERF_PRINT: print();
			break;
		case INTERF_STOP: clear();
			return 0;
		deafault:
			cout << "nieznany kod funkcji" << endl;
		}
	}
}
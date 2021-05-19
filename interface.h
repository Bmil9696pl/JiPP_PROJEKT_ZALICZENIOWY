#ifndef INTERFACE_H
#define INTERFACE_H

enum MY_INTERF_EN
{
	INTERF_PUSH,
	INTERF_POP,
	INTERF_CLEAR,
	INTERF_FIND,
	INTERF_SAVE,
	INTERF_READ,
	INTERF_PRINT,
	INTERF_STOP,
	INTERF_TOT
};

void menu();
void push();
void pop();
void clear();
void menu();
void find();
void find_nazw();
void find_rok();
void find_kier();
void save();
void read();
void print();

#endif
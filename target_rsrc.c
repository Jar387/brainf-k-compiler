#include <stdio.h>
#define MAX_LEN 1024

char buf[MAX_LEN];
char* ptr = buf;
char iobuf = 0;

void pinc(){
	++ptr;
}

void pdec(){
	--ptr;
}

void inc(){
	++*ptr;
}

void dec(){
	--*ptr;
}

void out(){
	putchar(*ptr);
}

void in(){
	*ptr = getchar();
}
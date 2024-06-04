#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include "dataType.h"

extern int brojIgraca; //7

int main(void) {


    char* datIgrac= "igraci.bin";

	kreiranjeDatoteke_Igraci(datIgrac);

	int uvjet = 1;

	while (uvjet) {
		uvjet = izbornik(datIgrac);
	}


	printf("\n Zavrsetak  programa");

	return 0;
}

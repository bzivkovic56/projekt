#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>
#include "dataType.h"
#include "Header.h"

//9
int izbornik(const char* const datIgrac) {
	printf("====================");
	printf("Izaberite jednu od ponudenih opcija:");
	printf("====================\n");

	printf("\t\t\tOpcija 1: Dodavanje novih igraca!\n");
	printf("\t\t\tOpcija 2: Ispisivanje igraca !\n");	
	printf("\t\t\tOpcija 3: Pretrazivanje igraca pomocu prezimena!\n");
	printf("\t\t\tOpcija 4: Sortiranje igraca preko najveceg broja poena!\n");
	printf("\t\t\tOpcija 5: Sortiranje igraca preko broja utakmica!\n");
	printf("\t\t\tOpcija 6: Pretrazivanje ozljedjenih igrace!\n");
	printf("\t\t\tOpcija 7: Azuriranje igraca!\n");
	printf("\t\t\tOpcija 8: Brisanje igraca! \n");
	printf("\t\t\tOpcija 9: Brisanje datoteka igraci! \n");
	printf("\t\t\tOpcija 10: Izlaz iz programa!\n");


	 int uvijet = 0;
	 //10
	static IGRAC* poljeIgraca = NULL;//13
	static IGRAC* pronadeniIgrac= NULL;

	scanf("%d", &uvijet);
	switch (uvijet) {
	case DODAVANJE_NOVIH_IGRACA:
		dodajIgraca(datIgrac);
		break;


	case ISPISIVANJE_IGRACA:
		if (poljeIgraca != NULL) {
			free(poljeIgraca);
			poljeIgraca = NULL;
		}

		poljeIgraca = (IGRAC*)ucitavanjeIgraca(datIgrac);

		ispisivanjeIgraca(poljeIgraca);
		break;

	case  PRETRAZIVANJE_IGRACA_PREZIME:
		if (poljeIgraca != NULL) {
			free(poljeIgraca);
			poljeIgraca = NULL;
		}

		poljeIgraca = (IGRAC*)ucitavanjeIgraca(datIgrac);

		pronadiIgracaPrezime(poljeIgraca);
		break;

	case  SORTIRANJE_IGRACA_PO_POENIMA_SILAZNO:
		if (poljeIgraca != NULL) {
			free(poljeIgraca);
			poljeIgraca = NULL;
		}

		poljeIgraca = (IGRAC*)ucitavanjeIgraca(datIgrac);

		ispisiSortiraneIgraceSilazno(poljeIgraca);
		break;

	case  SORTIRANJE_IGRACA_PO_UTAKMICAMA:
		if (poljeIgraca != NULL) {
			free(poljeIgraca);
			poljeIgraca = NULL;
		}

		poljeIgraca = (IGRAC*)ucitavanjeIgraca(datIgrac);

		SortirajUtakmice(poljeIgraca);
		break;

	case PRETRAZIVANJE_OZLJEDJENIH_IGRACA:
		if (poljeIgraca != NULL) {
			free(poljeIgraca);
			poljeIgraca = NULL;
		}

		poljeIgraca = (IGRAC*)ucitavanjeIgraca(datIgrac);

		ispisiOzljedjeneIgrace(poljeIgraca);
		break;


	case  AZURIRANJE_IGRACA:
		if (poljeIgraca != NULL) {
			free(poljeIgraca);
			poljeIgraca = NULL;
		}

		poljeIgraca = (IGRAC*)ucitavanjeIgraca(datIgrac);

		azuriranjeIgraca(poljeIgraca, datIgrac);
		break;

	case BRISANJE_IGRACA:
		if (poljeIgraca != NULL) {
			free(poljeIgraca);
			poljeIgraca = NULL;
		}

		poljeIgraca = (IGRAC*)ucitavanjeIgraca(datIgrac);

		brisanjeIgraca(poljeIgraca, datIgrac);
		break;

	case BRISANJE_DATOTEKA_IGRACI:
		brisanjeDatoteke_Igraci(datIgrac);
		break;

	default:
		uvijet = 0;
	}
	return uvijet;
	
}

	

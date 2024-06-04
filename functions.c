#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dataType.h"

static int brojIgraca = 0; //5

void kreiranjeDatoteke_Igraci(const char* const datIgrac) {
	FILE* pF = fopen(datIgrac, "wb");//17
	if (pF == NULL) {
		perror("Kreiranje datoteke igraci.dat");//20
		exit(EXIT_FAILURE);
	}
	fwrite(&brojIgraca, sizeof(int), 1, pF);
	fclose(pF);
}

void dodajIgraca(const char* const datIgrac) {
	FILE* pF = fopen(datIgrac, "rb+");
	if (pF == NULL) {
		perror("Dodavanje igraca u datoteku igraci.dat");
		exit(EXIT_FAILURE);
	}
	fread(&brojIgraca, sizeof(int), 1, pF);
	printf("brojIgraca: %d\n", brojIgraca);
	IGRAC temp = { 0 };
	temp.id = brojIgraca + 1;

	do {
		printf("Unesite ime igraca!\n");
		scanf(" %29[^\n]", temp.ime);
		int valid = 1;
		for (int i = 0; temp.ime[i] != '\0'; i++) {
			if (!isalpha(temp.ime[i])&& temp.ime[i] != ' ') {
				printf("Neispravan unos. Molimo unesite samo slova.\n");
				valid = 0;
				break;
			}
		}
		if (valid)
			break;
	} while (1);
	getchar();

	do {
		printf("Unesite prezime igraca!\n");
		scanf(" %19[^\n]", temp.prezime);
		int valid = 1;
		for (int i = 0; temp.prezime[i] != '\0'; i++) {
			if (!isalpha(temp.prezime[i])) {
				printf("Neispravan unos. Molimo unesite samo slova.\n");
				valid = 0;
				break;
			}
		}
		if (valid)
			break;
	} while (1);
	getchar();

	do {
		printf("Unesite poziciju igraca (Plej, Centar, Bek, Krilo):\n");
		char pozicija[10];
		scanf("%s", pozicija);
		for (int i = 0; pozicija[i]; i++) {
			pozicija[i] = tolower(pozicija[i]);
		}
		if (strcmp(pozicija, "plej") == 0 ||
			strcmp(pozicija, "centar") == 0 ||
			strcmp(pozicija, "bek") == 0 ||
			strcmp(pozicija, "krilo") == 0) {
			strcpy(temp.pozicija, pozicija);
			break;
		} else {
			printf("Neispravan unos. Molimo unesite poziciju između (Plej, Centar, Bek, Krilo).\n");
		}
	} while (1);
	getchar();

	do {
		printf("Unesite OIB igraca (11 brojeva):\n");
		scanf("%s", temp.oib);
		int validOIB = 1;
		if (strlen(temp.oib) != 11) {
			validOIB = 0;
		} else {
			for (int i = 0; i < 11; i++) {
				if (!isdigit(temp.oib[i])) {
					validOIB = 0;
					break;
				}
			}
		}
		if (!validOIB) {
			printf("Neispravan unos. OIB mora imati točno 11 brojeva.\n");
		} else {
			break;
		}
	} while (1);

	do {
		printf("Ima li igrac ozljedu? (1 za da, 0 za ne)\n");
		while (getchar() != '\n');
	} while (scanf("%d", &temp.ozljeda) != 1 || (temp.ozljeda != 0 && temp.ozljeda != 1));

	do {
		printf("Unesite broj poena igraca \n");
		while (getchar() != '\n');
	} while (scanf("%d", &temp.brojPoena) != 1);

	do {
		printf("Unesite broj asistencija igraca \n");
		while (getchar() != '\n');
	} while (scanf("%d", &temp.brojAsistencija) != 1);

	do {
		printf("Unesite broj skokova igraca \n");
		while (getchar() != '\n');
	} while (scanf("%d", &temp.brojSkokova) != 1);

	do {
		printf("Unesite broj utakmica igraca \n");
		while (getchar() != '\n');
	} while (scanf("%d", &temp.brojUtakmica) != 1);

	temp.prosjekPoena = (float)temp.brojPoena / (float)temp.brojUtakmica;
	temp.prosjekAsistencija = (float)temp.brojAsistencija / (float)temp.brojUtakmica;
	temp.prosjekSkokova = (float)temp.brojSkokova / (float)temp.brojUtakmica;

	//18
	fseek(pF, sizeof(IGRAC) * brojIgraca, SEEK_CUR);
	fwrite(&temp, sizeof(IGRAC), 1, pF);
	rewind(pF);
	brojIgraca++;
	fwrite(&brojIgraca, sizeof(int), 1, pF);
	fclose(pF);
}

IGRAC* ucitavanjeIgraca(const char* const datIgrac) {
	FILE* fp = fopen(datIgrac, "rb");

	if (fp == NULL) {
		perror("Ucitavanje igraca");
		return NULL;
	}

	fread(&brojIgraca, sizeof(int), 1, fp);
	//14,15
	IGRAC* poljeIgraca = (IGRAC*)calloc(brojIgraca, sizeof(IGRAC));

	if (poljeIgraca == NULL) {
		perror("Zauzimanje memorije za polje igraca");
		return NULL;
	}

	fread(poljeIgraca, sizeof(IGRAC), brojIgraca, fp);

	fclose(fp);

	return poljeIgraca;
}

void ispisivanjeIgraca(const IGRAC* const poljeIgraca) {
	if (brojIgraca == 0) {
		printf("Polje igraca prazno\n");
		return;
	}

	for (int i = 0; i < brojIgraca; i++) {
		printf("ID: %d  Ime: %s  Prezime: %s  Pozicija: %s  OIB: %s  Ozljeda [da/ne]: %s Prosjek poena: %.2f Prosjek asistencija: %.2f Prosjek skokova: %.2f  Broj utakmica: %d\n\n",
			(poljeIgraca + i)->id,
			(poljeIgraca + i)->ime,
			(poljeIgraca + i)->prezime,
			(poljeIgraca + i)->pozicija,
			(poljeIgraca + i)->oib,
			(poljeIgraca + i)->ozljeda == 1 ? "\033[1mDa\033[0m" : "Ne",
			(poljeIgraca + i)->prosjekPoena,
			(poljeIgraca + i)->prosjekAsistencija,
			(poljeIgraca + i)->prosjekSkokova,
			(poljeIgraca + i)->brojUtakmica);
	}
}

//22
void pronadiIgracaPrezime(IGRAC* const poljeIgraca) {
	//12
	if (brojIgraca == 0) {
		printf("Polje igraca prazno\n");
		return;
	}

	char trazenoPrezime[25];

	printf("Unesite prezime koje trazite: ");
	getchar();
	scanf("%s", trazenoPrezime);

	int counter = 0;

	for (int i = 0; i < brojIgraca; i++) {
		if (strcmp(trazenoPrezime, (poljeIgraca + i)->prezime) == 0) {
			printf("ID: %d  Ime: %s  Prezime: %s  Pozicija: %s  OIB: %s  Ozljeda [da/ne]: %s Prosjek poena: %.2f Prosjek asistencija: %.2f Prosjek skokova: %.2f  Broj utakmica: %d\n\n",
				(poljeIgraca + i)->id,
				(poljeIgraca + i)->ime,
				(poljeIgraca + i)->prezime,
				(poljeIgraca + i)->pozicija,
				(poljeIgraca + i)->oib,
				(poljeIgraca + i)->ozljeda == 1 ? "\033[1mDa\033[0m" : "Ne",
				(poljeIgraca + i)->prosjekPoena,
				(poljeIgraca + i)->prosjekAsistencija,
				(poljeIgraca + i)->prosjekSkokova,
				(poljeIgraca + i)->brojUtakmica);
			counter++;
		}
	}

	if (counter == 0) {
		printf("Igrac s prezimenom %s nije pronaden\n", trazenoPrezime);
	}
}


//4
void azuriranjeIgraca(IGRAC* poljeIgraca, const char* const datIgrac){

	if (brojIgraca == 0) {
		printf("Polje igraca prazno\n");
		return;
	}

	FILE* fp = fopen(datIgrac, "rb+");


	if (fp == NULL) {
		perror("Azuriranje igraca");
		exit(EXIT_FAILURE);
	}

	int trazeniId;

	printf("Unesite ID igraca kojeg zelite azurirati: ");

	do {
		scanf("%d", &trazeniId);

		if (trazeniId < 1 || trazeniId > brojIgraca) {
			printf("Igrac s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
	} while (trazeniId < 1 || trazeniId > brojIgraca);

	IGRAC temp = { 0 };

	temp.id = trazeniId;
	getchar();


   
    do {
        printf("Unesite ime igraca, (trenutno %s): ", (poljeIgraca + trazeniId - 1)->ime);
        scanf(" %29[^\n]", temp.ime);
        int valid = 1;
        for (int i = 0; temp.ime[i] != '\0'; i++) {
            if (!isalpha(temp.ime[i])&& temp.ime[i] != ' ') {
                printf("Neispravan unos. Molimo unesite samo slova.\n");
                valid = 0;
                break;
            }
        }
        if (valid)
            break;
    } while (1);
    getchar();
   
    do {
        printf("Unesite prezime igraca, (trenutno %s): ",(poljeIgraca + trazeniId - 1)->prezime);
        scanf(" %19[^\n]", temp.prezime);
        int valid = 1;
        for (int i = 0; temp.prezime[i] != '\0'; i++) {
            if (!isalpha(temp.prezime[i])) {
                printf("Neispravan unos. Molimo unesite samo slova.\n");
                valid = 0;
                break;
            }
        }
        if (valid)
            break;
    } while (1);

	getchar();

	do {
    printf("Unesite poziciju igraca (Plej, Centar, Bek, Krilo) (trenutno %s): ", (poljeIgraca + trazeniId - 1)->pozicija);
    char pozicija[10];
    scanf("%s", pozicija);
    // Pretvorba unosa u mala slova radi lakše usporedbe
    for (int i = 0; pozicija[i]; i++) {
        pozicija[i] = tolower(pozicija[i]);
    }
   
    if (strcmp(pozicija, "plej") == 0 || //Provjera da li se uneseni string poklapa sa ocekivanim
        strcmp(pozicija, "centar") == 0 ||
        strcmp(pozicija, "bek") == 0 ||
        strcmp(pozicija, "krilo") == 0) {
        strcpy(temp.pozicija, pozicija); // Ako je unos ispravan, kopiraj u strukturu
        break; 
    } else {
        printf("Neispravan unos. Molimo unesite poziciju između (Plej, Centar, Bek, Krilo).\n");
    }
	} while (1); // Ponavljaj sve dok korisnik ne unese ispravan uno
	getchar();
 	do {
        printf("Unesite OIB igraca (11 brojeva) (trenutno %s):\n", (poljeIgraca + trazeniId - 1)->oib);
        scanf("%s", temp.oib);
        int validOIB = 1;
        if (strlen(temp.oib) != 11) {
            validOIB = 0;
        } else {
            for (int i = 0; i < 11; i++) {
                if (!isdigit(temp.oib[i])) {
                    validOIB = 0;
                    break;
                }
            }
        }
        if (!validOIB) {
            printf("Neispravan unos. OIB mora imati točno 11 brojeva.\n");
        } else {
            break;
        }
    } while (1);

	do {
    printf("Ima li igrac ozljedu? (1 za da, 0 za ne) (trenutno %d): ", (poljeIgraca + trazeniId - 1)->ozljeda);
    while (getchar() != '\n'); 	
	} while (scanf("%d", &temp.ozljeda) != 1 || (temp.ozljeda != 0 && temp.ozljeda != 1));
	
	do {
        printf("Unesite broj poena igraca (trenutno %d): ",(poljeIgraca + trazeniId - 1)->brojPoena);
        while (getchar() != '\n'); 
    } while (scanf("%d", &temp.brojPoena) != 1);

    do {
        printf("Unesite broj asistencija igraca (trenutno %d): ",(poljeIgraca + trazeniId - 1)->brojAsistencija);
        while (getchar() != '\n'); 
    } while (scanf("%d", &temp.brojAsistencija) != 1);

    do {
        printf("Unesite broj skokova igraca (trenutno %d): ",(poljeIgraca + trazeniId - 1)->brojSkokova);
        while (getchar() != '\n'); 
    } while (scanf("%d", &temp.brojSkokova) != 1);

    do {
        printf("Unesite broj utakmica igraca (trenutno %d): ",(poljeIgraca + trazeniId - 1)->brojUtakmica);
        while (getchar() != '\n');
    } while (scanf("%d", &temp.brojUtakmica) != 1);

	temp.prosjekPoena = (float)temp.brojPoena / (float)temp.brojUtakmica;
	temp.prosjekAsistencija = (float)temp.brojAsistencija / (float)temp.brojUtakmica;
	temp.prosjekSkokova = (float)temp.brojSkokova / (float)temp.brojUtakmica;

	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(IGRAC) * (trazeniId - 1), SEEK_CUR);
	fwrite(&temp, sizeof(IGRAC), 1, fp);

	printf("Igrac uspjesno azuriran\n");

	fclose(fp);
}


void zamjena(IGRAC* const veci, IGRAC* const manji) {
	IGRAC temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}
//21
const IGRAC* sortirajPoPoenima(const IGRAC* poljeIgraca) {
    int max = -1; 
    for (int i = 0; i < brojIgraca - 1; i++) {
        max = i; 
        for (int j = i + 1; j < brojIgraca; j++) {
            if ((poljeIgraca + j)->prosjekPoena > (poljeIgraca + max)->prosjekPoena) { 
                max = j; 
            }
        }
        zamjena((IGRAC*)(poljeIgraca + i), (IGRAC*)(poljeIgraca + max));
    }
    return poljeIgraca;
}

void ispisiSortiraneIgraceSilazno(const IGRAC* poljeIgraca) {


	if (brojIgraca == 0) {
		printf("Polje igraca prazno\n");
		return;
	}

	int i;


	poljeIgraca = sortirajPoPoenima(poljeIgraca);


	for (i = 0; i < brojIgraca; i++) {
printf("ID: %d  Ime: %s  Prezime: %s  Pozicija: %s  OIB: %s  Ozljeda [da/ne]: %s Prosjek poena: %.2f Prosjek asistencija: %.2f Prosjek skokova: %.2f  Broj utakmica: %d\n\n",
			(poljeIgraca + i)->id,
			(poljeIgraca + i)->ime,
			(poljeIgraca + i)->prezime,
			(poljeIgraca + i)->pozicija,
			(poljeIgraca + i)->oib,
			(poljeIgraca + i)->ozljeda == 1 ? "\033[1mDa\033[0m" : "Ne",
			(poljeIgraca+i)->prosjekPoena,
			(poljeIgraca+i)->prosjekAsistencija,
			(poljeIgraca+i)->prosjekSkokova,
			(poljeIgraca+i)->brojUtakmica);
	}
}
 
//8 
static inline int compare(const void *p1, const void *p2){
	int utakmica1=((const IGRAC*)p1)->brojUtakmica;
	int utakmica2=((const IGRAC*)p2)->brojUtakmica;
	return utakmica2-utakmica1;
}
//23
//24
void SortirajUtakmice(IGRAC* poljeIgraca) {
    if (brojIgraca == 0) {
        printf("Polje igraca prazno\n");
        return;
    }

    qsort(poljeIgraca, brojIgraca, sizeof(IGRAC), compare);

    printf("Igraci sortirani prema broju utakmica (silazno):\n");
    for (int i = 0; i < brojIgraca; i++) {
        printf("ID: %d  Ime: %s  Prezime: %s  Pozicija: %s  OIB: %s  Ozljeda [da/ne]: %s Prosjek poena: %.2f Prosjek asistencija: %.2f Prosjek skokova: %.2f  Broj utakmica: %d\n\n",
               poljeIgraca[i].id,
               poljeIgraca[i].ime,
               poljeIgraca[i].prezime,
               poljeIgraca[i].pozicija,
               poljeIgraca[i].oib,
               poljeIgraca[i].ozljeda == 1 ? "\033[1mDa\033[0m" : "Ne",
               poljeIgraca[i].prosjekPoena,
               poljeIgraca[i].prosjekAsistencija,
               poljeIgraca[i].prosjekSkokova,
               poljeIgraca[i].brojUtakmica);
    }
}

void ispisiOzljedjeneIgrace(IGRAC* const poljeIgraca) {

	if (brojIgraca == 0) {
		printf("Polje igraca prazno");
		return;
	}

	int i, brojac = 0;

	printf("Igraci koji su trenutno ozljedjeni: \n");

	for (i = 0; i < brojIgraca; i++) {

		if ((poljeIgraca + i)->ozljeda == 1) {
	printf("ID: %d  Ime: %s  Prezime: %s  Pozicija: %s  OIB: %s  Ozljeda [da/ne]: %s Prosjek poena: %.2f Prosjek asistencija: %.2f Prosjek skokova: %.2f  Broj utakmica: %d\n\n",
			(poljeIgraca + i)->id,
			(poljeIgraca + i)->ime,
			(poljeIgraca + i)->prezime,
			(poljeIgraca + i)->pozicija,
			(poljeIgraca + i)->oib,
			(poljeIgraca + i)->ozljeda == 1 ? "\033[1mDa\033[0m" : "Ne",
			(poljeIgraca+i)->prosjekPoena,
			(poljeIgraca+i)->prosjekAsistencija,
			(poljeIgraca+i)->prosjekSkokova,
			(poljeIgraca+i)->brojUtakmica);

			brojac++;
		}
	}

	if (brojac == 0) {
		printf("Trenutno nema ozljedjenih igraca\n");
	}
}


void brisanjeIgraca(IGRAC* const poljeIgraca, const char* const datIgrac) {

	if (brojIgraca == 0) {
		printf("Polje igraca prazno\n");
		return;
	}

	FILE* fp = fopen(datIgrac, "rb+");

	if (fp == NULL) {
		perror("Brisanje igraca");
		exit(EXIT_FAILURE);
	}

	fseek(fp, sizeof(int), SEEK_CUR);

	int i, trazeniId;

	printf("Unesite ID igraca kojeg zelite obrisati: ");

	do {
		scanf("%d", &trazeniId);
		if (trazeniId < 1 || trazeniId > brojIgraca) {
			printf("Igrac s unesenim ID-em ne postoji. Unesite ID koji postoji: ");
		}
		if ((poljeIgraca + trazeniId - 1)->ozljeda   == 1) {
			printf("Igrac s unesenim ID-em trenutno je ozljedjen.\n");
			return;
		}
	} while (trazeniId < 1 || trazeniId > brojIgraca || (poljeIgraca + trazeniId - 1)->ozljeda == 1);

	IGRAC* pomocnoPolje = (IGRAC*)calloc(brojIgraca - 1, sizeof(IGRAC));

	int counter = 0;

	for (i = 0; i < brojIgraca; i++) {

		if (trazeniId != (poljeIgraca + i)->id) {
			*(pomocnoPolje + counter) = *(poljeIgraca + i);

			if ((pomocnoPolje + counter)->id > trazeniId) {
				(pomocnoPolje + counter)->id -= 1;
			}

			fwrite((pomocnoPolje + counter), sizeof(IGRAC), 1, fp);
			counter++;
		}
	}

	free(pomocnoPolje); //16
	pomocnoPolje = NULL;

	rewind(fp);

	fwrite(&counter, sizeof(int), 1, fp);
	fclose(fp);

	printf("Igrac je uspjesno obrisan\n");
}



void brisanjeDatoteke_Igraci(const char* datIgrac){

	FILE* fp = fopen(datIgrac, "rb");
	int status;
	if (fp == NULL) {
		printf("Datoteka %s ne postoji na disku\n", datIgrac);
		return;
	}
	else {
		fclose(fp);
	}
	//19
	status = remove(datIgrac);
	if (status == 0) {
		printf("Uspjesno obrisana datoteka!\n");
	}
	else {
		printf("Nemogucnost brisanja datoteke!\n");
	}
}





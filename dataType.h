#define _CRT_SECURE_NO_WARNINGS
#ifndef DATATYPE_H
#define DATATYPE_H
#define Ime_Length 30
#define Prezime_Length 20
#define Pozicija_Length 10
#define Oib_Length 11

//1
//2
//3
//11
//13
typedef struct igrac {
	int id;
	char ime[Ime_Length];
	char prezime[Prezime_Length];
	char pozicija[Pozicija_Length];
	char oib[Oib_Length];
    int ozljeda;
	int brojPoena;
	int brojAsistencija;
	int brojSkokova;
	int brojUtakmica;
	double prosjekPoena;
	double prosjekAsistencija;
	double prosjekSkokova;

}IGRAC;

typedef enum {
    DODAVANJE_NOVIH_IGRACA = 1,
    ISPISIVANJE_IGRACA,
    PRETRAZIVANJE_IGRACA_PREZIME,
    SORTIRANJE_IGRACA_PO_POENIMA_SILAZNO,
	SORTIRANJE_IGRACA_PO_UTAKMICAMA,
    PRETRAZIVANJE_OZLJEDJENIH_IGRACA,
    AZURIRANJE_IGRACA,
    BRISANJE_IGRACA,
    BRISANJE_DATOTEKA_IGRACI,
    IZLAZ_IZ_PROGRAMA
} OpcijeIzbornika;

#endif //DATATYPE_H
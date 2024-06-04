//6
#define _CRT_SECURE_NO_WARNINGS
#ifndef HEADER_H
#define HEADER_H
#include "dataType.h"

static inline int compare(const void *p1, const void *p2);
int izbornik(const char* const datIgrac);
void kreiranjeDatoteke_Igraci(const char* const datIgrac);
void dodajIgraca(const char* const datIgrac);
IGRAC* ucitavanjeIgraca(const char* const datIgrac);
void ispisivanjeIgraca(const IGRAC* const poljeIgraca);
void pronadiIgracaPrezime(IGRAC* const poljeIgraca);
void azuriranjeIgraca(IGRAC* poljeIgraca, const char* const datIgrac);
void zamjena(IGRAC* const veci, IGRAC* const manji);
const IGRAC* sortirajPoPoenima(const IGRAC* poljeIgraca);
void ispisiSortiraneIgraceSilazno(const IGRAC* poljeIgraca);
void SortirajUtakmice(IGRAC* poljeIgraca);
void ispisiOzljedjeneIgrace(IGRAC* const poljeIgraca);
void brisanjeIgraca(IGRAC* const poljeIgraca, const char* const datIgrac);
void brisanjeDatoteke_Igraci(const char* datIgrac);
static int brojIgraca;

#endif //HEADER_H

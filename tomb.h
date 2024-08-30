#ifndef TOMB_H_INCLUDED
#define TOMB_H_INCLUDED

typedef struct Szerviz {
    char nev[20+1],elerhetoseg[12+1],rendszam[7+1],tipus[13+1],evjarat[4+1],vizsga[11+1],javitas[20+1],datum[11+1],ar[8+1];
    bool torles;/*Adattorles a fileba visszairaskor tortenik, ilyenkor az adott sor torles valtozoja igaz lesz, es a program bezarasakor nem mentodik el a fileba.*/
}Szerviz;

extern Szerviz* tomb;

bool vizsgalejarat(int napok,int meret);
bool autotorles(char* rendszam,int meret);
bool ugyfel_keres(char* ugyfel,int meret);
bool rendszam_keres(char* rendszam,int meret);
int adatrogzites_tombbe(Szerviz ujelem,int sorszam);
bool tomb_atmeretez(Szerviz ujelem,int ujmeret);

#endif



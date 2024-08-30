#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "debugmalloc.h"
#include "fileok.h"
#include "console.h"
#include "tomb.h"

Szerviz* tomb;

int file_sorok(void){
    FILE* file;
    file = fopen("Szerviz.txt","r");
    if(file == NULL){
        perror("Fajl megnyitasa sikertelen");
        return -1;
    }
    char karakter;
    fscanf(file,"%c",&karakter);
    int sorok = 0;
    while (fscanf(file,"%c", &karakter) == 1)
        if(karakter == '\n')
            ++sorok;
    return sorok;
}

/*Megnyitja a szerviz filet, es ameddig van adat, addig irja a szerviz tombot tele adattal.
A fuggveny akkor ad igaz erteket, ha a filet sikerult megnyitni.*/
int betoltes(int meret){
    FILE* file;
    file = fopen("Szerviz.txt","r");
    if(file == NULL){
        perror("Fajl megnyitasa sikertelen");
        return -1;
    }
    tomb = (Szerviz*) malloc(sizeof(Szerviz)*meret);
    Szerviz sor;
    for(int i = 0;fscanf(file,"%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n",  sor.nev,sor.elerhetoseg,sor.rendszam,sor.tipus,sor.evjarat,sor.vizsga,sor.javitas,sor.datum,sor.ar) != EOF; ++i)
    {
    tomb[i]=sor;
    }
    return meret;
}

bool mentes(int meret){
    FILE* file;
    file = fopen("Szerviz.txt","w");
    if(file == NULL){
        perror("Fajl megnyitasa sikertelen");
        fclose(file);
        return false;
    }
    for(int i = 0; i < meret; ++i)
        if(!tomb[i].torles){
            fprintf(file,"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",tomb[i].nev,tomb[i].elerhetoseg,tomb[i].rendszam,tomb[i].tipus,tomb[i].evjarat,tomb[i].vizsga,tomb[i].javitas,tomb[i].datum,tomb[i].ar);
        }
    fclose(file);
    return true;
}



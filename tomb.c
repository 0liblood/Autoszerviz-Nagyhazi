#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "debugmalloc.h"
#include "fileok.h"
#include "console.h"
#include "tomb.h"

Szerviz* tomb;

int adatrogzites_tombbe(Szerviz ujelem,int sorszam){
    sorszam++;
    tomb_atmeretez(ujelem,sorszam);
    if(!tomb_atmeretez(ujelem,sorszam))
        return -1;
    return sorszam;
    }

bool vizsgalejarat(int napok,int meret){
    int vizsgaev,vizsgahonap,vizsganapok;
    bool kiiras = false;/*egyszer irja csak ki a gridet, ne minden sor kiiasakor*/
    for(int i = 0; i < meret; ++i){
        sscanf(tomb[i].vizsga, "%4d.%2d.%2d", &vizsgaev,&vizsgahonap,&vizsganapok);
        vizsganapok+=vizsgahonap*30+vizsgaev*365;/*mivel a felhasznalo altal beirt datumot is igy szamoljuk, ezert nem okoz hibat a 30-al valo szorzas.*/
        if(vizsganapok - napok < 30 && vizsganapok - napok > 0){
            if(!kiiras){
                printf("\n30 napon belul lejar a forgalmijuk:\n");
                kiiras = true;
                printf("\n\n%-20s|%-12s|%-8s|%-13s|%-7s|%-11s|\n","Nev","Elerhetoseg","Rendszam","Tipus","Evjarat","Vizsga");
                for(int i = 0;i<77;++i)
                    printf("-");
            }
            if(!tomb[i].torles)
                printf("\n%-20s|%-12s|%-8s|%-13s|%-7s|%-11s|",tomb[i].nev,tomb[i].elerhetoseg,tomb[i].rendszam,tomb[i].tipus,tomb[i].evjarat,tomb[i].vizsga);
        }
    }
    return kiiras;
}

bool tomb_atmeretez(Szerviz ujelem,int ujmeret) {
    Szerviz* ujtomb = (Szerviz*) malloc(sizeof(Szerviz) * ujmeret);
    if (ujtomb == NULL)
        return false;
    for (int i = 0; i < ujmeret-1; ++i)
        ujtomb[i]=tomb[i];
    free(tomb);
    ujtomb[ujmeret-1] = ujelem;
    tomb = ujtomb;
    return true;
}

bool autotorles(char* rendszam,int meret){
    bool talalat = false;
    for(int i = 0; i < meret; ++i){
        if(strcmp(strupr(rendszam),strupr(tomb[i].rendszam))==0){
            tomb[i].torles = true;
            talalat = true;
        }
    }
    return talalat;
}

bool ugyfel_keres(char* ugyfel,int meret){
    bool talalat = false;
    int db = 0;
    for(int i = 0; i < meret; ++i){
        if(strcmp(strupr(ugyfel),strupr(tomb[i].nev)) == 0){
            ++db;
            if(!talalat){
                printf("\n\n%-20s|%-12s|%-8s|%-13s|%-7s|%-11s|%-20s|%-11s|%-8s|\n","Nev","Elerhetoseg","Rendszam","Tipus","Evjarat","Vizsga","Javitas","Datum","Ar");
                for(int i = 0;i<119;++i)
                    printf("-");
            }
            talalat = true;
            sort_kiir(i);
        }
    }
    printf("\n\nTalalatok szama: %d\n\n",db);
    return talalat;
}

bool rendszam_keres(char* rendszam,int meret){
    bool talalat = false;
    int db = 0;
    for(int i = 0; i < meret ; ++i){
        if(strcmp(strupr(rendszam),strupr(tomb[i].rendszam))==0){
            ++db;
            if(!talalat){
                printf("\n\n%-20s|%-12s|%-8s|%-13s|%-7s|%-11s|%-20s|%-11s|%-8s|\n","Nev","Elerhetoseg","Rendszam","Tipus","Evjarat","Vizsga","Javitas","Datum","Ar");
                for(int i = 0;i<119;++i)
                    printf("-");
            }
            talalat = true;
            sort_kiir(i);
        }
    }
    printf("\n\nTalalatok szama: %d\n\n",db);
    return talalat;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "fileok.h"
#include "tomb.h"
#include "debugmalloc.h"

Szerviz* tomb;


int adatrogzites(int meret){
    printf("\n---Adatrogzites---\n\nIrja be az adatokat, ha valamelyik hianyzik, akkor kotojelet irjon a helyere!\n\n\t1. Ugyfel neve(max 20 karakter): ");
    Szerviz ujelem;
    gets(ujelem.nev);
    printf("\t2. Ugyfel telefonszama(max 12 karakter): ");
    gets(ujelem.elerhetoseg);
    printf("\t3. Gepjarmu rendszama(max 8 karakter): ");
    gets(ujelem.rendszam);
    printf("\t4. Gepjarmu tipusa(max 13 karakter): ");
    gets(ujelem.tipus);
    printf("\t5. Gepjarmu evjarata(max 7 karakter): ");
    gets(ujelem.evjarat);
    printf("\t6. Forgalmi vizsga ervenyessege eeee.hh.nn formatumban(max 11 karakter): ");
    gets(ujelem.vizsga);
    printf("\t7. Gepjarmuvon elvegzett javitas(max 20 karakter): ");
    gets(ujelem.javitas);
    printf("\t8. Javitas datuma eeee.hh.nn formatumban(max 11 karakter): ");
    gets(ujelem.datum);
    printf("\t9. Javitas koltsege forintban(max 8 karakter): ");
    gets(ujelem.ar);

    int regimeret = meret;
    meret = adatrogzites_tombbe(ujelem, meret);
    if(regimeret+1 == meret){
        printf("\nSikeres adatrogzites.\n");
        return meret;
    }
    return meret;
}

bool tombot_kiir(int meret){
    if(meret == -1){
        printf("\nHiba tortent a file betoltese kozben.\n");
        return false;
    }
    if(meret > 0){
        printf("\n%-20s|%-12s|%-8s|%-13s|%-7s|%-11s|%-20s|%-11s|%-8s|\n","Nev","Elerhetoseg","Rendszam","Tipus","Evjarat","Vizsga","Javitas","Datum","Ar");
        for(int i = 0;i<119;++i)
            printf("-");
    }
    else
        printf("\nNincs megjelenitheto adat\n");
    for(int i = 0; i<meret;i++)
        if(!tomb[i].torles)
            printf("\n%-20s|%-12s|%-8s|%-13s|%-7s|%-11s|%-20s|%-11s|%-8s|",tomb[i].nev,tomb[i].elerhetoseg,tomb[i].rendszam,tomb[i].tipus,tomb[i].evjarat,tomb[i].vizsga,tomb[i].javitas,tomb[i].datum,tomb[i].ar);
    printf("\n");
    return true;
}

void sort_kiir(int sorszam){
    printf("\n%-20s|%-12s|%-8s|%-13s|%-7s|%-11s|%-20s|%-11s|%-8s|",tomb[sorszam].nev,tomb[sorszam].elerhetoseg,tomb[sorszam].rendszam,tomb[sorszam].tipus,tomb[sorszam].evjarat,tomb[sorszam].vizsga,tomb[sorszam].javitas,tomb[sorszam].datum,tomb[sorszam].ar);
    return;
}

bool kereses(int meret){
    if(meret == -1){
        printf("\nHiba tortent a file betoltese kozben.\n");
        return false;
    }
    bool futas = true;
    while(futas){
        printf("\n\t[R] - Rendszam alapjan keres\n\t[U] - Ugyfel alapjan keres\n\t[V] - Visszalepes\n\n");
        char bemenet;
        scanf("%c",&bemenet);
        tolower(bemenet);/*kis es nagybeuket egyfogman kezeli*/
        while (getchar() != '\n')
                        ;
        switch(bemenet){
    case'r':
        printf("\nIrja be a keresni kivant rendszamot!\n");
        char rendszam[8];
        scanf("%s", rendszam);
        if(!rendszam_keres(rendszam,meret))
            printf("\nNincs talalat.\n");
        return true;
    case'u':
        printf("\nIrja be a keresni kivant ugyfelet!\n");
        char ugyfel[30];
        char karakter;
        int i = 0;
        scanf("%c",&karakter);
        while(karakter!= '\n'){
            ugyfel[i++]=karakter;
            scanf("%c",&karakter);
        }
        ugyfel[i]='\0';
        if(!ugyfel_keres(ugyfel,meret))
            printf("\nNincs talalat.\n");
        return true;
    case'v':
        printf("\nVisszalepes.\n");
        return false;
    default:
        printf("\nNincs ilyen opcio, probalja ujra!\n");
        break;
        }
    }
    return true;
}

bool vizsga(int meret){
    if(meret == -1){
        printf("\nHiba tortent a file betoltese kozben.\n");
        return false;
    }
    printf("\nIrjon be egy datumot eeee.hh.nn formatumban!\n");
    int ev,honap,nap;
    scanf("%4d.%2d.%2d", &ev,&honap,&nap);
    nap+=honap*30+ev*365;
    if(!vizsgalejarat(nap,meret))
        printf("\nSenkinek sem jar le 30 napon belul a forgalmija.\n");
    return true;
}

bool torles(int meret){
    if(meret == -1){
        printf("\nHiba tortent a file betoltese kozben.\n");
        return false;
    }
    printf("\nIrja be a torolni kivant rendszamot!\n");
        char rendszam[8];
        scanf("%s", rendszam);
        if(autotorles(rendszam,meret))
            printf("\nSikeres torles.\n");
        else{
            printf("\nNincs talalat.\n");
            return false;
        }
    return true;
}

void kilepes(int meret){
    printf("\nSzeretne menteni?\n\t[i] - igen\n\t[n] - nem\n");
    char bemenet;
    scanf("%c",&bemenet);
    if(bemenet == 'i')
        if(mentes(meret))
            printf("\nSikeres mentes.\n");
        else
            printf("\nHiba a file megnyitasakor, probalja ujra.\n");
    else
        return;
}

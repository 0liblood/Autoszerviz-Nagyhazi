#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "fileok.h"
#include "debugmalloc.h"
#include "console.h"
#include "tomb.h"

Szerviz* tomb;


int main()
{
    printf("\n\n       ###    ##     ## ########  #######   ######  ######## ######## ########  ##     ## #### ######## \n      ## ##   ##     ##    ##    ##     ## ##    ##      ##  ##       ##     ## ##     ##  ##       ##  \n     ##   ##  ##     ##    ##    ##     ## ##           ##   ##       ##     ## ##     ##  ##      ##   \n    ##     ## ##     ##    ##    ##     ##  ######     ##    ######   ########  ##     ##  ##     ##    \n    ######### ##     ##    ##    ##     ##       ##   ##     ##       ##   ##    ##   ##   ##    ##     \n    ##     ## ##     ##    ##    ##     ## ##    ##  ##      ##       ##    ##    ## ##    ##   ##      \n    ##     ##  #######     ##     #######   ######  ######## ######## ##     ##    ###    #### ######## \n");
    bool futas = true;
    int sorok = file_sorok();
    betoltes(sorok);
    while(futas){
        printf("\n\nMit szeretne tenni?\n\n\t[A] - Adatrogzites\n\t[L] - Osszes adat listazasa\n\t[K] - Kereses\n\t[V] - Lejaro vizsgak kiirasa\n\t[T] - Torles\n\t[M] - Mentes\n\t[X] - Kilepes a programbol\n\n");
        char bemenet;
        scanf("%c",&bemenet);
        while(bemenet==' ' || bemenet == '\n')
        scanf("%c",&bemenet);
        while (getchar() != '\n')
                ;
        tolower(bemenet);/*kis es nagybeuket egyfogman kezeli*/
        switch(bemenet) {
        case 'a':;
            sorok = adatrogzites(sorok);/*Ha az adatrogzites fuggveny false ertekkel ter vissza, akkor ujrahivja a main() fuggvenyt, ezaltal a program az elejerol kezd mindent.*/
            if(sorok == -1)
                printf("\nHiba tortent\n");
            break;
        case 'l':;
            tombot_kiir(sorok);
            break;
        case 'k':
            kereses(sorok);
            break;
        case 'v':
            vizsga(sorok);
            break;
        case 't':
            torles(sorok);
            break;
        case 'm':
            if(mentes(sorok))
                printf("\nSikeres mentes.\n");
            else
                printf("\nHiba a file megnyitasakor, probalja ujra.\n");
            break;
        case 'x':
            kilepes(sorok);
            futas = false;
            break;
        default:
            printf("\nNincs ilyen lehetoseg, probalja ujra.\n");
            break;
        }
    }
    free(tomb);/*Itt szabaditunk fel*/
    debugmalloc_log_file("memoria.txt");
    return 0;
}

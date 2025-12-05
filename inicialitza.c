#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcions_auxiliars.h"
#include "definicions.h"


Node* InicialitzaNode() {
    Node *p = calloc(1,sizeof(Node));
    p->nfil=-1;
    p->ncol=-1;
    p->fills = NULL;

    return p;
}

int CaraoCreuInicial() {

    printf("\nJuguem a cara o creu per veure qui juga primer.\n\n   1 - CARA\n   2 - CREU\n\n");
    int x,y;

    srand(time(NULL));

    int r=rand() % 2 + 1;
    while (1) {
        printf("Escriu 1 si vols CARA o 2 si vols CREU: ");
        y=LlegirEnter(&x);

        if(y==1) {
            if (x==1) {
                printf("\nHas escollit CARA i ");
                break;
            }
            else if (x==2) {
                printf("\nHas escollit CREU i ");
                break;
            }
            else printf("No has introduit 1 o 2.\n\n");
        }
        else if (y==-1) printf("Error: No has introduit un enter.\n\n");
        else if (y==0) printf("Error de lectura.\n");
    }

    if(r==1 && x==1) printf("ha sortit CARA. Per tant, en primer lloc juga l'huma.\n\n");
    else if(r==2 && x==1) printf("ha sortit CREU. Per tant, en primer lloc juga la CPU.\n\n");
    else if(r==1 && x==2) printf("ha sortit CARA. Per tant en primer lloc juga la CPU.\n\n");
    else printf("ha sortit CREU. Per tant, en primer lloc juga l'huma.\n\n");

    if (x==r) return 1;
    else return 2;
}

int TriaMode() {
    int x,y;
    printf("Quin mode de joc vols jugar?\n\n   1 - Huma vs Huma\n   2 - Huma vs CPU\n\n");
     while (1) {
        printf("Escriu 1 si vols el Mode Huma vs Huma i 2 si vols el Mode Huma vs CPU: ");
        y=LlegirEnter(&x);

        if(y==1) {
            if (x==1) {
                printf("\nHas escollit el Mode Huma vs Huma.\n\n");
                break;
            }
            else if (x==2) {
                printf("\nHas escollit el Mode Huma vs CPU.\n\n");
                break;
            }
            else printf("No has introduit 1 o 2.\n\n");
        }
        else if (y==-1) printf("Error: No has introduit un enter.\n\n");
        else printf("Error de lectura.\n");
    }
    return x;
}

int TriaModeDificultat() {
    int x,y;
    printf("Quin mode de dificultat vols per a la CPU?\n\n   1 - Facil\n   2 - Normal\n   3 - Dificil\n   4 - Impossible\n\n");
    while (1) {
        printf("Escriu 1 si vols el Mode Facil, 2 si vols el Mode Normal, 3 si vols el Mode Dificil i 4 si vols el Mode Impossible: ");
        y=LlegirEnter(&x);

        if(y==1) {
            if (x==1) {
                printf("\nHas escollit el Mode Facil.\n\n");
                break;
            }
            else if (x==2) {
                printf("\nHas escollit el Mode Normal.\n\n");
                break;
            }
            else if (x==3) {
                printf("\nHas escollit el Mode Dificil.\n\n");
                break;
            }
            else if (x==4) {
                printf("\nHas escollit el Mode Impossible.\n\n");
                break;
            }
            else printf("No has introduit 1, 2, 3 o 4.\n\n");
        }
        else if (y==-1) printf("Error: No has introduit un enter.\n\n");
        else printf("Error de lectura.\n");
    }
    return x;
}

int PrimerJugador(int *njug) {
    printf("Qui vols que comenci?\n\n   1 - Jugador Huma\n   2 - CPU\n   3 - Ho decidim a Cara o Creu\n\n");
    int x,y;
    while (1) {
        printf("Escriu 1 si vols tirar primer tu, 2 si vols que comenci la CPU \
o 3 si vols jugar a cara o creu per veure qui tira primer: ");
        y=LlegirEnter(&x);

        if(y==1) {
            if (x==1) {
                printf("\nHas escollit tirar primer.\n\n");
                *njug=1;
                return 0;
            }
            else if (x==2) {
                printf("\nHas escollit que tiri primer la CPU.\n\n");
                *njug=2;
                return 0;
            }
            else if (x==3) {
                *njug=CaraoCreuInicial();
                return 1;
            }
            else printf("No has introduit 1, 2 o 3.\n\n");
        }
        else if (y==-1) printf("Error: No has introduit un enter.\n\n");
        else printf("Error de lectura.\n");
    }
    return -1;
}
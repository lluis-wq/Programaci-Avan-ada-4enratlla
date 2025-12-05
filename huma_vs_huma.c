#include <stdio.h>
#include <stdlib.h>
#include "funcions_auxiliars.h"
#include "heuristica.h"
#include "definicions.h"


void FinalitzaPartidaHumavsHuma(char m[N][M], int njug, int nfil, int ncol) {
    if (AcabaPartida(m,njug,nfil,ncol)== 3) printf("Empat, no queden caselles lliures.\n");
    else printf("Ha guanyat el jugador %d.\n",njug);
}

void JugadaHumavsHuma(char m[N][M],int *njug, int *nfil, int *ncol) {
    int x,y;
    while (1) {
        printf("Juga el Jugador %d\n\nEn quina columna vols posar la fitxa (de la 1 a la %d): ",*njug,M);
        y = LlegirEnter(&x);
        if(y==0) printf("Error de lectura.\n");
        else if(y==-1) printf("Error: Columna no valida. Es necessari introduir un unic enter.\n\n");
        else if(y==1) break;
    }

    if (ComprobacioColumna(m,x)==-1) printf("Error: Columna fora del rang (1-%d).\n\n",M);
    else if (ComprobacioColumna(m,x)==0) printf("Error: La columna esta plena.\n\n");
    else if (ComprobacioColumna(m,x)==1) {
        ColocaFitxa(m,x,*njug,nfil,ncol);
        ImprimeixTauler(m);
        MissatgeColocaFitxaHumavsHuma(*njug,*nfil,*ncol);
    }
}

void JugaPartidaHumavsHuma(char m[N][M], int *njug, int *nfil, int *ncol) {
    printf("NOTA: El jugador 1 juga amb creus 'x' i el jugador 2 amb cercles 'o'.\n\nINICIA LA PARTIDA:\n\n");
    while(1) {
        JugadaHumavsHuma(m,njug,nfil,ncol);
        if(AcabaPartida(m,*njug,*nfil,*ncol)!=0) break;
        CambiaJug(njug);
    }
}
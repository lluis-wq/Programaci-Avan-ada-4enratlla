#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "funcions_auxiliars.h"
#include "arbre.h"
#include "heuristica.h"
#include "definicions.h"



void JugadaHuma(char m[N][M], int *njug, int *nfil, int *ncol) {
    int x,y;
    while (1) {
        printf("Torn del Jugador huma:\n\nEn quina columna vols posar la fitxa (de la 1 a la %d): ",M);
        y = LlegirEnter(&x);
        if(y==1) {
            int c=ComprobacioColumna(m,x);
            if(c==-1) printf("Error: Columna fora del rang (1-%d).\n\n",M);
            else if(c==0) printf("Error: La columna esta plena.\n\n");
            else break;
        }
        else if(y==-1) printf("Error: Columna no valida. Es necessari introduir un unic enter.\n\n");
        else printf("Error de lectura.\n");
    }
    ColocaFitxa(m,x,*njug,nfil,ncol);
    ImprimeixTauler(m);
    MissatgeColocaFitxaHumavsCPU(*njug,*nfil,*ncol);
}

void ModeFacilRandom (Node *p, int *njug) {
    int r=rand() % M + 1;
    ColocaFitxa(p->tauler,r,2,&(p->nfil),&(p->ncol));
    ImprimeixTauler(p->tauler);
    MissatgeColocaFitxaHumavsCPU(*njug,p->nfil,p->ncol);
}

void RecorreArbreRec(Node *p,int n) {
    if(p->n_fills==0) {
        return;
    }
    for(int i=0; i<M; i++) {
        if(p->fills[i]!=NULL && p->fills[i]->valor!=INT_MAX && p->fills[i]->valor!=INT_MIN) {
            RecorreArbreRec(p->fills[i],n+1);
        }
    }   
    if(n%2 == 1) {
        int extra;
        TrobaMinimIndexValor(p,&extra);
    }
    else {
        int extra;
        TrobaMaximIndexValor(p,&extra);
    }
}

int PrimerMovimentCPUDificil() {
    if(M <= (2*(NENRATLLA-1)) && M%2 == 0) {
        int r = rand() % 2;
        return r + M/2 - 1;
    }        
    else if (M <= (2*(NENRATLLA-1)) && M%2 != 0) {
        return (M-1)/2;
    }
    else { 
        int r=rand() % (M - 2*(NENRATLLA-1));
        return r + (NENRATLLA-1);
    }
}


void ModeDificilMinMax(Node *p, int *njug, int nivells) {
    int index;
    if(p->nfil==-1) {
        index = PrimerMovimentCPUDificil();
        ColocaFitxa(p->tauler,index+1,*njug,&(p->nfil),&(p->ncol));
    }
    else {
        int k=0;
        CreaArbreRec(p,k,nivells);
        if(GuanyemSegMov(*p)!=-1) index=GuanyemSegMov(*p);
        else {
            RecorreArbreRec(p,0);
            TrobaMaximIndexValor(p,&index);
        }
        Node *a = p->fills[index];
        AlliberaArbreRecSensePareNiIndex(p,index);
        CopiaParcialNode(a,p);
        free(p->fills);
        free(a);
        p->n_fills=0;
        p->fills=NULL;
    }
    ImprimeixTauler(p->tauler);
    MissatgeColocaFitxaHumavsCPU(*njug,p->nfil,p->ncol);
}

void JugadaCPU(Node *a, int *njug, int dificultat, int inici, int *nivellimp) {
    if (inici == 0) srand(time(NULL));
    printf("Torn de la CPU:\n\n");
    if(dificultat==1) {
        ModeFacilRandom(a,njug);
    }
    if(dificultat==2) {
        int nivells = 2;
        ModeDificilMinMax(a,njug,nivells);
    }
    if(dificultat==3) {
        int nivells=4;
        ModeDificilMinMax(a,njug,nivells);
    }
    if(dificultat==4) {
        int l = a->nfil;
        clock_t t0 = clock();
        ModeDificilMinMax(a,njug,*nivellimp);
        clock_t t1 = clock();
        double tempstotal = ((double)(t1 - t0)) / CLOCKS_PER_SEC;
        CanviaNivell(nivellimp,tempstotal,l,a->valor);
    }
}

void JugaPartidaHumavsCPU(Node *a, int *njug, int dificultat, int inici) {
    printf("NOTA: El jugador huma juga amb creus 'x' i la CPU amb cercles 'o'.\n\nINICIA LA PARTIDA:\n\n");
    int nivellimp = 7; 
    while (1){
        if(*njug==1) JugadaHuma(a->tauler,njug,&(a->nfil),&(a->ncol));
        else if(*njug==2) JugadaCPU(a,njug,dificultat,inici,&nivellimp);
        if (AcabaPartida(a->tauler,*njug,a->nfil,a->ncol)!=0) break;
        CambiaJug(njug);
    }
}

void FinalitzaPartidaHumavsCPU(Node *a, int njug) {
    if (AcabaPartida(a->tauler,njug,a->nfil,a->ncol)== 3) printf("Empat, no queden casilles lliures.\n");
    else if (njug==1) printf("Ha guanyat el jugador huma.\n");
    else printf("Ha guanyat la CPU\n");
    free(a);
}
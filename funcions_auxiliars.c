#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "definicions.h"

void OmpleCharDeZeros(char m[M]) {
    for (int j=0;j<M;j++) {
        m[j]=0;
    }
}

void OmpleTaulerDeZeros(char m[N][M]){
    for (int i=0;i<N;i++) {
        for(int j=0;j<M;j++){
            m[i][j] = 0;
        }
    }
}

void CopiaTauler(char m[N][M], char n[N][M]) {
    for (int i=0;i<N;i++) {
        for(int j=0;j<M;j++){
            n[i][j] = m[i][j];
        }
    }
}

void CopiaParcialNode(Node *p, Node *a) {
    CopiaTauler(p->tauler,a->tauler);
    a->nfil=p->nfil;
    a->ncol=p->ncol;
    a->valor=p->valor;
}

void ImprimeixTauler(char m[N][M]) {
    printf("Imprimim tauler...\n");
    char t[N][M];
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            if(m[i][j]==0) t[i][j]='.';
            if(m[i][j]==1) t[i][j]='x';
            if(m[i][j]==2) t[i][j]='o';
        }
    }

    printf("\n");
    for (int j=0;j<M;j++) {
        printf(" %d", j+1);
    }
    printf("\n");

    for (int i=N-1;i>=0;i--) {
        for (int j=0;j<M;j++) {
            printf(" %c", t[i][j]);
        }
        printf(" \n");
    }
    printf(" \n\n");
}


void TrobaMaximIndexValor(Node *p, int *index) {
    int valor;
    int profunditat;
    int count = 0;
    for (int i=0;i<M;i++) {
        if(p->fills[i]!=NULL) {
            if(count == 0) {
                *index = i;
                valor = p->fills[i]->valor;
                profunditat = p->fills[i]->profunditat;
                count = 1;
            }

            if(p->fills[i]->valor > valor) {
                *index = i;
                valor = p->fills[i]->valor;
                profunditat = p->fills[i]->profunditat;
                
            }
            else if(p->fills[i]->valor == valor) {
                if(valor == INT_MAX || valor == INT_MIN) {
                    if(p->fills[i]->profunditat < p->fills[*index]->profunditat) {
                        *index = i;
                        profunditat = p->fills[i]->profunditat;
                    }
                }
            }
        }
    }
    p->valor = valor;
    p->profunditat = profunditat;
} 

void TrobaMinimIndexValor(Node *p, int *index) {
    int valor;
    int profunditat;
    int count = 0;
    for (int i=0;i<M;i++) {
        if(p->fills[i]!=NULL) {
            if(count == 0) {
                *index = i;
                valor = p->fills[i]->valor;
                profunditat = p->fills[i]->profunditat;
                count = 1;
            }

            if(p->fills[i]->valor < valor) {
                *index = i;
                valor = p->fills[i]->valor;
                profunditat = p->fills[i]->profunditat;
                
            }
            else if(p->fills[i]->valor == valor) {
                if(valor == INT_MIN) {
                    if(p->fills[i]->profunditat > p->fills[*index]->profunditat) {
                        *index = i;
                        profunditat = p->fills[i]->profunditat;
                    }
                }
                if(valor == INT_MIN) {
                    if(p->fills[i]->profunditat > p->fills[*index]->profunditat) {
                        *index = i;
                        profunditat = p->fills[i]->profunditat;
                    }
                }
            }
        }
    }
    p->valor = valor;
    p->profunditat = profunditat;
} 

int GuanyemSegMov(Node p) {
    for (int i=0;i<M;i++) {
        if(p.fills[i]!=NULL) {
            if(p.fills[i]->valor == INT_MAX) {
                return i;

            }
        }
    }
    return -1;
}

int LlegirEnter (int *n) {
    char entrada[100];
    char extra;

    if(!fgets(entrada,sizeof(entrada),stdin)) {
        return 0;
    }

    if(sscanf(entrada," %d %c", n, &extra) == 1) {
        return  1;
    }
    else return -1;
}

void CambiaJug (int *njug) {
    if(*njug==1) *njug=2;
    else *njug=1;
}

void ColocaFitxa(char m[N][M], int x, int njug, int *nfil, int *ncol) {
    for (int i=0;i<N;i++) {
        if (m[i][x-1] == 0) {
            *nfil = i+1;
            *ncol = x;
            break;
        }
    }
    m[*nfil-1][*ncol-1] = njug;
}

void MissatgeColocaFitxaHumavsCPU(int njug, int nfil, int ncol) {
    if (njug == 1) printf("El Jugador huma coloca la fitxa a la columna %d .\nPer gravetat cau a la fila %d .\n\n", ncol,nfil);
    else printf("La CPU coloca la fitxa a la columna %d.\nPer gravetat cau a la fila %d .\n\n", ncol,nfil);
}

void MissatgeColocaFitxaHumavsHuma(int njug, int nfil, int ncol) {
    printf("El Jugador %d coloca la fitxa a la columna %d .\nPer gravetat cau a la fila %d .\n\n", njug, ncol,nfil);
}

int ComprobacioFila(char m[N][M], int x) {
    for (int i=0;i<N;i++) {
        if (m[i][x-1] == 0) {
            return 1;
        }
    }
    return 0;
}

int ComprobacioColumna (char m[N][M], int x) {
    if (x>0 && x<=M) return ComprobacioFila(m,x);
    else return -1;
}

void CanviaNivell(int *nivellimp, double tempstotal, int nfil, int valorminmax) {
    if(nfil != -1 && valorminmax!=INT_MAX && valorminmax!=INT_MIN) {
        int count = 0;
        double valor = 0.8;
        while(1) {
            if(tempstotal > valor) break;
            if(tempstotal <= valor) {
                valor = valor * valor;
                count = count + 1;
            }
        }
        *nivellimp = *nivellimp + count;
    }
}
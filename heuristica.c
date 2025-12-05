#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "definicions.h"


int kEnColumna (char m[N][M], int njug, int nfil, int ncol, int k, int *ffinal) {
    int n=0;

    for (int i=1; i<2*k;i++) {
        if(nfil-1-k+i<0 || nfil-1-k+i>=N) n=0;
        else if(m[nfil-1-k+i][ncol-1]==njug) n=n+1;
        else n=0;
        if (n==k) {
            *ffinal=nfil-1-k+i;
            return 1;
        }
    }
    *ffinal = -1;
    return 0;
}

int kEnFila (char m[N][M], int njug, int nfil, int ncol, int k, int *cfinal) {
    int n=0;

    for (int j=1; j<2*k;j++) {
        if(ncol-1-k+j<0 || ncol-1-k+j>=M) n=0;
        else if(m[nfil-1][ncol-1-k+j]==njug) n=n+1;
        else n=0;
        if (n==k) {
            *cfinal=ncol-1-k+j;
            return 1;
        }
    }
    *cfinal = -1;
    return 0;
}

int kEnDiagonalCreixent (char m[N][M], int njug, int nfil, int ncol, int k, int *ffinal, int *cfinal) {
    int n=0;

    for (int i=1; i<2*k;i++) {
        if (nfil-1-k+i<0 || nfil-1-k+i>=N || ncol-1-k+i<0 || ncol-1-k+i>=M) n=0;
        else if(m[nfil-1-k+i][ncol-1-k+i]==njug) n=n+1;
        else n=0;
        if (n==k) {
            *ffinal=nfil-1-k+i;
            *cfinal=ncol-1-k+i;
            return 1;
        }
    }
    *cfinal = -1;
    *ffinal = -1;
    return 0;
}

int kEnDiagonalDecreixent (char m[N][M], int njug, int nfil, int ncol, int k, int *ffinal, int *cfinal) {
    int n=0;

    for (int i=1; i<2*k;i++) {
        if (nfil-1+k-i<0 || nfil-1+k-i>=N || ncol-1-k+i<0 || ncol-1-k+i>=M) n=0;
        else if(m[nfil-1+k-i][ncol-1-k+i]==njug) n=n+1;
        else n=0;
        if (n==k) {
            *ffinal=nfil-1+k-i;
            *cfinal=ncol-1+k-i;
            return 1;
        }
    }
    return 0;
}

int AcabaPartida(char m[N][M], int njug, int nfil, int ncol) {
    int extra1;
    int extra2;

    if(kEnColumna(m,njug,nfil,ncol,NENRATLLA,&extra1)==1) return njug;

    if(kEnFila(m,njug,nfil,ncol,NENRATLLA,&extra2)==1) return njug;

    if(kEnDiagonalCreixent(m,njug,nfil,ncol,NENRATLLA,&extra1,&extra2)==1) return njug;

    if(kEnDiagonalDecreixent(m,njug,nfil,ncol,NENRATLLA,&extra1,&extra2)==1) return njug;


    int count=0;
    for (int j=0;j<M;j++) {
        if(m[N-1][j]!=0) count++;
    }
    if(count == M) return 3;

    return 0;
}

void ValoraColumna (char m[N][M], int njug, int i, int j, int *count) {
    int ffinal;

    for(int t=2; t<NENRATLLA;t++) {
        if(kEnColumna(m,njug,i+1,j+1,t,&ffinal)==1) {
            if(ffinal+1<N && m[ffinal+1][j]==0) *count = *count + 3*t*t;
        }
    }
}

void ValoraFila (char m[N][M], int njug, int i, int j, int *count) {
    int cfinal=0;

    for(int t=2; t<NENRATLLA;t++) {
        if(kEnFila(m,njug,i+1,j+1,t,&cfinal)==1) {
            if(cfinal+1<M && m[i][cfinal+1]==0) {
                if(i==0) {
                    if(t==NENRATLLA-2 && cfinal+2<M && m[i][cfinal+2]==njug) *count = *count + 3*(NENRATLLA-1)*(NENRATLLA-1);
                    else *count = *count + 3*t*t;
                }
                else if (m[i-1][cfinal+1]!=0) {
                    if(t==NENRATLLA-2 && cfinal+2<M && m[i][cfinal+2]==njug) *count = *count + 3*(NENRATLLA-1)*(NENRATLLA-1);
                    else *count = *count + 3*t*t;
                }
                else {
                    if(t==NENRATLLA-2 && cfinal+2<M && m[i][cfinal+2]==njug) *count = *count + (NENRATLLA-1)*(NENRATLLA-1);
                    else *count = *count + t*t;
                }
            }
            if(cfinal-t>=0 && m[i][cfinal-t]==0) {
                if(i==0) {
                    if(t==NENRATLLA-2 && cfinal-t-1<M && m[i][cfinal-t-1]==njug) *count = *count + 3*(NENRATLLA-1)*(NENRATLLA-1);
                    else *count = *count + 3*t*t;
                }
                else if (m[i-1][cfinal-t]!=0) {
                    if(t==NENRATLLA-2 && cfinal-t-1<M && m[i][cfinal-t-1]==njug) *count = *count + 3*(NENRATLLA-1)*(NENRATLLA-1);
                    else *count = *count + 3*t*t;
                }
                else {
                    if(t==NENRATLLA-2 && cfinal-t-1<M && m[i][cfinal-t-1]==njug) *count = *count + (NENRATLLA-1)*(NENRATLLA-1);
                    else *count = *count + t*t;
                }
            }
        }
    }
}


void ValoraDiagonalCreixent (char m[N][M], int njug, int i, int j, int *count) {
    int ffinal;
    int cfinal;

    for(int t=2;t<NENRATLLA;t++) {
        if(kEnDiagonalCreixent(m,njug,i+1,j+1,t,&ffinal,&cfinal)==1) {
            if(ffinal+1<N && cfinal+1<M && m[ffinal+1][cfinal+1]==0) {
                if(m[ffinal][cfinal+1]!=0) {
                    if(t==NENRATLLA-2 && ffinal+2<N && cfinal+2<M && m[ffinal+2][cfinal+2]==njug) *count = *count + 3*(NENRATLLA-1)*(NENRATLLA-1);
                    else *count = *count + 3*t*t;
                }
                else {
                    if(t==NENRATLLA-2 && ffinal+2<N && cfinal+2<M && m[ffinal+2][cfinal+2]==njug) *count = *count + (NENRATLLA-1)*(NENRATLLA-1);
                    else *count = *count + t*t;
                }
            }
            if(ffinal-t>=0 && cfinal-t>=0 && m[ffinal-t][cfinal-t]==0) {
                if(ffinal-t==0) *count = *count + 3*t*t;
                else if (m[ffinal-t-1][cfinal-t]!=0) {
                    if(t==NENRATLLA-2 && cfinal-t-1>=0 && m[ffinal-t-1][cfinal-t-1]==njug) *count = *count + 3*(NENRATLLA-1)*(NENRATLLA-1);
                    else *count = *count + 3*t*t;
                }
                else {
                    if(t==NENRATLLA-2 && cfinal-t-1>=0 && m[ffinal-t-1][cfinal-t-1]==njug) *count = *count + (NENRATLLA-1)*(NENRATLLA-1);
                    else *count = *count + t*t;
                }
            }
        }
    }
}

void ValoraDiagonalDecreixent(char m[N][M], int njug, int i, int j, int *count) {
    int ffinal;
    int cfinal;

        for(int t=2;t<NENRATLLA;t++) {
            if(kEnDiagonalDecreixent(m,njug,i+1,j+1,t,&ffinal,&cfinal)==1) {
                if(ffinal-1>=0 && cfinal+1<M && m[ffinal-1][cfinal+1]==0) {
                    if(ffinal-1==0) *count = *count + 3*t*t;
                    else if (m[ffinal-2][cfinal+1]!=0) {
                        if(t==NENRATLLA-2 && cfinal+2<M && m[ffinal-2][cfinal+2]==njug) *count = *count + 3*(NENRATLLA-1)*(NENRATLLA-1);
                        else *count = *count + 3*t*t;
                    }
                    else {
                        if(t==NENRATLLA-2 && cfinal+2<M && m[ffinal-2][cfinal+2]==njug) *count = *count + (NENRATLLA-1)*(NENRATLLA-1);
                        else *count = *count + t*t;
                    }
                }
                if(ffinal+t<N && cfinal-t>=0 && m[ffinal+1][cfinal-t]==0) {
                    if(m[ffinal+t-1][cfinal-t]!=0) {
                        if(t==NENRATLLA-2 && ffinal+t+1<N && cfinal-t-1>=0 && m[ffinal+t+1][cfinal-t-1]==njug) *count = *count + 3*(NENRATLLA-1)*(NENRATLLA-1);
                        else *count = *count + 3*t*t;
                    }
                    else {
                        if(t==NENRATLLA-2 && ffinal+t+1<N && cfinal-t-1>=0 && m[ffinal+t+1][cfinal-t-1]==njug) *count = *count + (NENRATLLA-1)*(NENRATLLA-1);
                        else *count = *count + t*t;
                    }
                }
            }
        }
}

int PuntsPosicioJug (char m[N][M], int njug) {
    int count=0;

    for (int i=0;i<N;i++) {
        for(int j=0;j<M;j++){
            if(m[i][j]==njug) {
                ValoraColumna(m,njug,i,j,&count);
                ValoraFila(m,njug,i,j,&count);
                ValoraDiagonalCreixent(m,njug,i,j,&count);
                ValoraDiagonalDecreixent(m,njug,i,j,&count);
            }
        }
    }
    return count;
}

int ValoraPosicioCPU (char m[N][M], int njug, int nfil, int ncol) {
    int resultat = AcabaPartida(m,njug,nfil,ncol);
    if(resultat == 3) return 0;
    else if(resultat == 1 && njug == 1) return INT_MIN;
    else if(resultat == 2 && njug == 2) return INT_MAX; 

    int p1=PuntsPosicioJug(m,1);
    int p2=PuntsPosicioJug(m,2);

    return p2-p1;
}
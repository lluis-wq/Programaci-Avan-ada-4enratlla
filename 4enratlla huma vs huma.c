#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define N 8
#define M 8
#define NEnRatlla 4

/* typedef struct node {
	struct node * *fills;
	int n_fills;
	char tauler[N][N];
	double valor;
} Node; */


void OmpleTaulerDeZeros(char m[N][M]){
    for (int i=0;i<N;i++) {
        for(int j=0;j<M;j++){
            m[i][j] = 0;
        }
    }
}

void ImprimeixTauler(char m[N][M]) {

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

int CaraoCreuInicial () {

    printf("Juguem a cara o creu per veure qui juga primer. \n\n");
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

    if(r==1) printf("ha sortit CARA.\n\nPer tant, ");
    else if(r==2) printf("ha sortit CREU.\n\nPer tant, ");

    if (x==r) return 1;
    else return 2;
}

void CambiaJug (int *njug) {
    if(*njug==1) *njug=2;
    else *njug=1;
}


int kEnColumna (char m[N][M], int njug, int nfil, int ncol, int k, int *ffinal) {
    int n=0;

    for (int i=1; i<2*k;i++) {
        if(nfil-1-k+i<0 || ncol-1-k+i>=N) n=0;
        else if(m[nfil-1-k+i][ncol-1]==njug) n=n+1;
        else n=0;
        if (n==k) {
            *ffinal=nfil-1-k+i;
            return 1;
        }
    }
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
    return 0;
}

int kEnDiagonalDecreixent (char m[N][M], int njug, int nfil, int ncol, int k, int *ffinal, int *cfinal) {
    int n=0;

    for (int i=1; i<2*k;i++) {
        if (nfil-1-k+i<0 || nfil-1-k+i>=N || ncol-1-k+i<0 || ncol-1-k+i>=M) n=0;
        else if(m[nfil-1+k-i][ncol-1-k+i]==njug) n=n+1;
        else n=0;
        if (n==k) {
            *ffinal=nfil-1-k+i;
            *cfinal=ncol-1+k-i;
            return 1;
        }
    }
    return 0;
}

int AcabaPartida(char m[N][M],int ntir, int njug, int nfil, int ncol) {
    CambiaJug(&njug);
    int extra1;
    int extra2;

    if(kEnColumna(m,njug,nfil,ncol,NEnRatlla,&extra1)==1) return njug;

    if(kEnFila(m,njug,nfil,ncol,NEnRatlla,&extra2)==1) return njug;

    if(kEnDiagonalCreixent(m,njug,nfil,ncol,NEnRatlla,&extra1,&extra2)==1) return njug;

    if(kEnDiagonalDecreixent(m,njug,nfil,ncol,NEnRatlla,&extra1,&extra2)==1) return njug;


    if (ntir == N*M) return 3;

    return 0;
}

void ValoraColumna (char m[M][N], int njug, int i, int j, int *count) {
    int ffinal;

    for(int t=2; t<NEnRatlla;t++) {
        if(kEnColumna(m,njug,i+1,j+1,t,&ffinal)==1) {
            if(ffinal+1<N && m[ffinal+1][j]==0) *count = *count + 3*t*t;
        }
    }
}

void ValoraFila (char m[M][N], int njug, int i, int j, int *count) {
    int cfinal;

    for(int t=2; t<NEnRatlla;t++) {
        if(kEnFila(m,njug,i+1,j+1,t,&cfinal)==1) {
            if(cfinal+1<M && m[i][cfinal+1]==0) {
                if(i==0) {
                    if(t==NEnRatlla-2 && cfinal+2<M && m[i][cfinal+2]==njug) *count = *count + 3*(NEnRatlla-1)*(NEnRatlla-1);
                    else *count = *count + 3*t*t;
                }
                else if (m[i-1][cfinal+1]!=0) {
                    if(t==NEnRatlla-2 && cfinal+2<M && m[i][cfinal+2]==njug) *count = *count + 3*(NEnRatlla-1)*(NEnRatlla-1);
                    else *count = *count + 3*t*t;
                }
                else {
                    if(t==NEnRatlla-2 && cfinal+2<M && m[i][cfinal+2]==njug) *count = *count + (NEnRatlla-1)*(NEnRatlla-1);
                    else *count = *count + t*t;
                }
            }
            if(cfinal-t>=0 && m[i][cfinal-t]==0) {
                if(i==0) {
                    if(t==NEnRatlla-2 && cfinal-t-1<M && m[i][cfinal-t-1]==njug) *count = *count + 3*(NEnRatlla-1)*(NEnRatlla-1);
                    else *count = *count + 3*t*t;
                }
                else if (m[i-1][cfinal-t]!=0) {
                    if(t==NEnRatlla-2 && cfinal-t-1<M && m[i][cfinal-t-1]==njug) *count = *count + 3*(NEnRatlla-1)*(NEnRatlla-1);
                    else *count = *count + 3*t*t;
                }
                else {
                    if(t==NEnRatlla-2 && cfinal-t-1<M && m[i][cfinal-t-1]==njug) *count = *count + (NEnRatlla-1)*(NEnRatlla-1);
                    else *count = *count + t*t;
                }
            }
        }
    }
}


void ValoraDiagonalCreixent (char m[N][M], int njug, int i, int j, int *count) {
    int ffinal;
    int cfinal;

    for(int t=2;t<NEnRatlla;t++) {
        if(kEnDiagonalCreixent(m,njug,i+1,j+1,t,&ffinal,&cfinal)==1) {
            if(ffinal+1<N && cfinal+1<M && m[ffinal+1][cfinal+1]==0) {
                if(m[ffinal][cfinal+1]!=0) {
                    if(t==NEnRatlla-2 && ffinal+2<N && cfinal+2<M && m[ffinal+2][cfinal+2]==njug) *count = *count + 3*(NEnRatlla-1)*(NEnRatlla-1);
                    else *count = *count + 3*t*t;
                }
                else {
                    if(t==NEnRatlla-2 && ffinal+2<N && cfinal+2<M && m[ffinal+2][cfinal+2]==njug) *count = *count + (NEnRatlla-1)*(NEnRatlla-1);
                    else *count = *count + t*t;
                }
            }
            if(ffinal-t>=0 && cfinal-t>=0 && m[ffinal-t][cfinal-t]==0) {
                if(ffinal-t==0) *count = *count + 3*t*t;
                else if (m[ffinal-t-1][cfinal-t]!=0) {
                    if(t==NEnRatlla-2 && cfinal-t-1>=0 && m[ffinal-t-1][cfinal-t-1]==njug) *count = *count + 3*(NEnRatlla-1)*(NEnRatlla-1);
                    else *count = *count + 3*t*t;
                }
                else {
                    if(t==NEnRatlla-2 && cfinal-t-1>=0 && m[ffinal-t-1][cfinal-t-1]==njug) *count = *count + (NEnRatlla-1)*(NEnRatlla-1);
                    else *count = *count + t*t;
                }
            }
        }
    }
}

void ValoraDiagonalDecreixent(char m[N][M], int njug, int i, int j, int *count) {
    int ffinal;
    int cfinal;

        for(int t=2;t<NEnRatlla;t++) {
            if(kEnDiagonalDecreixent(m,njug,i+1,j+1,t,&ffinal,&cfinal)==1) {
                if(ffinal-1>=0 && cfinal+1<M && m[ffinal-1][cfinal+1]==0) {
                    if(ffinal-1==0) *count = *count + 3*t*t;
                    else if (m[ffinal-2][cfinal+1]!=0) {
                        if(t==NEnRatlla-2 && cfinal+2<M && m[ffinal-2][cfinal+2]==njug) *count = *count + 3*(NEnRatlla-1)*(NEnRatlla-1);
                        else *count = *count + 3*t*t;
                    }
                    else {
                        if(t==NEnRatlla-2 && cfinal+2<M && m[ffinal-2][cfinal+2]==njug) *count = *count + (NEnRatlla-1)*(NEnRatlla-1);
                        else *count = *count + t*t;
                    }
                }
                if(ffinal+t<N && cfinal-t>=0 && m[ffinal+1][cfinal-t]==0) {
                    if(m[ffinal+t-1][cfinal-t]!=0) {
                        if(t==NEnRatlla-2 && ffinal+t+1<N && cfinal-t-1>=0 && m[ffinal+t+1][cfinal-t-1]==njug) *count = *count + 3*(NEnRatlla-1)*(NEnRatlla-1);
                        else *count = *count + 3*t*t;
                    }
                    else {
                        if(t==NEnRatlla-2 && ffinal+t+1<N && cfinal-t-1>=0 && m[ffinal+t+1][cfinal-t-1]==njug) *count = *count + (NEnRatlla-1)*(NEnRatlla-1);
                        else *count = *count + t*t;
                    }
                }
            }
        }
}

/* int PuntsPosicioJug (char m[M][N], int njug) {
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
} */

/* int ValoraPosicio (char m[N][M], int ntir, int njug, int nfil, int ncol) {

    if(AcabaPartida(m,ntir,njug,nfil,ncol)!=0) return INT_MAX;
    if(AcabaPartida(m,ntir,njug,nfil,ncol)==3) return 5;

    CambiaJug(&njug);

    int p1=PuntsPosicioJug(m,njug);
    CambiaJug(&njug);
    int p2=PuntsPosicioJug(m,njug);

    return p1-p2;
} */

int ComprobacioFila(char m[N][M], int x, int *nfil, int *ncol) {
    for (int i=0;i<N;i++) {
        if (m[i][x-1] == 0) {
            *nfil = i+1;
            *ncol = x;
            return 1;
        }
    }
    return 0;
}

int ComprobacioColumna (char m[N][M], int x, int *nfil, int *ncol) {
    if (x>0 && x<=M) return ComprobacioFila(m,x,nfil,ncol);
    else return -1;
}


void Jugada(char m[N][M], int *ntir, int *njug, int *nfil, int *ncol) {
    int x,y;
    while (1) {
        printf("Juga el Jugador %d\n\nEn quina columna vols posar la ficha (de la 1 a la %d): ",*njug,N);
        y = LlegirEnter(&x);
        if(y==0) printf("Error de lectura.\n");
        else if(y==-1) printf("Error: Columna no valida. Es necessari introduir un unic enter.\n\n");
        else if(y==1) break;
    }

    if (ComprobacioColumna(m,x,nfil,ncol)==-1) printf("Error: Columna fora del rang (1-%d).\n\n",N);
    else if (ComprobacioColumna(m,x,nfil,ncol)==0) printf("Error: La columna esta plena.\n\n");
    else if (ComprobacioColumna(m,x,nfil,ncol)==1) {
        m[*nfil-1][*ncol-1] = *njug;
        *ntir = *ntir +1;
        CambiaJug(njug);
        ImprimeixTauler(m);
        printf("Ficha colocada a la casella (%d,%d) .\n\n", *nfil,*ncol);
    }
}


int main(){

    char tauler[N][M];
    OmpleTaulerDeZeros(tauler);

    int ntir=0;
    int njug=CaraoCreuInicial();
    int nfil=1;
    int ncol;
    while (1){
        Jugada(tauler,&ntir,&njug,&nfil,&ncol);
        /* printf("ValPosicio = %d\n\n",ValoraPosicio(tauler,ntir,njug,nfil,ncol)); */
        if (AcabaPartida(tauler,ntir,njug,nfil,ncol)!=0) break;

    }

    CambiaJug(&njug);
    if (AcabaPartida(tauler,ntir,njug,nfil,ncol)== 3) printf("Empat, no queden casilles lliures.\n");
    else printf("Ha guanyat el jugador %d.\n", njug);
    return 0;
}

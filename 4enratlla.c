#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define N 8
#define M 8
#define NENRATLLA 4
#define NIVELLS 2

typedef struct node {
	struct node * *fills;
	char tauler[N][M];
	int valor;
} Node;

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

int AcabaPartida(char m[N][M], int njug, int nfil, int ncol) {
    CambiaJug(&njug);
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

void ValoraColumna (char m[M][N], int njug, int i, int j, int *count) {
    int ffinal;

    for(int t=2; t<NENRATLLA;t++) {
        if(kEnColumna(m,njug,i+1,j+1,t,&ffinal)==1) {
            if(ffinal+1<N && m[ffinal+1][j]==0) *count = *count + 3*t*t;
        }
    }
}

void ValoraFila (char m[M][N], int njug, int i, int j, int *count) {
    int cfinal;

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

int PuntsPosicioJug (char m[M][N], int njug, int nfil, int ncol) {
    
    if(AcabaPartida(m,njug,nfil,ncol)!=0) return INT_MAX;
    if(AcabaPartida(m,njug,nfil,ncol)==3) return 0;
    
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

int ValoraPosicioCPU (char m[N][M], int nfil, int ncol) {
    int njug=1;

    int p1=PuntsPosicioJug(m,njug,nfil,ncol);
    CambiaJug(&njug);
    int p2=PuntsPosicioJug(m,njug,nfil,ncol);

    return p2-p1;
}

void ColocaFicha(char m[N][M], int x, int njug, int *nfil, int *ncol) {
    for (int i=0;i<N;i++) {
        if (m[i][x-1] == 0) {
            *nfil = i+1;
            *ncol = x;
        }
        m[*nfil-1][*ncol-1] = njug;
        printf("Ficha colocada a la casella (%d,%d) .\n\n", *nfil,*ncol);
    }
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


void JugadaHuma(char m[N][M], int *njug, int *nfil, int *ncol) {
    int x,y;
    while (1) {
        printf("Juga el Jugador %d\n\nEn quina columna vols posar la ficha (de la 1 a la %d): ",*njug,N);
        y = LlegirEnter(&x);
        if(y==0) printf("Error de lectura.\n");
        else if(y==-1) printf("Error: Columna no valida. Es necessari introduir un unic enter.\n\n");
        else if(y==1) break;
    }

    if (ComprobacioColumna(m,x)==-1) printf("Error: Columna fora del rang (1-%d).\n\n",N);
    else if (ComprobacioColumna(m,x)==0) printf("Error: La columna esta plena.\n\n");
    else if (ComprobacioColumna(m,x)==1) {
        ColocaFicha(m,x,*njug,nfil,ncol);
        CambiaJug(njug);
        ImprimeixTauler(m);
    }
}

Node* creaNode(Node *pare,int numDeFill) {
    int extra1,extra2;
	Node *p=malloc(sizeof(Node));
    CopiaTauler(pare->tauler, p->tauler);
	ColocaFicha(p->tauler,numDeFill, 2, &extra1, &extra2);
	p->valor=ValoraPosicio(p->tauler);
	p->fills=malloc( M * sizeof(Node*));
	return p;
}

void AnalitzaFills (char m[N][M], char v[M] ) {
    int extra1,extra2;
    for (j=0;j<M;j++) {
        if(ComprobacioFila(m,j,&extra1,&extra2)==1) v[j]=1;
    }
}

void creaNivell(Node *pare) {
    char v[M];
    OmpleCharDeZeros(v);
	for(int i=0 ; i<M ; i++) {
        AnalitzaFills(pare->tauler, v);
        if(v[i]==1) pare->fills[i] = creaNode(pare,i);
	}
}

void CreaArbre (Node *p) {
    int count=0;
    while(1) {
        nivell=1;
        creaNivell(p);
        count = count + 1;
        if(count==NIVELLS) break;
        for(int i=0 ; i<M ; i++) {
            nivell=2;
            creaNivell(p->fills[i]);
            CreaArbre(p->fills[i]);
        }
        count = count + 1;
        if(count==NIVELLS) break;
    }

}

Node* SeleccionaMillorFillMinMax (Node *p) {
    Node *c;
    CopiaTauler(p->tauler,c->tauler)
    char v[M];
    char val[M];
    AnalitzaFills(c->tauler,v);
    for(int i=0; i<M; i++ ) {
        if(v[i]==1) val[i] = p->valor + p->fills[i]->valor
    }
    return c;
}

void JugadaCPU(Node *a) {
    CreaArbre(a);
    int count=0;
    for ()

}



int main(){
    Node a;

    OmpleTaulerDeZeros(a.tauler);

    int njug=CaraoCreuInicial();
    int nfil=1;
    int ncol;
    while (1){
        if(njug==1) JugadaHuma(a.tauler,&njug,&nfil,&ncol);
        else if(njug==2) JugadaCPU(&a);
        printf("ValPosicio = %d\n\n",ValoraPosicio(a.tauler,njug,nfil,ncol));
        if (AcabaPartida(a.tauler,njug,nfil,ncol)!=0) break;

    }

    CambiaJug(&njug);
    if (AcabaPartida(a.tauler,njug,nfil,ncol)== 3) printf("Empat, no queden casilles lliures.\n");
    else if (njug==1) printf("Ha guanyat el jugador 1.\n");
    else printf("Ha guanyat la CPU\n");
    return 0;
}

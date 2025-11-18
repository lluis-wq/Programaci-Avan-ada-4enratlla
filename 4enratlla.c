#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#define N 8
#define M 8
#define NENRATLLA 4

typedef struct node {
	struct node * *fills;
    int n_fills;
    char v_fills[M];
	char tauler[N][M];
	int valor;
    int nfil;
    int ncol;
    int profunditat;
} Node;

void OmpleCharDeZeros(char m[M]) {
    for (int j=0;j<M;j++) {
        m[j]=0;
    }
}

void OmpleCharDeUns(char m[M]) {
    for (int j=0;j<M;j++) {
        m[j]=1;
    }
}

void OmpleTaulerDeZeros(char m[N][M]){
    for (int i=0;i<N;i++) {
        for(int j=0;j<M;j++){
            m[i][j] = 0;
        }
    }
}

void CopiaChar (char v[M], char w[M]) {
    for (int j=0;j<M;j++) {
        w[j] = v[j];
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
    int valor=INT_MIN;
    for (int i=0;i<M;i++) {
        if(p->fills[i]!=NULL) {
            if(p->fills[i]->valor >= valor) {
                *index = i;
                valor = p->fills[i]->valor;
            }
        }
    }
    p->valor = valor;
}

void TrobaMinimIndexValor(Node *p, int *index) {
    int valor=INT_MAX;
    for (int i=0;i<M;i++) {
        if(p->fills[i]!=NULL) {
            if(p->fills[i]->valor <= valor) {
                *index = i;
                valor = p->fills[i]->valor;
            }
        }
    }
    p->valor = valor;
}

void TrobaMinimaProfunditat(Node *p) {
    int valor = INT_MAX;
    for(int i=0; i<M;i++) {
        if(p->fills[i]!=NULL) {
            if(p->fills[i]->profunditat!=0 && p->fills[i]->profunditat<=valor) valor = p->fills[i]->profunditat;
        }
    }
    if(valor != INT_MAX) p->profunditat = valor;
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

int CaraoCreuInicial () {

    printf("\nJuguem a cara o creu per veure qui juga primer. \n\n");
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
        else if (y==0) printf("Error de lectura.\n");
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
        else if (y==0) printf("Error de lectura.\n");
    }
    return x;
}

void CambiaJug (int *njug) {
    if(*njug==1) *njug=2;
    else *njug=1;
}


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

void MissatgeColocaFitxa(int njug, int nfil, int ncol) {
    if (njug == 1) printf("El Jugador huma coloca la fitxa a la casella (%d,%d) .\n\n", nfil,ncol);
    else printf("La CPU coloca la fitxa a la casella (%d,%d) .\n\n", nfil,ncol);
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
        printf("Torn del Jugador huma:\n\nEn quina columna vols posar la ficha (de la 1 a la %d): ",M);
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
        MissatgeColocaFitxa(*njug,*nfil,*ncol);
    }
}


void AnalitzaFills (char m[N][M], char v[M], int *n) {
    int count = 0;
    for (int j=0;j<M;j++) {
        if(ComprobacioFila(m,j+1)==1) {
            v[j]=1;
            count = count + 1;
        }
    }
    *n = count;
}

Node* creaNode(Node *pare,int numDeFill, int njug, int k, int nivells) {
	Node *p=malloc(sizeof(Node));
    CopiaTauler(pare->tauler, p->tauler);
	ColocaFitxa(p->tauler,numDeFill+1, njug, &(p->nfil), &(p->ncol));
	p->valor=ValoraPosicioCPU(p->tauler,njug,p->nfil,p->ncol);
    if(p->valor == INT_MAX) p->profunditat = k+1;
    else if(p->valor == INT_MIN) p->profunditat = -k-1;
    else p->profunditat = 0;
	if(k < nivells - 1) {
        OmpleCharDeZeros(p->v_fills);
        int n;
        AnalitzaFills(p->tauler,p->v_fills,&n);
        p->n_fills = n;
        p->fills=malloc( M * sizeof(Node*));
	}
	else {
        p->n_fills = 0;
        p->fills=NULL;
	}
	return p;
}

void creaNivell(Node *pare, int k, int nivells) {
    OmpleCharDeZeros(pare->v_fills);
    AnalitzaFills(pare->tauler, pare->v_fills, &(pare->n_fills));
    if (pare->n_fills > 0) {
        pare->fills = malloc(M * sizeof(Node*));
        int njug;
        if ((k+2)%2 == 0) njug = 2;
        else njug = 1;
        for(int i=0 ; i<M ; i++) {
            if(pare->v_fills[i]==1) {
                pare->fills[i] = creaNode(pare,i,njug,k,nivells);
            }
            else pare->fills[i] = NULL;
        }
    }
}

void CreaArbreRec (Node *p, int k, int nivells) {
    creaNivell(p,k,nivells);
    if(k<nivells-1) {
        for (int i=0; i<M; i++) {
            if(p->v_fills[i]==1 && p->fills[i]!= NULL) CreaArbreRec(p->fills[i],k+1,nivells);
        }
    }
}

void ModeFacilRandom (Node *p, int *njug) {
    int r=rand() % M + 1;
    ColocaFitxa(p->tauler,r,2,&(p->nfil),&(p->ncol));
    ImprimeixTauler(p->tauler);
    MissatgeColocaFitxa(*njug,p->nfil,p->ncol);
}

void AlliberaArbreRec(Node *p) {
    if(p==NULL) return;
    if(p->fills != NULL) {
        for (int i=0;i<M;i++) {
            if(p->fills[i]!=NULL) AlliberaArbreRec(p->fills[i]);
        }
        free(p->fills);
    }
    free(p);
}

void AlliberaArbreRecSensePareNiIndex(Node *p, int index) {
    for(int i=0;i<M;i++) {
        if(i!=index && p->fills[i]!=NULL) AlliberaArbreRec(p->fills[i]);
    }
}

int TriaNodeUnNivell(Node *a) {
    int index;
    int valor=INT_MIN;
    if(a->nfil==-1) {
        index=rand() % M;
    }
    TrobaMaximIndexValor(a,&index);
    return index;
}

void ModeNormalUnNivell(Node *p, int *njug) {
    int k=0;
    int nivells=1;
    CreaArbreRec(p,k,nivells);
    int index = TriaNodeUnNivell(p);
    Node *a = p->fills[index];
    AlliberaArbreRecSensePareNiIndex(p,index);
    CopiaParcialNode(a,p);
    free(p->fills);
    free(a);
    p->n_fills=0;
    p->fills=NULL;
    ImprimeixTauler(p->tauler);
    MissatgeColocaFitxa(*njug,p->nfil,p->ncol);
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
        TrobaMinimaProfunditat(p);
    }
    else {
        int extra;
        TrobaMaximIndexValor(p,&extra);
        TrobaMinimaProfunditat(p);
    }
}

int PrimerMovimentCPUDificil () {
    if(M <= (2*(NENRATLLA-1)) && M%2 == 0) {
        int r = rand() % 2;
        return r + M/2 - 1;
    }        
    else if (M <= (2*(NENRATLLA-1)) && M%2 != 0) {
        return (M-1)/2;
    }
    else { 
        int r=rand() % (M - 2*(NENRATLLA-1));
        printf("%d\n",r);
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
            printf("Valor Despres MinMax: %d\n",p->valor);
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
    MissatgeColocaFitxa(*njug,p->nfil,p->ncol);
}

void JugadaCPU(Node *a, int *njug, int dificultat, int inici) {
    if (inici == 0) srand(time(NULL));
    printf("Torn de la CPU:\n\n");
    if(dificultat==1) {
        ModeFacilRandom(a,njug);
    }
    if(dificultat==2) {
        ModeNormalUnNivell(a,njug);
    }
    if(dificultat==3) {
        int nivells=2;
        ModeDificilMinMax(a,njug,nivells);
    }
    if(dificultat==4) {
        int nivells=6;
        ModeDificilMinMax(a,njug,nivells);
    }

}

void InicialitzaNode(Node *p) {
    OmpleTaulerDeZeros(p->tauler);
    p->nfil=-1;
    p->valor = 0;
    p->fills = NULL;
    p->n_fills=0;
}

void JugaPartidaHumavsCPU(Node *a, int *njug, int dificultat, int inici) {
    printf("NOTA: El jugador huma juga amb creus 'x' i la CPU amb cercles 'o'.\n\nINICIA LA PARTIDA:\n\n");
    while (1){
        if(*njug==1) JugadaHuma(a->tauler,njug,&(a->nfil),&(a->ncol));
        else if(*njug==2) JugadaCPU(a,njug,dificultat,inici);
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

void FinalitzaPartidaHumavsHuma(Node *a, int njug) {
    if (AcabaPartida(a->tauler,njug,a->nfil,a->ncol)== 3) printf("Empat, no queden casilles lliures.\n");
    else printf("Ha guanyat el jugador %d.\n",njug);
    free(a);
}

void JugadaHumavsHuma(char m[N][M],int *njug, int *nfil, int *ncol) {
    int x,y;
    while (1) {
        printf("Juga el Jugador %d\n\nEn quina columna vols posar la ficha (de la 1 a la %d): ",*njug,M);
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
        printf("Ficha colocada a la casella (%d,%d) .\n\n", *nfil,*ncol);
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

int PrimerJugador(int *njug) {
    printf("Qui vols que comenci?\n");
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
        else if (y==0) printf("Error de lectura.\n");
    }
}

void InicialitzaPartida() {
    Node *a = malloc(sizeof(Node));
    InicialitzaNode(a);
    int mode = TriaMode();
    if(mode == 1) {
        int njug=1;
        JugaPartidaHumavsHuma(a->tauler, &njug, &(a->nfil), &(a->ncol));
        FinalitzaPartidaHumavsHuma(a,njug);
    }
    else {
        int dificultat = TriaModeDificultat();
        int njug;
        int inici = PrimerJugador(&njug);
        JugaPartidaHumavsCPU(a,&njug,dificultat,inici);
        FinalitzaPartidaHumavsCPU(a,njug);
    }
}

int main(){
    InicialitzaPartida();
    return 0;
}
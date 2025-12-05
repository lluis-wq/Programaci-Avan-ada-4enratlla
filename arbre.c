#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "funcions_auxiliars.h"
#include "heuristica.h"
#include "definicions.h"

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
	Node *p=calloc(1,sizeof(Node));
    CopiaTauler(pare->tauler, p->tauler);
	ColocaFitxa(p->tauler,numDeFill+1, njug, &(p->nfil), &(p->ncol));
	p->valor=ValoraPosicioCPU(p->tauler,njug,p->nfil,p->ncol);
    if(p->valor == INT_MAX) {
        p->profunditat = k+1;
        p->n_fills = 0;
        p->fills=NULL;
    }
    else if(p->valor == INT_MIN) {
        p->profunditat = -k-1;
        p->n_fills = 0;
        p->fills=NULL;
    }

	if(k < nivells - 1) {
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
#ifndef DEFS_H  
#define DEFS_H 

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

#endif
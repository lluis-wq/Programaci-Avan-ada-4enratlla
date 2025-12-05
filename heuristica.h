#include "definicions.h"

int kEnColumna (char m[N][M], int njug, int nfil, int ncol, int k, int *ffinal);
int kEnFila (char m[N][M], int njug, int nfil, int ncol, int k, int *cfinal);
int kEnDiagonalCreixent (char m[N][M], int njug, int nfil, int ncol, int k, int *ffinal, int *cfinal);
int kEnDiagonalDecreixent (char m[N][M], int njug, int nfil, int ncol, int k, int *ffinal, int *cfinal);
int AcabaPartida(char m[N][M], int njug, int nfil, int ncol);
void ValoraColumna (char m[N][M], int njug, int i, int j, int *count);
void ValoraFila (char m[N][M], int njug, int i, int j, int *count);
void ValoraDiagonalCreixent (char m[N][M], int njug, int i, int j, int *count);
void ValoraDiagonalDecreixent(char m[N][M], int njug, int i, int j, int *count);
int PuntsPosicioJug (char m[N][M], int njug);
int ValoraPosicioCPU (char m[N][M], int njug, int nfil, int ncol);
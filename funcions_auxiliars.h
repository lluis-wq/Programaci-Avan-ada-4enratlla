#include "definicions.h"


void OmpleCharDeZeros(char m[M]);
void OmpleTaulerDeZeros(char m[N][M]);
void CopiaTauler(char m[N][M], char n[N][M]);
void CopiaParcialNode(Node *p, Node *a);
void ImprimeixTauler(char m[N][M]);
void TrobaMaximIndexValor(Node *p, int *index);
void TrobaMinimIndexValor(Node *p, int *index);
int GuanyemSegMov(Node p);
int LlegirEnter (int *n);
void CambiaJug (int *njug);
void ColocaFitxa(char m[N][M], int x, int njug, int *nfil, int *ncol);
void MissatgeColocaFitxaHumavsCPU(int njug, int nfil, int ncol);
void MissatgeColocaFitxaHumavsHuma(int njug, int nfil, int ncol);
int ComprobacioFila(char m[N][M], int x);
int ComprobacioColumna (char m[N][M], int x);
void CanviaNivell(int *nivellimp, double tempstotal, int nfil, int valorminmax);
#include "definicions.h"

void JugadaHuma(char m[N][M], int *njug, int *nfil, int *ncol);
void ModeFacilRandom (Node *p, int *njug);
void RecorreArbreRec(Node *p,int n);
int PrimerMovimentCPUDificil();
void ModeDificilMinMax(Node *p, int *njug, int nivells);
void JugadaCPU(Node *a, int *njug, int dificultat, int inici, int *nivellimp);
void JugaPartidaHumavsCPU(Node *a, int *njug, int dificultat, int inici);
void FinalitzaPartidaHumavsCPU(Node *a, int njug);
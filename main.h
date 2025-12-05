void ImprimeixTauler(char m[N][M]);
void CambiaJug (int *njug);
int QuatreEnColumna (char m[N][M], int njug, int nfil, int ncol);
int QuatreEnFila (char m[N][M], int njug, int nfil, int ncol);
int QuatreEnDiagonalCreixent (char m[N][M], int njug, int nfil, int ncol);
int QuatreEnDiagonalDecreixent (char m[N][M], int njug, int nfil, int ncol);
int AcabaPartida(char m[N][M],int ntir, int njug, int nfil, int ncol);
int ComprobacioFila(char m[N][M], int x, int *nfil, int *ncol);
int ComprobacioColumna (char m[N][M], int x, int *nfil, int *ncol);
int LlegirEnter (int njug);
void Jugada(char m[N][M], int *ntir, int *njug, int *nfil, int *ncol);


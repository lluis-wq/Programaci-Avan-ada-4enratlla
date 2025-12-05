#include "definicions.h"

void AnalitzaFills (char m[N][M], char v[M], int *n);
Node* creaNode(Node *pare,int numDeFill, int njug, int k, int nivells);
void creaNivell(Node *pare, int k, int nivells);
void CreaArbreRec (Node *p, int k, int nivells);
void AlliberaArbreRec(Node *p);
void AlliberaArbreRecSensePareNiIndex(Node *p, int index);
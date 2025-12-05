#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "huma_vs_huma.h"
#include "huma_vs_cpu.h"
#include "funcions_auxiliars.h"
#include "inicialitza.h"
#include "definicions.h"

void InicialitzaPartida() {
    Node *a=InicialitzaNode();
    int mode = TriaMode();
    if(mode == 1) {
        int njug=1;
        JugaPartidaHumavsHuma(a->tauler, &njug, &(a->nfil), &(a->ncol));
        FinalitzaPartidaHumavsHuma(a->tauler,njug,a->nfil,a->ncol);
        free(a);
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

#include "personagem.h"
#include <stdio.h>
#include <string.h>

extern short filaEspera[MAX_NUM_PERSONAGEM];

void esquentar_algo(Personagem *p) {
    sai_da_fila(p);
	printf("%s comeca a esquentar algo\n", p->nome);
	sleep(1);
}

void comer(Personagem *p) {
	int t = rand() % 4;
    if( t == 0 ) t = 1;
    sleep(t);
}

void vai_para_fila(Personagem *p) {
    filaEspera[ p->id ] = 1;
}

void sai_da_fila(Personagem *p) {
    filaEspera[ p->id ] = 0;
}

void CriaVetPersonagem(Personagem *vetper){
	int i;
	
    for (i=0; i < MAX_NUM_PERSONAGEM; i++) {
		vetper[i].numVezesComeu = 0;
		vetper[i].id = i;
	}

	vetper[0].nome = "Raj";
    
	vetper[1].idParceiro = 2;
	vetper[1].nome = "Amy";
	
    vetper[2].idParceiro = 1;
	vetper[2].nome = "Sheldon";
	
    vetper[3].idParceiro = 4;
	vetper[3].nome ="Bernardette";
    
    vetper[4].idParceiro = 3;
    vetper[4].nome ="Howard";
    
    vetper[5].idParceiro = 6;
    vetper[5].nome ="Penny";
    
    vetper[6].idParceiro = 5;
    vetper[6].nome ="Leonard";
    
}

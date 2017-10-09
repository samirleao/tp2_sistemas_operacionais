
#include "personagem.h"
#include <stdio.h>
#include <string.h>

extern short filaEspera[MAX_NUM_PERSONAGEM];

void esquentar_algo(Personagem *p) {
	printf("%s comeca a esquentar algo\n", p->nome);
	filaEspera[p->id] = 0;
	sleep(1);
}

void comer(Personagem *p) {
	sleep(2);
}

void CriaVetPersonagem(Personagem *vetper){
	int i;
	
    for (i=0; i < MAX_NUM_PERSONAGEM; i++){
		vetper[i].numVezesComeu = 0;
		vetper[i].id = i;
	}

	vetper[0].nome = "Raj";

	vetper[1].idParceiro = 2;
	vetper[1].nome = "Amy";
	vetper[1].idUsaAntesMulher = 5;
	vetper[1].idUsaAntesHomem = 6;


	vetper[2].idParceiro = 1;
	vetper[2].nome = "Sheldon";
	vetper[2].idUsaAntesMulher = 5;
	vetper[2].idUsaAntesHomem = 6;

	vetper[3].idParceiro = 4;
	vetper[3].nome ="Bernardette";
	vetper[3].idUsaAntesMulher = 1;
	vetper[3].idUsaAntesHomem = 2;


    vetper[4].idParceiro = 3;
    vetper[4].nome ="Howard";
    vetper[4].idUsaAntesMulher = 1;
    vetper[4].idUsaAntesHomem = 2;


    vetper[5].idParceiro = 6;
    vetper[5].nome ="Penny";
    vetper[5].idUsaAntesMulher = 3;
    vetper[5].idUsaAntesHomem = 4;

    vetper[6].idParceiro = 5;
    vetper[6].nome ="Leonard";
    vetper[6].idUsaAntesMulher = 3;
    vetper[6].idUsaAntesHomem = 4;
}

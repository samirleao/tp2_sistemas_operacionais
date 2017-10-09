#include "forno.h"

extern short 	filaEspera[MAX_NUM_PERSONAGEM];
extern int 		vaiPrimeiroCasal[3];

int casal_maior_prioridade() {
    
    if( fila_vazia() ) return -1;
    if( filaEspera[SHELDON] || filaEspera[AMY] ) {
        if( filaEspera[HOWARD] || filaEspera[BERNARDETTE] ) {
            if( filaEspera[LEONARD] || filaEspera[PENNY] ) return -1;
            else return 0;
        }
        else {
            if( filaEspera[LEONARD] || filaEspera[PENNY] ) return 2;
        }
    }
    else {
        if( filaEspera[HOWARD] || filaEspera[BERNARDETTE] ) return 1;
        else return 2;
    }
    
}

int personagem_maior_prioridade() {
    
    int casal = casal_maior_prioridade();
    //printf("casal selecionado = %d\n", casal);
    
    if( casal == -1 ) return -1;
    
    //no casal selecionado, ver quem esta presente e selecionar um membro
    if( casal == 0 ) {
        if( filaEspera[SHELDON] == 1 && filaEspera[AMY] == 0 ) {
            return SHELDON;
        }
        else {
            if( filaEspera[SHELDON] == 0 && filaEspera[AMY] == 1 ) {
                return AMY;
            }
            else if( filaEspera[SHELDON] == 1 && filaEspera[AMY] == 1 ) {
                //selecionar quem do casal chegou primeiro
                //printf("quem vai primeiro no casal %d: %d\n", id_casal(SHELDON), vaiPrimeiroCasal[SHELDON]);
                return vaiPrimeiroCasal[ id_casal(SHELDON) ];
            }
        }
    }
    else if( casal == 1 ) {
        if( filaEspera[HOWARD] == 1 && filaEspera[BERNARDETTE] == 0 ) {
            return HOWARD;
        }
        else {
            if( filaEspera[HOWARD] == 0 && filaEspera[BERNARDETTE] == 1 ) {
                return BERNARDETTE;
            }
            else if( filaEspera[HOWARD] == 1 && filaEspera[BERNARDETTE] == 1 ) {
                //selecionar quem do casal chegou primeiro
                //printf("quem vai primeiro no casal %d: %d\n", id_casal(HOWARD), vaiPrimeiroCasal[HOWARD]);
                return vaiPrimeiroCasal[ id_casal(HOWARD) ];
            }
        }
    }
    else if( casal == 2 ) {
        if( filaEspera[LEONARD] == 1 && filaEspera[PENNY] == 0 ) {
            return LEONARD;
        }
        else {
            if( filaEspera[LEONARD] == 0 && filaEspera[PENNY] == 1 ) {
                return PENNY;
            }
            else if( filaEspera[LEONARD] == 1 && filaEspera[PENNY] == 1 ) {
                //selecionar quem do casal chegou primeiro
                //printf("quem vai primeiro no casal %d: %d\n", id_casal(LEONARD), vaiPrimeiroCasal[LEONARD]);
                return vaiPrimeiroCasal[ id_casal(LEONARD) ];
            }
        }
    }
    
}

int fila_vazia() {
	int i;
	for(i = 0; i < MAX_NUM_PERSONAGEM; i++) {
		if( filaEspera[i] == 1 ) return 0;
	}
	return 1;
}

int id_casal(int id) {
    if( id == 1 || id == 2 ) return 0; //sheldon e amy
    if( id == 3 || id == 4 ) return 1; //howard e bernardette
    if( id == 5 || id == 6 ) return 2; //leonard e penny
}

void imprime_fila() {
    int i;
    printf("fila: ");
    for(i = 1; i < MAX_NUM_PERSONAGEM; i++) {
        if( filaEspera[i] == 1 ) {
            if( i == 1 ) printf("amy ");
            else if( i == 2 ) printf("sheldon ");
            else if( i == 3 ) printf("bernardette ");
            else if( i == 4 ) printf("howard ");
            else if( i == 5 ) printf("penny ");
            else if( i == 6 ) printf("leonard ");
        }
    }
    printf("\n");
}


#include "forno.h"

int numVezes; //numero de vezes que cada personagem ira comer 
Personagem personagens[MAX_NUM_PERSONAGEM]; 					//vetor de personagens
short filaEspera[MAX_NUM_PERSONAGEM] = {0, 0, 0, 0, 0, 0, 0};	//fila de espera
forno_t *monitorForno;
int estado;

void print() {
	int i;
	for(i = 0; i < MAX_NUM_PERSONAGEM; i++) {
		if( filaEspera[i] == 1 ) printf("%s - ", personagens[i].nome);
	}
	printf("\n");
}

int unicoFila(Personagem *p) {
    int count = 0;
    int i;
    for(i = 1; i < MAX_NUM_PERSONAGEM; i++) {
        if( filaEspera[i] == 1 ) count++;
    }
    if( filaEspera[p->id] == 1 && count == 1 ) return 1;
    return 0;
}

int primeiro_fila() {
	int i;
	for(i = 0; i < MAX_NUM_PERSONAGEM; i++) {
		if( filaEspera[i] == 1 ) return i;
	}
	return -1; 
}

int fila_vazia() {
	int i;
	for(i = 0; i < MAX_NUM_PERSONAGEM; i++) {
		if( filaEspera[i] == 1 ) return 0;
	}
	return 1;
}

void inicializar_forno() {
	int i; 
	monitorForno = (forno_t *) malloc (sizeof(forno_t));
    pthread_mutex_init(&monitorForno->mutex, NULL);
    for(i = 0; i < 6; i++) pthread_cond_init(&monitorForno->precedencia_acesso[i], NULL);
    monitorForno->numUsoForno = numVezes * 6;
}

void destruir_forno() {
	int i;
	pthread_mutex_destroy( &monitorForno->mutex );
	for(i = 0; i < 6; i++) pthread_cond_destroy( &monitorForno->precedencia_acesso[i] );
	free(monitorForno);
}

void esperar(Personagem *p) {
    pthread_mutex_lock( &monitorForno->mutex );
    printf("%s quer usar o forno\n", p->nome);
    pthread_cond_wait( &monitorForno->precedencia_acesso[ p->id-1 ], &monitorForno->mutex );
	pthread_mutex_unlock( &monitorForno->mutex );
}

void liberar(Personagem *p) { //falta terminar essa funcao
    int i;
    int ind;
	printf("%s saiu e comecou a comer\n", p->nome);
	p->numVezesComeu++;
	monitorForno->numUsoForno--;
    if( filaEspera[p->idParceiro] == 1 ) { //olhar se o parceiro esta na fila de espera
        pthread_cond_signal( &monitorForno->precedencia_acesso[ p->idParceiro-1 ] );
        return;
    }
    else {
        if( p->id == 2 ) { //se for o sheldon
            if( filaEspera[4] == 1 ) { //se o howard esta na fila entao ele vai
                pthread_cond_signal( &monitorForno->precedencia_acesso[ 4-1 ] );
                return;
            }
        }
        else if( p->id == 4 ) { //se for o howard
            if( filaEspera[6] == 1 ) { //se o leonard esta na fila entao ele vai
                pthread_cond_signal( &monitorForno->precedencia_acesso[ 6-1 ] );
                return;
            }
        }
        else if(p ->id == 6 ) { //se for o leonard
            if( filaEspera[2] == 1 ) { //se o sheldon esta na fila entao ele vai
                pthread_cond_signal( &monitorForno->precedencia_acesso[ 2-1 ] );
                return;
            }
        }
    }
    if( ind > 0 ) pthread_cond_signal( &monitorForno->precedencia_acesso[primeiro_fila()] );
}

void *forno(void *personagem) {

    Personagem *p = (Personagem *)personagem;
    
    while( p->numVezesComeu < numVezes ) {
        filaEspera[p->id] = 1;
        if( unicoFila(p) ) {
            esquentar_algo(p);
            liberar(p);
            comer(p);
        }
        else {
            esperar(p);
            esquentar_algo(p);
            liberar(p);
            comer(p);
        }
    }

}

int verifica() {
    
    //caso 1 -- pelo menos um membro de cada casal
    if( (filaEspera[1] > 0 || filaEspera[2] > 0) &&
        (filaEspera[3] > 0 || filaEspera[4] > 0) &&
        (filaEspera[5] > 0 || filaEspera[6] > 0) )
    { return 1; }
    
    //caso 2 -- pelo menos quatro pessoas na fila
    int i;
    int count = 0;
    for(i = 1; i < 7; i++) {
        if( filaEspera[i] > 0 ) count++;
        if( count == 4 ) return 1;
    }
    
    return 0;
    
}

void *funcao_raj() {
	int idSorteado;   
	while( monitorForno->numUsoForno > 0 ) {
          
        //esperar 5 segundos
        sleep(5);
        
        //olhar se tem deadlock
        if( verifica() ) { //se ocorreu deadlock entao sortear um id para usar o forno
            while(1){
                idSorteado = rand() % MAX_NUM_PERSONAGEM;
                if( idSorteado == 0 ) idSorteado = 1;
                if( filaEspera[idSorteado] == 1 ) break;
            }
            printf("Raj detectou um deadlock, liberando %s\n", personagens[idSorteado].nome);
            pthread_cond_signal( &monitorForno->precedencia_acesso[ idSorteado-1 ] );
        }
    }

}

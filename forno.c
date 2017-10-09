#include "forno.h"

int 		numVezes;                         //numero de vezes que cada personagem ira comer
Personagem 	personagens[MAX_NUM_PERSONAGEM];  //vetor de personagens
short		filaEspera[MAX_NUM_PERSONAGEM];   //fila de espera
forno_t 	*monitor;                         //monitor
int 		vaiPrimeiroCasal[3];              //marca quem vai primeiro no casal

void inicializar_forno() {
	int i; 
	monitor = (forno_t *) malloc (sizeof(forno_t));
    pthread_mutex_init(&monitor->mutex, NULL);
    for(i = 0; i < 6; i++) pthread_cond_init(&monitor->precedencia_acesso[i], NULL);
    for(i = 0; i < MAX_NUM_PERSONAGEM; i++) filaEspera[i] = 0;
    for(i = 0; i < 3; i++) vaiPrimeiroCasal[i] = 0;
    monitor->numUsoForno = numVezes * 6;
    monitor->estado = LIVRE;
}

void destruir_forno() {
	int i;
	pthread_mutex_destroy( &monitor->mutex );
	for(i = 0; i < 6; i++) pthread_cond_destroy( &monitor->precedencia_acesso[i] );
	free(monitor);
}

void esperar(Personagem *p) {
    pthread_mutex_lock( &monitor->mutex );
    if( filaEspera[p->idParceiro] == 0 ) {
    	vaiPrimeiroCasal[ id_casal(p->id) ] = p->id;
    	//printf("quem vai primeiro no casal %d: %d\n", id_casal(p->id), vaiPrimeiroCasal[ id_casal(p->id) ]);
    }
    else {
    	vaiPrimeiroCasal[ id_casal(p->id) ] = p->idParceiro;
    	//printf("quem vai primeiro no casal %d: %d\n", id_casal(p->id), vaiPrimeiroCasal[ id_casal(p->id) ]);
    }
    printf("%s quer usar o forno\n", p->nome);
    if( (monitor->estado == OCUPADO) || !fila_vazia() ){
    	vai_para_fila(p);
    	//imprime_fila();
        pthread_cond_wait( &monitor->precedencia_acesso[ p->id-1 ], &monitor->mutex );
    }
	pthread_mutex_unlock( &monitor->mutex );
}

void liberar(Personagem *p) {
    int i;
    int ind;
	printf("%s saiu e comecou a comer\n", p->nome);
	p->numVezesComeu++;
	monitor->numUsoForno--;
    monitor->estado = LIVRE;
    
    int id = personagem_maior_prioridade();
    //printf("id selecionado = %d\n", id);
    //imprime_fila();
    if( id > 0 ) {
        pthread_cond_signal( &monitor->precedencia_acesso[ id-1 ] );
        return;
    }
    
}

void *forno(void *personagem) {

    Personagem *p = (Personagem *)personagem;
    
    while( p->numVezesComeu < numVezes ) {
        esperar(p);
        monitor->estado = OCUPADO;
        esquentar_algo(p);
        liberar(p);
        comer(p);
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
	while( monitor->numUsoForno > 0 ) {
          
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
            while( monitor->estado == OCUPADO ) { }
            pthread_cond_signal( &monitor->precedencia_acesso[ idSorteado-1 ] );
        }
    
    }

}

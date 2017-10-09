
#ifndef FORNO_H_
#define FORNO_H_

#include "personagem.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

typedef enum {
    LIVRE,
    OCUPADO,
} estado_t;

typedef struct {
    pthread_cond_t precedencia_acesso[6];
    pthread_mutex_t mutex;
    int numUsoForno;
    estado_t estado;
} forno_t;

//inicializacao e alocaco do monitor
void inicializar_forno();

//liberacao de variaveis de condicao e memoria usada pelo monitor
void destruir_forno();

//retorna verdadeiro se a fila de espera esta vazia ou falso caso contrario
int fila_vazia();

void imprime_fila();

//retorna id do casal a partir do id do personagem
int id_casal(int id);

//retorna indice do casal com maior prioridade tendo algum membro do mesmo na fila
int casal_maior_prioridade();

//retorna indice do personagem com maior prioridade na fila
int personagem_maior_prioridade();

//usado pela pessoa que espera para usar o forno
void esperar(Personagem *p);

//usado pela pessoa (thread) que liberou o forno
void liberar(Personagem *p);

/*Representa o fono (ou o comportamento de utilização do forno) que será usado pelas pessoas. Essa funcão usa as seguintes
 * funçoes auxiliares: espera, usar e liberar. */
void *forno(void *pers);

//retorna verdadeiro se ocorreu deadlock ou falso caso contrario
int verifica();

//funcao desempenhada pela thread raj para tratar deadlocks
void *funcao_raj();

#endif /* FORNO_H_ */


#ifndef FORNO_H_
#define FORNO_H_

#include "personagem.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    pthread_cond_t precedencia_acesso[6];
    pthread_mutex_t mutex;
    int numUsoForno;
} forno_t;

void print();

//inicializacao e alocaco do monitor
void inicializar_forno();

//liberacao de variaveis de condicao e memoria usada pelo monitor
void destruir_forno();

//verdadeiro se p e o unico na fila ou falso caso contrario
int unicoFila(Personagem *p);

//retorna indice do primeiro personagem que aparece na fila de espera -- desempate
int primeiro_fila();

//retorna verdadeiro se a fila de espera esta vazia ou falso caso contrario
int fila_vazia();

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

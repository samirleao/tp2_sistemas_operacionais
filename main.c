/*=========================================================
	
	UFMG - Universidade Federal de Minas Gerais
	DCC  - Departamento de Ciencia da Computacao 
 	Sistemas Operacionais
 	Trabalho Pratico 2
 	2013/01
 	
 	Samir Moreira Andrade Leao - 2008047355
 	Guilherme Henrique Rodrigues Nascimento - 2010054460
 
===========================================================*/

#include "forno.h"

extern int numVezes;
extern int numUsoForno; 													
extern Personagem personagens[MAX_NUM_PERSONAGEM]; 					
extern short filaEspera[MAX_NUM_PERSONAGEM];
extern forno_t *monitorForno;					

int main(int argc, char *argv[]){

	printf ("\nTRABALHO PRATICO 2\n");
	printf ("SISTEMAS DE INFORMAÇÃO - DCC - UFMG\n");
	printf ("SISTEMAS OPERACIONAIS\n");
	printf ("Guilherme Henrique Rodrigues Nascimento - 2010054460\n");
    printf ("Samir Moreira Andrade Leao - 2008047355\n\n");
    
    
    /*Treads Correspodentes a cada personagem*/
    pthread_t sheldon;
    pthread_t amy;
    pthread_t leonard;
    pthread_t penny;
    pthread_t howard;
    pthread_t bernardette;
    pthread_t raj;

	if(argc == 1){
		numVezes = 1;
	}
	else{
		numVezes = atoi( argv[1] );
	}
	
	CriaVetPersonagem(personagens);
	inicializar_forno();


	pthread_create ( &raj, NULL, funcao_raj, (void *)&personagens[0] );
	pthread_create ( &amy, NULL, forno, (void *)&personagens[1] );
	pthread_create ( &sheldon, NULL, forno, (void *) &personagens[2] );
	pthread_create ( &penny, NULL, forno, (void *) &personagens[3] );
	pthread_create ( &howard, NULL, forno, (void *) &personagens[4] );
	pthread_create ( &bernardette, NULL, forno, (void *)&personagens[5] );
	pthread_create ( &leonard, NULL, forno, (void *) &personagens[6] );

	pthread_join ( sheldon, NULL );
	pthread_join ( amy, NULL );
	pthread_join ( leonard, NULL );
	pthread_join ( penny, NULL );
	pthread_join ( howard, NULL );
	pthread_join ( bernardette, NULL );
	pthread_join ( raj, NULL );
	
	destruir_forno();
    
	return 0;
}




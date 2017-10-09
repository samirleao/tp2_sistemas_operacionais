
#ifndef PERSONAGEN_H_
#define PERSONAGEN_H_

#define MAX_NUM_PERSONAGEM  7
#define SHELDON             2
#define AMY                 1
#define HOWARD              4
#define BERNARDETTE         3
#define LEONARD             6
#define PENNY               5

//define a identidade dos personagens
typedef struct Personagem {
	int id;              //identifica o personagem dentro do programa(diferente do id da thread)
	char *nome;          //nome do personagem
	int idParceiro;      //identifica o namorado(a) do personagem
	int numVezesComeu;	 //numero de vezes que personagem comeu
} Personagem;

//cria um vertor que representa os pessonagens
void CriaVetPersonagem(Personagem *vetper);

//chamado pela pessoa para usar o forno por um tempo
void esquentar_algo(Personagem *p);

//chamado pela pessoa apos usar o forno
void comer(Personagem *p);

//coloca personagem na fila espera
void vai_para_fila(Personagem *p);

//retira personagem da fila de espera
void sai_da_fila(Personagem *p);

#endif /* PERSONAGEN_H_ */

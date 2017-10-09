
#ifndef PERSONAGEN_H_
#define PERSONAGEN_H_

#define MAX_NUM_PERSONAGEM 7 //numero maximo de personagens

//define a identidade dos personagens
typedef struct Personagem {
	int id;              //identifica o personagem dentro do programa(diferente do id da thread)
	char *nome;          //nome do personagem
	int idParceiro;      //identifica o namorado(a) do personagem
	int idUsaAntesMulher;//identifica o Mulher que usara antes o forno
	int idUsaAntesHomem; //identifica a homem que usara antes o forno
	int numVezesComeu;	 //numero de vezes que personagem comeu
} Personagem;

//cria um vertor que representa os pessonagens
void CriaVetPersonagem(Personagem *vetper);

//chamado pela pessoa para usar o forno por um tempo
void esquentar_algo(Personagem *p);

//chamado pela pessoa apos usar o forno
void comer(Personagem *p);

#endif /* PERSONAGEN_H_ */

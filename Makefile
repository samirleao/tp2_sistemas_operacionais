# Makefile para o tp2 de Sistemas Operacionais
# Sincronizacao de processos
# Sera gerado um executavel de nome tbbt
# make clean para apagar arquivos objeto
# Alunos: Samir Moreira Andrade Leao, Guilherme Henrique Rodrigues Nascimento

CC  = gcc
OBJ = main.o personagem.o forno.o 

all: tp2

tp2: $(OBJ)
	$(CC) -pthread -o bbtmwov $(OBJ)

personagem.o: personagem.c personagem.h
	$(CC) -c personagem.c

forno.o: forno.c personagem.c forno.h personagem.h
	$(CC) -c forno.c
	
main.o: main.c forno.h
	$(CC) -c main.c

clean:
	rm *.o

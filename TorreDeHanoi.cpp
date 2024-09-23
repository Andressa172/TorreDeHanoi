#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio2.h>
#include <unistd.h>
#include <time.h> 

#include "TADPilhaM2.h"

struct TpTorre
{
	int origem, destino, aux;
};

char menuPrincipal(void)
{
	clrscr();
	printf("### OPCOES DE JOGO ###");
	printf("\n[A] - Jogar manualmente");
	printf("\n[B] - Simulacao automatica");
	printf("\n[ESC] - Sair");
	printf("\n\nOpcao: ");
	return toupper(getche());
}

void manual(TpPilhaM2 &pm)
{
	int qtdeDisco, i=0, valor, movimento=0, op;
	TpTorre t;
	
	printf("\nQuantidade de discos (MIN:3 - MAX:10): ");
	scanf("%d",&qtdeDisco);
	if(qtdeDisco >=3 && qtdeDisco <= 10)
	{
		t.origem = 0;
		valor = qtdeDisco;
		while(i<qtdeDisco)
		{
			inserir(pm,valor,0);
			valor--;
			i++;
		}
		
		//TESTE PARA SABER SE ESTÁ TUDO CERTO NO INSERIR
		exibir(pm,t.origem);
		getch();
		
		//opção 2-3 porque a torre já começa na 1
		printf("\nPara qual pilha voce deseja levar a torre?(2 - 3) ");
		scanf("%d",&t.destino);
		
		t.destino--;//trantando o destino já que nas pilhas são 0,1,2
		
		//EU ACHO QUE PARA A GENTE APENAS USAR AS PILHAS MULTIPLAS TEM QUE SER ISSO
		if(t.destino == 1) //nossa auxiliar vai ser a pilha 2
		{
			printf("\n\n*** MOVIMENTANDO DA TORRE %d PARA TORRE %d\n",t.origem+1,t.destino+1);
			t.aux = 2;
			while(!pilhaVazia(pm,t.origem) || !pilhaVazia(pm,t.aux))
			{
				/*
				aqui teria que fazer a parte de perguntar a torre de onde ele vai tirar o disco e para qual torre
				ele deseja levar, fazendo as validações se é possivel ou não fazer a movimentação.
				A repetição vai se encerrar quando não houver mais disco na origem e tambem na auxiliar
				isso indica que todos os disco estão devidamente na torre destino.
				
				OQUE FAZER NESSA REPETIÇÃO COLOCAMOS NO IF DE BAIXO
				*/
				
				
				movimento++; //contador para saber o total de movimentos
			}
		}
		else
		if(t.destino == 2) //nossa auxiliar vai ser a pilha 1
		{
			printf("\n\n*** MOVIMENTANDO DA TORRE %d PARA TORRE %d\n",t.origem+1,t.destino+1);
			t.aux = 1;
			while(!pilhaVazia(pm,t.origem) || !pilhaVazia(pm,t.aux))
			{
				
				
				movimento++; //contador para saber o total de movimentos
			}
		}
		else
			printf("\nTorre invalida!\n");
		
	}
	else
		printf("\nQuantidade de disco invalida!\n");

}

void automatico(TpPilhaM2 &pm)
{
	int qtdeDisco, i=0, valor;
	TpTorre t;
	
	printf("\nQuantidade de discos (MIN:3 - MAX:10): ");
	scanf("%d",&qtdeDisco);
	if(qtdeDisco >= 3 && qtdeDisco <= 10)
	{
		t.origem=0;
		valor = qtdeDisco;
		while(i<qtdeDisco)
		{
			inserir(pm,valor,0);
			valor--;
			i++;
		}
					
		/*TESTE PARA SABER SE ESTÁ TUDO CERTO NO INSERIR
		exibir(pm,t.origem);
		getch(); */
					
	}
	else
		printf("\nQuantidade de disco invalida!\n");
}

int main(void)
{
	char op;
	int qtdeDisco, i=0, destino, valor;
	
	//pilha para maniupulação
	TpPilhaM2 pm;
	
	do
	{
		//3 é quantidade fixa de pilha que vamos ter, mudando apenas a quantidade de valores dentro delas
		inicializar(pm,3); //0, 1, 2
		clrscr();
		op = menuPrincipal();
		
		switch(op)
		{
			case 'A':
				manual(pm);
				
				break;
				
			case 'B':
				automatico(pm);
				
				break;
				
			case 27:
				printf("\nJogo encerrado!\n"); //pode colocar na parte de mensagem do jogo
		}
		getch();
	}while(op != 27);
	
	return 0;
}

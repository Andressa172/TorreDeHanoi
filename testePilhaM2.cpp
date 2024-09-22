#include<stdio.h>
#include<conio2.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#include "TADPilhaM2.h"

//opções do menu para realizar os teste do TADPilhaM1
char menu(void)
{
	//clrscr();
	printf("### OPERACOES TESTE PARA TAD DA TORRE DE HANOI COM PILHA MULTIPLA 2 ###\n");
	printf("\n[A] - Inicializar");
	printf("\n[B] - Empilhar");
	printf("\n[C] - Desempilhar");
	printf("\n[D] - Elemento topo");
	printf("\n[E] - Exibe pilha");
	printf("\n[ESC] - Sair\n");
	return toupper(getch());
}

int main(void)
{
	TpPilhaM2 pilha;
	char op;
	int np, qtde, num;
	
	do
	{
		op = menu();
		switch(op)
		{
			case 'A':
				printf("\n\nINICIALIZAR\n");
				printf("\nDigite a quantidade de pilhas: ");
				scanf("%d",&qtde);
				inicializar(pilha,qtde);
				printf("\nPilha inicializada!");
				
				break;
				
			case 'B':
				printf("\n\INSERIR\n");
				printf("\nNumero da pilha: ");
				scanf("%d",&np);
				printf("\nElemento: ");
				scanf("%d",&num);
				while(!pilhaCheia(pilha,np) && num != 0)
				{
					if(!pilhaCheia(pilha,np))
					{
						inserir(pilha,num,np);
						printf("\nNumero da pilha: ");
						scanf("%d",&np);
						printf("\nElemento: ");
						scanf("%d",&num);	
					}
					else
						printf("\nPilha cheia!");
				}
				
				break;
				
			case 'C':
				printf("\nRETIRAR\n");
				
				printf("\nNumero da pilha: ");
				scanf("%d",&np);
	
				if(!pilhaVazia(pilha,np))
					printf("\nElemento retirado: %d",retirar(pilha,np));
				else
					printf("\nPilha vazia!");
				
				break;
			
			case 'D':
				printf("\n\nELEMENTO TOPO\n");
				printf("\nNumero da pilha: ");
				scanf("%d",&np);

				if(!pilhaVazia(pilha,np))
					printf("\nElemento do topo: %d",elementoTopo(pilha,np));
				else
					printf("\nPilha vazia!");
					
				break;
			
			case 'E':
				printf("\n\nEXIBE PILHA\n");
				printf("\nNumero da pilha: ");
				scanf("%d",&np);
				if(!pilhaVazia(pilha,np))
					exibir(pilha,np);
				else
					printf("\nPilha vazia!\n");
				
				break;
				
			case 27:
				printf("\nTeste encerrado!\n");
				
				break;
		}
		getch();
	}while(op != 27);
	
	return 0;
}

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio2.h>
#include <unistd.h>
#include <time.h> 

#include "TADPilhaM2.h"
#include "TADVisual.h"

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

void exibirTorres(TpPilhaM2 pm)
{
    printf("\nTorre 1: "); exibir(pm, 0);
    printf("\nTorre 2: "); exibir(pm, 1);
    printf("\nTorre 3: "); exibir(pm, 2);
}

char validarMovimento(TpPilhaM2 pm, int origem, int destino)
{
	int aux=1;
    if (pilhaVazia(pm, origem))
    {
        printf("\nTorre de origem vazia! Escolha outra torre\n");
        aux = -1;
    }
	else
	{
    	int topoOrigem = elementoTopo(pm, origem);
    	int topoDestino;

        if (pilhaVazia(pm, destino))
		{
            topoDestino = 0; //***
        } else
		{
            topoDestino = elementoTopo(pm, destino);
        }

        if (topoOrigem > topoDestino)
        {
            printf("\n[Movimento invalido!]\n Disco maior nao pode ficar sobre disco menor\n");
            aux=-1;
            getch();
        }
	}

    return aux;
}

/* TODO (andressa#1#): adicionar funcao */
void moverDisco(TpPilhaM2 &pm, int origem, int destino)
{
    int disco = retirar(pm, origem);
    inserir(pm, disco, destino);
}

//andressa
void manual(TpPilhaM2 &pm)
{
	system("cls");
	FormularioMenu();
    int qtdeDisco, i = 0, valor, movimento = 0;
    int sair = 0;
    TpTorre t;
	Layout("Modo Manual");

	
    printf("\nQuantidade de discos (MIN:3 - MAX:10): ");
    scanf("%d", &qtdeDisco);

    if(qtdeDisco >= 3 && qtdeDisco <= 10)
    {
        t.origem = 0;
        valor = qtdeDisco;
        while (i < qtdeDisco)
        {
            inserir(pm, valor, 0); // origem
            valor--;
            i++;
        }

        exibirTorres(pm);
        getch();

        printf("\nPara qual pilha voce deseja levar a torre? (2 - 3): ");
        scanf("%d", &t.destino);
        t.destino--;

		if (t.destino == 1) {
            t.aux = 2;
        } else {
            t.aux = 1;
        }

        printf("\n\n*** MOVIMENTANDO DA TORRE %d PARA TORRE %d\n", t.origem + 1, t.destino + 1);

        while (sair != -1 || !pilhaVazia(pm, t.origem) && !pilhaVazia(pm, t.aux)) //movimentacao
        {
            int origem, destino;
            exibirTorres(pm);
            printf("\n\nDe qual torre deseja mover o disco? (1, 2 ou 3): ");
            scanf("%d", &origem);
            origem--;

            printf("\nPara qual torre deseja mover o disco? (1, 2 ou 3): ");
            scanf("%d", &destino);
            destino--;

            if (validarMovimento(pm, origem, destino))
            {
                moverDisco(pm, origem, destino);
                movimento++;
            }

            if (pilhaVazia(pm, t.origem) && pilhaVazia(pm, t.aux) && !pilhaVazia(pm, t.destino)) //se chegou no fim
            {
                printf("\n\n*** Jogo completado com sucesso em [%d] movimentos! ***\n", movimento);
                sair = -1;
                getch();
            }
        }
    }
    else
    {
    	limpatela();
        printf("\nQuantidade de discos invalida!\n");
        getch();
    }
}




//gui
void manual(TpPilhaM2 &pm)
{
	int qtdeDisco, i=0, valor, movimento=0, op;
	int origem;
	TpTorre t;
	
	printf("\nQuantidade de discos (MIN:3 - MAX:10): ");
	scanf("%d",&qtdeDisco);
	if(qtdeDisco >=3 && qtdeDisco <= 10)
	{
		t.origem = 0;
		valor = qtdeDisco;
		while(i<qtdeDisco)
		{
			inserir(pm,valor,0); //na torre origem?
			valor--;
			i++;
		}
	
		//TESTE PARA SABER SE ESTÁ TUDO CERTO NO INSERIR
		exibir(pm,t.origem);
		getch();
		
		//opção 2-3 porque a torre já começa na 1
        printf("\nPara qual torre deseja mover o disco? (2 ou 3): ");
        scanf("%d",&t.destino);
		t.destino--;//trantando o destino já que nas pilhas são 0,1,2
		
		if(t.destino == 1) //pilha 2
			t.aux = 2;
		else
		if(t.destino == 2) //pilha 3
			t.aux = 1;
		else
			printf("\nTorre invalida!\n");
		
		while(!pilhaVazia(pm,0) && !pilhaVazia(pm,t.aux))
		{
			
			/*
			aqui teria que fazer a parte de perguntar a torre de onde ele vai tirar o disco e para qual torre
			ele deseja levar, fazendo as validações se é possivel ou não fazer a movimentação.
			A repetição vai se encerrar quando não houver mais disco na origem e tambem na auxiliar
			isso indica que todos os disco estão devidamente na torre destino.
				
			OQUE FAZER NESSA REPETIÇÃO COLOCAMOS NO IF DE BAIXO
			*/
			if(pilhaVazia(pm,t.destino))
				inserir(pm,retirar(pm,t.origem),t.destino);
			else
			if(elementoTopo(pm,t.origem) < elementoTopo(pm,t.destino))
				inserir(pm,retirar(pm,t.origem),t.destino);
			
			printf("\n\nDe qual torre deseja mover o disco? (1, 2 ou 3): ");
	        scanf("%d",&t.origem);
	        t.origem--;
			printf("\nPara qual torre deseja mover o disco? (2 ou 3): ");
       		scanf("%d",&t.destino);
			t.destino--;	
				
			movimento++; //contador para saber o total de movimentos
		}
		
		
	}
	else
		printf("\nQuantidade de disco invalida!\n");

}

void automatico(TpPilhaM2 &pm)
{
	int qtdeDisco, i=0, valor;
	TpTorre t;
	Layout("Modo Automatico");
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
		
		Layout("TORRE DE HANOI");

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

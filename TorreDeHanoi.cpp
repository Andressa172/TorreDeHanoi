#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio2.h>
#include <unistd.h>
#include <time.h> 
#include<math.h>

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
    if(pilhaVazia(pm,origem))
    {
        printf("\nTorre de origem vazia! Escolha outra torre\n");
        aux = -1;
    }
	else
	{
    	int topoOrigem = elementoTopo(pm,origem);
    	int topoDestino;

        if(pilhaVazia(pm,destino))
		{
            topoDestino = 0; //***
        }
		else
		{
            topoDestino = elementoTopo(pm, destino);
        }

        if(topoOrigem > topoDestino)
        {
            printf("\n[Movimento invalido!]\n Disco maior nao pode ficar sobre disco menor\n");
            aux = -1;
        }
	}
	getch();
    return aux;
}

/* TODO (andressa#1#): adicionar funcao */
void moverDisco(TpPilhaM2 &pm, int origem, int destino)
{
    int disco = retirar(pm, origem);
    inserir(pm, disco, destino);
}

//andressa
//void manual(TpPilhaM2 &pm)
//{
//	system("cls");
//	FormularioMenu();
//    int qtdeDisco, i = 0, valor, movimento = 0;
//    int sair = 0;
//    TpTorre t;
//	Layout("Modo Manual");

//	
//    printf("\nQuantidade de discos (MIN:3 - MAX:10): ");
//    scanf("%d", &qtdeDisco);

//    if(qtdeDisco >= 3 && qtdeDisco <= 10)
//    {
//        t.origem = 0;
//        valor = qtdeDisco;
//        while (i < qtdeDisco)
//        {
//            inserir(pm, valor, 0); // origem
//            valor--;
//            i++;
//        }

//        exibirTorres(pm);
//        getch();

//        printf("\nPara qual pilha voce deseja levar a torre? (2 - 3): ");
//        scanf("%d", &t.destino);
//        t.destino--;

//		if (t.destino == 1) {
//            t.aux = 2;
//        } else {
//            t.aux = 1;
//        }

//        printf("\n\n*** MOVIMENTANDO DA TORRE %d PARA TORRE %d\n", t.origem + 1, t.destino + 1);

//        while (sair != -1 || !pilhaVazia(pm, t.origem) && !pilhaVazia(pm, t.aux)) //movimentacao
//        {
//            int origem, destino;
//            exibirTorres(pm);
//            printf("\n\nDe qual torre deseja mover o disco? (1, 2 ou 3): ");
//            scanf("%d", &origem);
//            origem--;

//            printf("\nPara qual torre deseja mover o disco? (1, 2 ou 3): ");
//            scanf("%d", &destino);
//            destino--;

//            if (validarMovimento(pm, origem, destino))
//            {
//                moverDisco(pm, origem, destino);
//                movimento++;
//            }

//            if (pilhaVazia(pm, t.origem) && pilhaVazia(pm, t.aux) && !pilhaVazia(pm, t.destino)) //se chegou no fim
//            {
//                printf("\n\n*** Jogo completado com sucesso em [%d] movimentos! ***\n", movimento);
//                sair = -1;
//                getch();
//            }
//        }
//    }
//    else
//    {
//    	limpatela();
//        printf("\nQuantidade de discos invalida!\n");
//        getch();
//    }
//}


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
			inserir(pm,valor,0);
			valor--;
			i++;
		}

		printf("\nPara qual haste deseja mover o disco? (2 ou 3): ");
	    scanf("%d",&t.destino);
		t.destino--;
		do
		{
			//VALIDAÇÃO PARA FAZER AS MOVIMENTAÇÕES
       		if(pilhaVazia(pm,t.destino))
       		{
				inserir(pm,retirar(pm,t.origem),t.destino);
       			printf("\nDisco movido com sucesso!");
       			movimento++;
       		}
       		else
			if(elementoTopo(pm,t.origem) < elementoTopo(pm,t.destino))
			{
				inserir(pm,retirar(pm,t.origem),t.destino);
				printf("\nDisco movido com sucesso!");
				movimento++;
			}
			else
				printf("Erro! Nao foi possivel realizar o movimento!\n");
				
			
			//EXIBIÇÃO DAS PILHAS
			if(pilhaVazia(pm,0))
			{
				printf("\nPilha vazia!"); 
				printf("\nPILHA 1\n");
			}
			else
			{
				exibir(pm,0);
				printf("\nPILHA 1\n");
			}
			
			if(pilhaVazia(pm,1))
			{
				printf("\nPilha vazia!");
				printf("\nPILHA 2\n");
			}
			else
			{
				exibir(pm,1);
				printf("\nPILHA 2\n");
			}
			
			if(pilhaVazia(pm,2))
			{
				printf("\nPilha vazia!");
				printf("\nPILHA 3\n");
			}
			else
			{
				exibir(pm,2);
				printf("\nPILHA 3\n");
			}	
			
			//VERIFICANDO SE A PESSOA AINDA NÃO GANHOU PARA SEGUIR JOGANDO
			if((!pilhaVazia(pm,0) && !pilhaVazia(pm,1))
		 	|| (!pilhaVazia(pm,0) && !pilhaVazia(pm,2)) || (!pilhaVazia(pm,1) && !pilhaVazia(pm,2)))
		 	{
		 		printf("\n\nDe qual torre deseja mover o disco? (1, 2 ou 3): ");
		        scanf("%d",&t.origem);
		        t.origem--;
				printf("\nPara qual torre deseja mover o disco? (1, 2 ou 3): ");
	       		scanf("%d",&t.destino);
				t.destino--;
				
				//FAZER VERIFICAÇÃO SE CASO O CARA NÃO DIGITAR NUMERO VALIDOS (1, 2 E 3)	
		 	}
		 	
		 	//SE CASO A PESSOA CONSEGUIU MOVER TUDO
		 	if((pilhaVazia(pm,0) && pilhaVazia(pm,1))
		 	|| (pilhaVazia(pm,0) && pilhaVazia(pm,2)) || (pilhaVazia(pm,1) && pilhaVazia(pm,2)))
		 		printf("\nPARABENS VOCE GANHOU!\n");
		
		}while((!pilhaVazia(pm,0) && !pilhaVazia(pm,1))
		 || (!pilhaVazia(pm,0) && !pilhaVazia(pm,2)) || (!pilhaVazia(pm,1) && !pilhaVazia(pm,2)));
		 
		 printf("\nTotal de movimentos: %d\n",movimento);
	}
	else
		printf("\nQuantidade de disco invalida!\n");

}

//SIMULAÇÃO AUTOMATICA
void automatico(TpPilhaM2 &pm)
{
    int disco, i, qtdeDisco, auxiliar;
    int movimentosTotal;
    TpTorre t;
    
    t.origem = 0; //sempre começa na pilha 1
    //PEGANDO A QUANTIADE DE DISCO QUE VAI SER MOVIMENTADO
    printf("\nQuantidade de discos (MIN:3 - MAX:10): ");
    scanf("%d",&qtdeDisco);
    
    //CALCULANDO A QUANTIDADE TOTAL DE MOVIMENTOS PARA FINALIZAR AS MOVIMENTAÇÕES
    movimentosTotal = pow(2, qtdeDisco) - 1;
    
    //PERGUNTANDO PARA QUAL HASTE ELE VAI QUERER MOVIMENTAR
    printf("\nPara qual haste voce deseja levar os disco? (2 - 3): ");
    scanf("%d",&t.destino);
    t.destino--;

	if(t.destino == 1)
    	t.aux = 2;
    if(t.destino == 2)
        t.aux = 1;
        
    if(t.destino != 1 && t.destino != 2)
    	printf("\nErro! Essa pilha não existe");
    else
    {
	    //SE O NUMERO DE DISCO ESCOLHIDO FOR IMPAR DESTINO E AUXILAR TROCAM O PAPEL
		if(qtdeDisco % 2 == 0)
		{
		    auxiliar = t.destino;
		    t.destino = t.aux;
		    t.aux = auxiliar;
		}
		
		//INSERINDO OS DISCO DENTRO A PILHA ORIGEM
		disco = qtdeDisco;
		i=0;
		while(i<qtdeDisco)
		{
			inserir(pm,disco,t.origem);
			disco--;
			i++;
		}
			
		i=1;
		while(i <= movimentosTotal)
		{
		    if(i%3 == 1) //HASTE 1
			{
		        //MOVIMENTAÇÃO DO DISCO DA HASTE ORIGEM PARA A HASTE DESTINO
		        if(pilhaVazia(pm,t.destino) || (!pilhaVazia(pm,t.origem) && elementoTopo(pm,t.origem) < elementoTopo(pm,t.destino)))
				{
		                printf("\nMovendo disco da haste %d para haste %d\n",t.origem+1,t.destino+1);
		                inserir(pm,retirar(pm,t.origem),t.destino);
		        }
				else //movendo da destino para origem
				{
		            printf("\nMovendo disco da haste %d para haste %d\n",t.destino+1,t.origem+1);
		            inserir(pm,retirar(pm,t.destino),t.origem);
		        }
		    }
			else
			if(i%3 == 2) //HASTE 2
			{
		        //MOVIMENTAÇÃO DO DISCO DA HASTE ORIGEM PARA A HASTE AUXILIAR
		        if(pilhaVazia(pm,t.aux) || (!pilhaVazia(pm,t.origem) && elementoTopo(pm,t.origem) < elementoTopo(pm,t.aux)))
				{
		            printf("\nMovendo disco da haste %d para haste %d\n",t.origem+1,t.aux+1);
		            inserir(pm,retirar(pm,t.origem),t.aux);
		        }
				else //movendo da auxiliar para origem
				{
		            printf("\nMovendo disco da haste %d para haste %d\n",t.aux+1,t.origem+1);
		            inserir(pm,retirar(pm,t.aux),t.origem);
		        }
		    }
			else
			if(i%3 == 3) //HASTE 3
			{
				//MOVIMENTAÇÃO DO DISCO DA HASTE AUXILAR PARA HASTE DESTINO
		        if(pilhaVazia(pm,t.destino) || (!pilhaVazia(pm,t.aux) && elementoTopo(pm,t.aux) < elementoTopo(pm,t.destino)))
				{
		            printf("\nMovendo disco da haste %d para haste %d\n",t.aux+1,t.destino+1);
		            inserir(pm,retirar(pm,t.aux),t.destino);
		        }
				else //movendo da destino para auxiliar
				{
		                printf("\nMovendo disco da haste %d para haste %d\n",t.destino+1,t.aux+1);
		                inserir(pm,retirar(pm,t.destino),t.aux);
		        }
		    }
		    i++; //CONTATOR PARA ENCERRAR QUANDO BATER A QUANTIDADE DE PASSOS TOTAL
		    
		    //EXIBIÇÃO DAS PILHAS
			if(pilhaVazia(pm,0))
			{
				printf("\nPilha vazia!"); 
				printf("\nPILHA 1\n");
			}
			else
			{
				exibir(pm,0);
				printf("\nPILHA 1\n");
			}
			
			if(pilhaVazia(pm,1))
			{
				printf("\nPilha vazia!");
				printf("\nPILHA 2\n");
			}
			else
			{
				exibir(pm,1);
				printf("\nPILHA 2\n");
			}
			if(pilhaVazia(pm,2))
			{
				printf("\nPilha vazia!");
				printf("\nPILHA 3\n");
			}
			else
			{
				exibir(pm,2);
				printf("\nPILHA 3\n");
			}	
		}
		printf("\nAutomatico finalizado!\n");
		printf("\nMovimentacoes: %d",movimentosTotal);
		getch();
	}
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
				printf("\nJJogo encerrado!\n"); //pode colocar na parte de mensagem do jogo
		}
		getch();
	}while(op != 27);
	
	return 0;
}

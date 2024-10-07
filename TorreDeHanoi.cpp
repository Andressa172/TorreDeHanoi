#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio2.h>
#include<unistd.h>
#include<time.h> 
#include<math.h>

#include "bootstrap.h"
#include "TADPilhaM2.h"

//STRUCT PARA AUXILIAR NAS MOVIMENTAÇÕES ENTRE AS PILHAS
struct TpTorre
{
	int origem, destino, aux;
};

//FUNÇÃO QUE TEM AS OPÇÕES DO MENU
char menuPrincipal(void)
{
	application();
    consolePrintf("topo", "verde", 0, "TORRE DE HANOI");
    consolePrintf("subMenu", "verde", 0, "Selecione um item:");
    consolePrintf("esquerda", "branco", 0, "[A] Jogar manual");
    consolePrintf("esquerda", "branco", 1, "[B] Jogar automatico");
    consolePrintf("esquerda", "branco", 2, "[C] Infos sobre o jogo");
    consolePrintf("esquerda", "branco", 5, "[ESC] - Sair");
    gotoxy(4, 15);
	
	return toupper(getche()); 
}

//FUNÇÃO QUE EXIBE AS PILHAS PARA O USUARIO
void mostrarPilhas(TpPilhaM2 &pm)
{
	//EXIBIÇÃO DAS PILHAS
	if(pilhaVazia(pm,0))
	{
		limpandoArea("rightside");
		consolePrintf("direita", "verde_claro", 10, "Vazia");
    	consolePrintf("direita", "verde", 11, "PILHA 1");
//		printf("\nPilha vazia!"); 
//		printf("\nPILHA 1\n");
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
		getch();
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

//FUNÇÃO QUE COLOCA A QUANTIADE DE DISCO NA PILHA 1
void colocarDisco(TpPilhaM2 &pm, int qtdeDisco)
{
	int i=0, disco = qtdeDisco;
	
	while(i<qtdeDisco)
	{
		inserir(pm,disco,0);
		disco--;
		i++;
	}
}

//FUNÇÃO DO JOGO MANUAL
void manual(TpPilhaM2 &pm)
{
	int qtdeDisco, i=0, valor, movimento=0, op;
	int origem;
	TpTorre t;
	application();
    consolePrintf("topo", "verde", 0, "JOGO MANUAL");
    consolePrintf("subMenu", "verde", 0, "     Jogando...    ");
    consolePrintf("esquerda", "branco", 0, "[0] Voltar Menu");
    consolePrintf("direita", "rosa_claro", 0, "Qual a quantidade de discos?");
    consolePrintf("direita", "rosa", 1, "(MIN:3 - MAX:10) ");
	scanf("%d",&qtdeDisco);
	
	if(qtdeDisco >=3 && qtdeDisco <= 10)
	{
		//o jogo começa sempre na haste 0
		t.origem = 0;
		
		//colocando a quantidade de disco na haste de inicio
		colocarDisco(pm,qtdeDisco);
		
		//EXIBIÇÃO DAS PILHAS
		mostrarPilhas(pm);
		do
		{
			limpandoArea("rightside");
			consolePrintf("direita", "rosa_claro", 0, "De qual torre deseja mover o disco?");
    		consolePrintf("direita", "rosa", 1, "(1, 2 ou 3): ");
			scanf("%d",&t.origem);
			t.origem--;
			consolePrintf("direita", "rosa_claro", 3, "Para qual torre deseja mover o disco?");
    		consolePrintf("direita", "rosa", 4, "(1, 2 ou 3): ");
			scanf("%d",&t.destino);
			t.destino--;
			if(t.origem != t.destino)
			{
				if((t.destino >= 0 && t.destino <= 2) && (t.origem >= 0  && t.origem <= 2))
				{
					//VALIDAÇÃO PARA FAZER AS MOVIMENTAÇÕES
		       		if(pilhaVazia(pm,t.destino))
		       		{
						inserir(pm,retirar(pm,t.origem),t.destino);
						limpandoArea("rightside");
						consolePrintf("direita", "verde_claro", 0, "Movido da haste %d\t->\t%d",t.origem+1,t.destino+1);
		       			movimento++;
		       		}
		       		else
					if(elementoTopo(pm,t.origem) < elementoTopo(pm,t.destino))
					{
						inserir(pm,retirar(pm,t.origem),t.destino);
						textcolor(GREEN);
		       			printf("\nMovido da haste: %d \t Para haste: %d",t.origem+1,t.destino+1);
						movimento++;
					}
					else
					{
						textcolor(RED);
						printf("Erro! Nao foi possivel realizar o movimento!\n");
					}
					//VOLTANDO PARA COR PADRÃO DO PROGRAMA
					textcolor(WHITE);	
					
					//EXIBIÇÃO DAS PILHAS
					mostrarPilhas(pm);
				}
				else
				{
					textcolor(RED);
					printf("\nErro! Voce digitou uma haste que nao existe! Digite novamente...");
					textcolor(WHITE);
					printf("\nPara qual haste deseja mover o disco? (2 ou 3): ");
				    scanf("%d",&t.destino);
					t.destino--;
				}
			}
			else
			{
				textcolor(RED);
				printf("Erro! Nao e possivel mover para mesma haste!\n");
				textcolor(WHITE);
			}
			
			//VERIFICANDO SE A PESSOA GANHOU
			if((pilhaVazia(pm,0) && pilhaVazia(pm,1)) || (pilhaVazia(pm,0) && pilhaVazia(pm,2)))
			{
			 	textcolor(13);
				printf("\nPARABENS VOCE GANHOU!\n");
				textcolor(WHITE);
			}
		}while((!pilhaVazia(pm,0) && !pilhaVazia(pm,1))
		 || (!pilhaVazia(pm,0) && !pilhaVazia(pm,2)) || (!pilhaVazia(pm,1) && !pilhaVazia(pm,2)));
		 textcolor(WHITE);
		 printf("\nTotal de movimentos: %d\n",movimento);
	}
	else
	{
		textcolor(RED);
		printf("\nErro! Quantidade de disco invalida!\n");
		textcolor(WHITE);
	}
}

//FUNÇÃO QUE MOVE O AUTOMATICO
void moverAutomatico(TpPilhaM2 &pm, int origem, int destino)
{
	if(pilhaVazia(pm,origem) && !pilhaVazia(pm,destino))
		inserir(pm,retirar(pm,destino),origem);
	else
	if(!pilhaVazia(pm,origem) && pilhaVazia(pm,destino))
		inserir(pm,retirar(pm,origem),destino);
	else
	if(elementoTopo(pm,origem) > elementoTopo(pm,destino))
		inserir(pm,retirar(pm,destino),origem);
	else
		inserir(pm,retirar(pm,origem),destino);
}

//SIMULAÇÃO AUTOMATICA
void automatico(TpPilhaM2 &pm)
{
    int i, qtdeDisco, auxiliar;
    int movimentosTotal;
    TpTorre t;
    
    t.origem = 0;
    t.aux = 1;
    t.destino = 2;
    
    //PEGANDO A QUANTIADE DE DISCO QUE VAI SER MOVIMENTADO
    printf("\nQuantidade de discos (MIN:3 - MAX:10): ");
    scanf("%d",&qtdeDisco);
    
    if(qtdeDisco >= 3 && qtdeDisco <= 10)
    {
    	//CALCULANDO A QUANTIDADE TOTAL DE MOVIMENTOS PARA FINALIZAR AS MOVIMENTAÇÕES
    	movimentosTotal = pow(2, qtdeDisco) - 1;
    	
    	//SE O NUMERO DE DISCO ESCOLHIDO FOR IMPAR DESTINO E AUXILAR TROCAM O PAPEL
		if(qtdeDisco % 2 == 0)
		{
		    auxiliar = t.destino;
		    t.destino = t.aux;
		    t.aux = auxiliar;
		}
		
		//INSERINDO OS DISCO DENTRO A PILHA ORIGEM
		colocarDisco(pm,qtdeDisco);
		
		//mostrando pilha inicial para o usuario
		mostrarPilhas(pm);
			
		i=1;
		while(i <= movimentosTotal)
		{
		    if(i%3 == 1) //HASTE 1
				moverAutomatico(pm,t.origem,t.destino);
			else
			if(i%3 == 2) //HASTE 2
				moverAutomatico(pm,t.origem,t.aux);
			else
			if(i%3 == 0) //HASTE 3
				moverAutomatico(pm,t.aux,t.destino);
				
			//mostrar as pilhas para o usuario
			printf("\n\n%d.o MOVIMENTACAO",i);
			mostrarPilhas(pm);
				
		    i++; //CONTATOR PARA ENCERRAR QUANDO BATER A QUANTIDADE DE PASSOS TOTAL
		    //Sleep(500);
		}
		textcolor(GREEN);
		printf("\nAutomatico finalizado!\n");
		textcolor(WHITE);
		printf("\nMovimentacoes: %d",movimentosTotal);
		getch();
	}
	else
	{
		textcolor(RED);
		printf("\nErro! Quantidade de disco invalida");
		textcolor(WHITE);
	}
}

//FUNÇÃO QUE MOSTRA AS INFORMAÇÕES E REGRAS DO JOGO
void informacoes(void)
{
	char op;
	do{
		application();
		consolePrintf("topo", "verde", 0, "Regras e Informacoes do Jogo");
		consolePrintf("subMenu", "verde", 0, "Selecione um item:");
		consolePrintf("esquerda", "branco", 0, "[M] Manual");
		consolePrintf("esquerda", "branco", 1, "[A] Automatico");
		consolePrintf("esquerda", "branco", 2, "[ESQ] Voltar Menu");
		gotoxy(4, 15);
    	
        op = toupper(getche());
        
        switch(op){
            case 'M':
            	consolePrintf("direita", "rosa_claro", 0, "Manual:");
				consolePrintf("direita", "branco", 1, "informacoes das regras do manual devem ser inseridas aqui xxxx");
				consolePrintf("direita", "branco", 2, "xxxx xxxx xxxx xxxx xxxx xxxx xxxx");
				getch();
				limpandoArea("rightside");
				application();            
                break;
            case 'A':
            	consolePrintf("direita", "rosa_claro", 0, "Automatico:");
				consolePrintf("direita", "branco", 1, "informacoes das regras do automatico devem ser inseridas aqui xxxx");
				consolePrintf("direita", "branco", 2, "xxxx xxxx xxxx xxxx xxxx xxxx xxxx");
				getch();      
				limpandoArea("rightside");
				application();          
                break;
		}
	}while(op!=27);	
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
			
			case 'C':
				informacoes();
				break;
				
//			case 27:
//				printf("\nJogo encerrado!\n"); //pode colocar na parte de mensagem do jogo
		}
		getch();
	}while(op != 27);
	return 0;
}

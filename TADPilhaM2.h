#define MAXPILHA 6

struct TpPilhaM2
{
	int base[MAXPILHA], topo[MAXPILHA], pilha[MAXPILHA];
};

void inicializar(TpPilhaM2 &pm, int qtde)
{
	int i, qtdeElem = MAXPILHA / qtde;
	
	for(i=0; i<=qtde; i++)
	{
		pm.base[i] = qtdeElem * i;
		pm.topo[i] = pm.base[i]- 1;
	}
}

void inserir(TpPilhaM2 &pm, int elem, int np)
{
	pm.pilha[++pm.topo[np]] = elem;
}

int retirar(TpPilhaM2 &pm, int np)
{
	return pm.pilha[pm.topo[np]--];
}

char pilhaVazia(TpPilhaM2 pm, int np)
{
	return pm.topo[np] < pm.base[np];
}

char pilhaCheia(TpPilhaM2 pm, int np)
{
	return pm.topo[np]+1 == pm.base[np+1];
}

int elementoTopo(TpPilhaM2 pm, int np)
{
	return pm.pilha[pm.topo[np]];
}

void exibir(TpPilhaM2 pm, int np)
{
	while(!pilhaVazia(pm,np))
		printf("\nElemento: %d",retirar(pm,np));
}

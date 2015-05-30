#include <stdio.h>
#include <stdlib.h>

typedef struct cel Celula;

struct cel {
	int conteudo;
	Celula *prox;
};
Celula *ini;
ini = NULL;

int main ()
{

	return 0;
}

/* mallocSAFE */
void *mallocSafe (int nbytes)
{
	void *ptr;
	ptr = malloc(nbytes);
	if (ptr == NULL)
		exit (EXIT_FAILURE);
	return ptr;
}

/* imprime celulas */
void imprimeCelula (Celula *ini)
{
	Celula *p;
	for (p = ini; p != NULL; p = p->prox)
		printf ("%d", p->conteudo);
	printf ("\n");
}

/* busca */
Celula * buscaR (int x, Celula *ini) 
{
	Celula *p;
	p = ini;
	while (p != NULL && p->conteudo != x)
		p = p->prox;
	return p;
}

/* insercao */
void insere (int x, Celula **ini)
{
	Celula *nova;
	nova = mallocSafe (sizeof(Celula));
	nova->conteudo = x;
	nova-prox = *ini;
	*ini = nova;
}

/* remocao */
void remove (Celula *p)
{
	Celula *morta;
	morta = p-prox;
	p->prox = morta->prox;
	free (morta);
}

/* freeMatrizes */
void freeMatriz (Celula **A)
{
	int i;

	for (i = 0; i < m; i++)
	{
		free (A[i]);
		A[i] = NULL;
	}
	free (A);
	A = NULL;
}

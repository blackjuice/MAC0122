/*
  \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

  AO PREENCHER ESSE CABECALHO COM O MEU NOME E O MEU NUMERO USP, 
  DECLARO QUE SOU O UNICO AUTOR E RESPONSAVEL POR ESSE PROGRAMA. 
  TODAS AS PARTES ORIGINAIS DESSE EXERCICIO PROGRAMA (EP) FORAM 
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUCOES DESSE EP
  E QUE PORTANTO NAO CONSTITUEM PLAGIO. DECLARO TAMBEM QUE SOU RESPONSAVEL
  POR TODAS AS COPIAS DESSE PROGRAMA E QUE EU NAO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUICAO. ESTOU CIENTE QUE OS CASOS DE PLAGIO SAO PUNIDOS COM 
  REPROVACAO DIRETA NA DISCIPLINA.

  Nome: Lucas Sung Jun Hong
  NUSP: 8124329

  IMDB: filmes.c


  Referencias: Com exceÃ§Ã£o das rotinas fornecidas no esqueleto e em sala
  de aula, caso voce tenha utilizado alguma referencia, liste-as abaixo
  para que o seu programa nao seja considerada plagio.


  \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/


/*----------------------------------------------------------*/
/* filmes.h e a interface para as funcoes neste modulo      */
#include "filmes.h" 

/*----------------------------------------------------------*/
#include <stdlib.h>  /* NULL, free() */
#include <stdio.h>   /* printf(), scanf() */ 
#include <string.h>  /* strlen(), strncpy(), strcmp() */

#include "utils.h"     /* Bool, mallocSafe() */
#include "iofilmes.h"



/*----------------------------------------------------------------------
    crieFilme(dist, votos, nota, nome, ano)

    Recebe informacoes dobre um filme 

        - dist  : distribuicao de notas
        - votos : numero de votos
        - nota  : nota do filme 
        - ano   : ano de producao do filme

    e cria uma celula do tipo Filme para armazenar essa informacao. 
    A funcao retorna o endereco da celula criada.
*/

Filme *
crieFilme (char dist[], int votos, float nota, char *nome, int ano)
{
    Filme *flm;
    int    len = strlen(nome) + 1; /* +1 para o '\0' */
    
    flm = mallocSafe(sizeof *flm);
    
    strncpy(flm->dist, dist, TAM_DIST+1); /* +1 para o '\0' */
    
    flm->votos = votos;
    flm->nota  = nota;
    
    flm->nome = mallocSafe(len*sizeof(char));
    strncpy(flm->nome, nome, len);
    
    flm->ano  = ano;
    
    flm->prox = flm->ant = NULL; /* paranoia */
    
    return flm;
 
}



/*----------------------------------------------------------------------
    crieListaFilmes()
  
    Cria uma estrutura que representa lista de filmes vazia.
    A funcao retorna o endereco dessa estrutura.

    Um lista de filmes e representada por uma lista encadeada 
    com cabeca duplamente ligada. 
*/

ListaFilmes *
crieListaFilmes()
{
    ListaFilmes *lst;
    
    lst =  mallocSafe(sizeof *lst);

    lst->nFilmes = 0;   
    lst->cab = mallocSafe(sizeof *lst->cab);

    lst->cab->ant  = lst->cab->prox = lst->cab;
    
    return lst;
}


/*----------------------------------------------------------------------
    libereListaFilmes(lst)

    Recebe um ponteiro lst para uma estrutura que representa uma lista 
    de filmes e libera toda a memoria alocada para a lista.

    Esta funcao utiliza a funcao libereFilme().
*/

void
libereListaFilmes(ListaFilmes *lst)
{
    Filme *p;

    for (p = lst->cab->prox; p != lst->cab; p = p->prox)
	libereFilme(p);	

    free (lst);
    /* End with 
	lst->nFilmes = 0; */
}


/*----------------------------------------------------------------------
    libereFilme(flm)

    Recebe um ponteiro flm para uma estrutura que representa um 
    filme e libera a area alocada.

*/

void 
libereFilme(Filme *flm)
{
    /* first we free the 2 chars and then we free the entire cell */
    free (flm->dist);
    free (flm->nome);

    free (flm);
}

/*----------------------------------------------------------------------
    insiraFilme(lst, flm)

    Recebe um ponteito lst para uma estrutura que representa
    uma lista de filmes e um ponteiro para uma estrutura
    que representa uma filme.

    A funcao insere o filme na lista.
    
*/

void 
insiraFilme(ListaFilmes *lst, Filme *flm)
{
    /* caso lista vazia */
    if (lst->nFilmes == 0)
    {
	flm->prox = lst->cab;
	flm->ant = lst->cab;
	lst->cab->prox = flm;
	lst->cab->ant = flm;

	lst->nFilmes++;
    }

    /* caso contrario */
    else
    {
	flm->prox = lst->cab;
	flm->ant = lst->cab->ant;
	lst->cab->ant = flm;
	lst->cab->ant->prox = flm; /* lst->cab->ant = celula anterior (anterior) */

	lst->nFilmes++;
    }
}

/*---------------------------------------------------------------------
    contemFilme(lst, flm)

    Recebe um ponteito lst para uma estrutura que representa
    uma lista de filmes e um ponteiro para uma estrutura
    que representa uma filme.
  
    A funcao retorna  TRUE se o filme esta na lista e 
    FALSE em caso contrario. 
  
    Consideramos que dois filmes f e g sao iguais se

         - f->nome  e' igual a g->nome )
         - f->nota  e' igual a g->nota
         - f->ano   e' igual a g->ano 

    Para comparar dois nomes voce pode usar alguma funcao da 
    bibliteca do c  como strcmp, strncmp (string,h) 
    ou a funcao strCmp (utils.h).

*/

Bool 
contemFilme(ListaFilmes *lst, Filme *flm)
{
    Filme *p; /* ponteiro para percorrer lista */

    /* caso lista vazia */
    if (lst->nFilmes == 0)
	return FALSE;

    /* caso contrario, andamos a lista */
    for (p = lst->cab->prox; p != lst->cab; p = p->prox)
	if (strCmp(p->nome, flm->nome) == 0) /* usamos funcao strCmp. Se return 0,  f->nome  e' igual a g->nome */
	    if (p->nota == flm->nota)
		if (p->ano == flm->ano)
		     return TRUE;
    return FALSE;
}


/*----------------------------------------------------------------------
     removaFilme(lst, flm)

     Remove da lista e filmes lst o filme dado por flm.
     
     Pre-condicao: a funcao supoe que o filme flm esta 
     na lista lst.
*/

void 
removaFilme(ListaFilmes *lst, Filme *flm)
{
    Filme *p, *q; /* q = ponteiro para celula anterior a flm */

    /* andamos na celula ate acharmos a desejada */
    for (p = lst->cab->prox; p != flm; p = p->prox);
    /* for (p = lst->cab; contemFilme (lst, flm); p = p->prox); */
    
    q = p->ant; /* q aponta para a celula anterior a aquela procurada */

    q->prox = p->prox;	 /* a celula anterior aponta para a proxima da flm */
    p = p->prox;	 /* p dara um passo a frente */
    p->ant = q;		 /* celula em frente a flm aponta, para tras, para onde q aponta */

    libereFilme (flm);
    p = NULL;
    q = NULL;

}


/*----------------------------------------------------------------------
    mergeSortFilmes(lst, criterio)

    Ordena uma lista de filmes utilizando o algoritmo quickSort 
    adaptado para listas encadeadas duplamente ligadas.

    Se criterio == NOTA, entao a lista deve ser ordenada
    em ordem decrescente de nota.

    Se criterio == NOME, entao a lista deve ser ordenada
    em ordem crescente de nome (ordem alfabetica).

    ------------------------------------------------------------------
    A ordenacao deve ser feita 'in-place', ou seja   
    o conteudo das celulas nao deve ser copiado,  
    apenas os ponteiros devem ser alterados.

    A funcao so deve utilizar espaco extra O(1).
    Hmmm, ok, sem levar em consideracao o espaco O(lg n)
    utilizado pela pilha da recursao).
    Em outras palavras, a funcao pode conter apenas declaracoes
    de umas poucas variaveis (um vetor v[0..n] conta como 
    n variaveis).

    ------------------------------------------------------------------
    Para ordenar por nome, veja a funcao strCmp em utils.[h|c].
*/

void 
mergeSortFilmes(ListaFilmes *lst, Criterio criterio)
{
    AVISO(mergeSortFilmes:  Vixe ainda nao fiz essa funcao...);
}


/*----------------------------------------------------------------------
    quickSortFilmes(lst, criterio) [opcional]

    Ordena uma lista de filmes utilizando o algoritmo quickSort 
    adaptado para listas encadeadas duplamente ligadas.

    Se criterio == NOTA, entao a lista deve ser ordenada
    em ordem decrescente de nota.

    Se criterio == NOME, entao a lista deve ser ordenada
    em ordem crescente de nome (ordem alfabetica).

    ------------------------------------------------------------------
    A ordenacao deve ser feita 'in-place', ou seja   
    o conteudo das celulas nao deve ser copiado,  
    apenas os ponteiros devem ser alterados.

    A funcao so deve utilizar espaco extra O(1).
    Hmmm, ok, sem levar em consideracao o espaco O(lg n)
    utilizado pela pilha da recursao).
    Em outras palavras, a funcao pode conter apenas declaracoes
    de umas poucas variaveis (um vetor v[0..n] conta como 
    n variaveis).

    ------------------------------------------------------------------
    Para ordenar por nome, veja a funcao strCmp em utils.[h|c].

*/

void 
quickSortFilmes(ListaFilmes *lst, Criterio criterio)
{
    AVISO(quickSortFilmes:  Vixe ainda nao fiz essa funcao...);
}

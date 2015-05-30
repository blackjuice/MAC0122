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

  Nome:  Lucas Sung Jun Hong    8124329

  ts.c
  Pitao II

  Referencias: Com exceÃ§Ã£o das rotinas fornecidas no esqueleto e em sala
  de aula, caso voce tenha utilizado alguma referencia, liste-as abaixo
  para que o seu programa nao seja considerada plagio.
	-http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
	-http://en.wikipedia.org/wiki/Symbol_table

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ESQUELETO
*/


/* iterface para o uso da funcao deste mÃ³dulo */
#include "ts.h"     /* tipo CelTS */

#include <stdlib.h> /* free() */
#include <string.h>

#include "util.h"  /* mallocSafe() */

/*-----------------------------------------------------------
    A tabela de simbolos dever ser implementada atraves de uma 
    __lista ligada com cabeca__. 

    Note que todas as listas, filas e pilhas neste EP sao com 
    cabeca.
*/

/* ponteiro para a celula cabeca da lista que representa a tabela
   de simbolos */
static CelTS *ini; 

/* funcao auxiliar */
static CelTS *endVarTS(char *nomeVar);

/*-------------------------------------------------------------
   initTS()

   Funcao que cria uma tabela de simbolos vazia.
   
   Em outras palavras, cria uma lista ligada com cabeca 
   vazia. Cada celula da lista e' do tipo CelTS.

 */

void 
initTS()
{
    ini = mallocSafe (sizeof *ini);
    ini->prox = NULL;
}


/*-------------------------------------------------------------
   getValorTS(nomeVar)

   Recebe o nome 'nomeVar' de uma variavel, procura 
   essa variavel na tabela de simbolos e retorna o seu valor.

   Esta funcao deve utilizar a funcao endVarTS().
 */

float
getValorTS(char *nomeVar)
{
    CelTS *p;

    /* procura na tabela a variavel e retorna o endereco da celula que representa a variavel */
    p = endVarTS(nomeVar);
    return p->valor;
}


/*-------------------------------------------------------------
   setValorTS(nomeVar,valor)

   Recebe o nome 'nomeVar' de uma variavel e um numero 'valor', 
   procura essa variavel na tabela de simbolos e atribui o numero 
   a essa variavel.

   Esta funcao deve utilizar a funcao endVarTS().
 */

void
setValorTS(char *nomeVar, float valor)
{
    CelTS *p;

    /* procuro a variavel */
    p = endVarTS(nomeVar);
    /* inserimos o numero na variavel */
    p->valor = valor;
    /* sendo que ja foi inicializada */
    p->inic = TRUE;
}

/*-------------------------------------------------------------
   freeTS()

   Funcao que libera toda a memoria alocada para a tabela
   de simbolos.

 */

void 
freeTS()
{
    CelTS *p, *aux;
    p = ini->prox;
    aux = p;

    while (p != NULL)
    {
	p = aux->prox;
	free (aux);
    }
}

/*-------------------------------------------------------------
   showTS()

   Funcao que para cada variavel na tabela de simbolos mostra:

       - o seu nome;
       - se a variavel foi ou nao inicializada
       - o valor atual da variavel.
 */

void
showTS()
{
    /* devemos andar na tabela */
    CelTS *p;

    printf ("\n==========================\n"
	    "  Tabela de simbolos\n"
	    "  nome - inicializada? - valor\n"
	    "--------------------------\n");

    /* andando na tabela */
    for (p = ini->prox; p != NULL; p = p->prox)
    {
	if (p->inic == TRUE)
	    printf ("%s - sim - %f", p->nomeVar, p->vFloat);

	if (p->inic == FALSE)
	    printf ("%s - nao - %f", p->nomeVar, p->vFloat);
    }
}


/*-------------------------------------------------------------
   endVarTS(nomeVar)

   Recebe um string 'nomeVar' com o nome de uma variavel e retorna
   o endereco da celula na tabela de simbolos que representa a 
   variavel. 

   Se na tabela de simbolos nao for encontrada uma celula que
   representa a variavel de nome 'nomeVar' uma nova celula e
   inserida na tabela para representar essa variavel.

   Esta funcao utiliza a funcao mallocSafe().
   Esta funcao aloca um string para copiar o nome da variavel 
   para o campo nomeVar da celula (strcpy ou strncpy ou ...).
 */

static CelTS *
endVarTS(char *nomeVar)
{
    CelTS *p, *end;
    char *copia;

    for (p = ini->prox; p != NULL; p = p->prox)
    {
	if (p->nomeVar == nomeVar)
	{
	    end = p->nomeVar;
	    return end;
	} 
	else
	    sdf
    }

    return NULL; 
}

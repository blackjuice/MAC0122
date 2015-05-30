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

  eval.c
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

/*------------------------------------------------------------*/
/* interface para as funcoes deste modulo */
#include "eval.h" 

/*------------------------------------------------------------*/
#include <stdlib.h>  /* free(), atoi(), atof() */
#include <string.h>  /* strncmp(), strlen(), strncpy(), strcpy() */
#include <math.h>    /* pow() */

/*------------------------------------------------------------*/
#include "classes.h" /* tipo Classe */
#include "ts.h"      /* getValorTS() e setValorTS() */

/*------------------------------------------------------------
  Tabela com a preceedencia do operadores

  http://www.ime.usp.br/~pf/algoritmos/apend/precedence.html
*/
static const int precedencia[MAX_OPERADORES] =
{
    /* 4 operadores relacionais com 2 simbolos  */
     4   /* "==" */ /* da esquerda para a direita */
    ,4   /* "!=" */ /* da esquerda para a direita */
    ,5   /* ">=" */ /* da esquerda para a direita */
    ,5   /* "<=" */ /* da esquerda para a direita */
    
    /* 2 operadores relacionais com 1 simbolo */
    ,5  /* ">"  */ /* da esquerda para a direita */
    ,5  /* "<"  */ /* da esquerda para a direita */ 
    
    /* 7 operadores aritmeticos */
    ,8  /* "^" */ /* da direita para a esquerda */
    ,7  /* "%" */ /* da esquerda para a direita */
    ,7  /* "*" */ /* da esquerda para a direita */
    ,7  /* "/" */ /* da esquerda para a direita */
    ,6  /* "+" */ /* da esquerda para a direita */
    ,6  /* "-" */ /* da esquerda para a direita */
    ,8  /* "_" */ /* da direita para a esquerda */
    
    /* 3 operadores logicos  */
    ,3  /* "&&" */ /* da esquerda para a direita */ 
    ,2  /* "||" */ /* da esquerda para a direita */
    ,8  /* "!"  */ /* da direita para a esquerda */

     /* atribuicao */ 
    ,1  /* "=" */ /* da direita para a esquerda */ 
}; 


/*-------------------------------------------------------------
    itensParaValores(iniFilaItens)
    
    Recebe uma lista ligada com cabeca iniFilaItens representado uma 
    fila de itens lexicos e converte o campo util de cada celula 
    para um valor como descrito a seguir. 

    Nessa conversao, o campo 'util' de cada celula recebe um valor 
    da seguinte maneira.

       - se o campo 'classe' da celula indica que 'item' e um ponteiro 
         para um string que representa um float (FLOAT_STR), 
         o campo 'vFloat' deve recebe o valor desse float;

       - se o campo 'classe' da celula indica que 'item' e um ponteiro 
         para um operador, o campo 'prec' deve receber a precedencia
         desse operador.
 
         Para isto utilize o vetor 'precedencia'declarado antes 
         desta funcao. 

	 Nesta funcao voce pode utilizar qualquer funcao da biblioteca
         string do C, como, por exemplo, atof().

   Esta funcao _nao_ deve alocar celula alguma, no entanto ela
   deve dar free nas estruturas que deixarem de ser necessarias.

*/

void
itensParaValores(CelUtil *iniFilaItens)
{
    CelUtil *p;
    float f;
    /* percorremos a lista normalmente */
    for (p = iniFilaItens->prox ; p != NULL; p = p->prox)
    {
	if (p->classe == FLOAT_STR)
	{
	    f = atof(p->pStr);	
	    free (p->pStr);	
	    p->vFloat = f;	
	    p->classe = FLOAT;	
	}
	if (p->classe < MAX_OPERADORES)   /* temos 17 operadores */
	    p->prec = precedencia[p->classe];
}


/*-------------------------------------------------------------
  FUNCOES PARA MANIPULACAO DE PILHAS
  Para isso, foram criadas 2 funcoes extras:
	- void stackPush ();
	- float stackPop ().
*/

/* "Empurrando" para a pilha */
void stackPush (float valor, CelUtil **topo)
{
    CelUtil *nova = mallocSafe (sizeof(CelUtil));
    /* insercao do valor no campo vFloat */
    nova->vFloat = valor; 
    /* nova passa a ser topo */
    nova->prox = NULL;
    (*topo)->prox = nova;
    *topo = nova;
    /* indicaremos a classe da celula nova */
    nova->classe = FLOAT;
}


/* "Retirando" da pilha */
float stackPop (CelUtil *iniPilha, CelUtil **topo)
{
    CelUtil *topoAnt;
    float valor;

    /* procuramos a celula anterior ao topo para que a mesma seja um novo topo */
    for (topoAnt = iniPilha; topoAnt->prox != *topo; topoAnt = topoAnt->prox);
    /* extraimos o conteudo da celula do topo */
    valor = (*topo)->vFloat; 
    /* libera o topo */
    free(*topo); 
    /* topo passa a ser celula anterior */
    (*topo) = topoAnt; 

    return valor;
}


float calculo (float op2, float op1, Classe operator)
{
    /* operadores aritmeticos */
    if(operator == OPER_ADICAO)
        return (op2 + op1);
    else if(operator == OPER_SUBTRACAO)
        return (op2 - op1);
    else if(operator == OPER_MULTIPLICACAO)
        return (op2 * op1);
    else if(operator == OPER_DIVISAO)
        return (op2 / op1);
    else if(operator == OPER_EXPONENCIACAO)
        return (pow(op2, op1));
    else if(operator == OPER_RESTO_DIVISAO)
        return (((op2/op1) - (int)(op2/op1)) * op1);
    else if(operator == OPER_MENOS_UNARIO) /* ultimo op * (sinal negativo) */
		return ((-1) * op2);

    /* operacoes relacionais 1 simbolo */
    else if(operator == OPER_MAIOR)
        return (op2 > op1);
    else if(operator == OPER_MENOR)
		return (op2 < op1);

    /* operacoes relacionais 2 simbolos */
    else if(operator == OPER_IGUAL)
		return (op2 == op1);

    else if(operator == OPER_DIFERENTE)
		return (op2 != op1);
    else if(operator == OPER_MAIOR_IGUAL)
		return (op2 >= op1);
    else if(operator == OPER_MENOR_IGUAL)
		return (op2 <= op1);

    /* operacoes logicos */
    else if(operator == OPER_LOGICO_AND)
		return (op2 && op1);
    else if(operator == OPER_LOGICO_OR)
		return (op2 || op1);
    else if(operator == OPER_LOGICO_NOT)
		return (!op2);

    /* atribuicao */
    else if(operator == OPER_ATRIBUICAO)
		return op2;
}


/*-------------------------------------------------------------
  eval(iniPosfixa, mostrePilhaExecucao)
  
  Recebe uma lista ligada como cabeca iniPosfixa que representa
  uma expressao em notacao posfixa. 
  
  A funcao percorre a expressao calculando os valores resultantes.
  Para isto e utilizada uma pilha de execucao. 
  
  A pilha de execucao e representada atraves de uma lista ligada
  com cabeca em que cada elemento e do tipo CelUtil.
  
  Ao final a funcao retorna o endereco da celula no topo da 
  pilha de execucao.
  
  O parametro mostrePilhaExecucao indica se os valores
  na pilha devem ser exibidos depois de qualquer alteracao na
  pilha de execucao.
  
  Esta funcao, ou qualquer funcao chamada por ela,
  pode alocar __no maximo__ uma celula CelUtil para ser a 
  cabeca da pilha. Isto pode ser particularmente util
  para aqueles que desejarem escrever um interface e biblioteca 
  como stack.h e stack.c feitas na aula
  desta semana.  

  Esta funcao deve dar free nas estruturas que deixarem de ser necessarias.

  usaremos:
  getValorTS() e setValorTS()
*/

CelUtil *
eval (CelUtil *iniPosfixa, Bool mostrePilhaExecucao)
{
    CelUtil *q, *iniPilha, *topo;
    CelUtil *s, *aux;

    float op;

    iniPilha = mallocSafe(sizeof(CelUtil));
    iniPilha->prox = NULL;

    topo = iniPilha;

    /* percorremos a fila */
    for (q = iniPosfixa->prox; q != NULL; q = q->prox)
    {
	if (q->classe == FLOAT)
	    stackPush(q->vFloat, &topo);

	else if (q->classe < 17)
	{
	    /* caso 1: operacao que utiliza apenas um operando */
	    op = 0; /* para inicializar op */
	    if (q->classe != OPER_MENOS_UNARIO && q->classe != OPER_LOGICO_NOT)
		op = stackPop(iniPilha, &topo);

	    /* caso 2: operacao que utiliza dois */
	    topo->vFloat = calculo(topo->vFloat, op, q->classe);
	}
	/* caso 3: operacao de atribuicao */
	else if (q->classe == OPER_ATRIBUICAO)
	{
	    op = stackPop(iniPilha, &topo);
	}

	if (mostrePilhaExecucao == TRUE)
	{
	    printf ("\n==========================\n"
		    "Pilha de execucao\n"
		    "Valor  -  Classe\n"
		    "---------------------------\n");

	   for (s = iniPilha->prox; s != topo->prox; s = s->prox)
		mostreUtil(s, VALOR);
	}
    }


    s = iniPilha;
    while(s != topo)
    {
	aux = s->prox;
	free(s);
	s = aux;
    }
}

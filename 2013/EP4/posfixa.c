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

  posfixa.c
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
#include "posfixa.h"

#include "util.h"  /* tipo CelUtil, freeUtil() */

/*-------------------------------------------------------------
    itensParaPosfixa(iniFilaInf)
    
    Recebe uma lista ligada com cabeca iniFilaInf representando uma 
    fila de itens de uma expressao infixa e retorna uma lista ligada 
    com cabeca contendo a fila que representacao a correspondente 
    expressao em notacao posfixa. 

    Nessa conversao, nenhuma celula nova deve ser criada a nao ser,
    possivelmente, a celula cabeca da notacao posfixa.  As demais 
    celulas devem simplesmente migrar da fila da notacao infixa 
    para a fila da notacao posfixa. 

    As celulas da notacao infixa que nao forem utilizadas na notacao 
    posfixa (abre e fecha parentese) devem ser liberadas (free).
*/

CelUtil *
infixaParaPosfixa (CelUtil *iniFilaInf)
{
    CelUtil *posf;
    CelUtil *p; /* para percorrer a lista iniFilaInf */

    /* percorremos  a lista */
    for (p = iniFilaInf; p != NULL; p = p->prox)
    {

   char *posf; 
   char *pi; int t; // pilha
   int n, i, j;

   n = strlen( inf);
   posf = mallocc( n * sizeof (char));
   pi = mallocc( n * sizeof (char));
   t = 0;
   pi[t++] = inf[0];                          // empilha '('
   for (j = 0, i = 1; /*X*/ inf[i] != '\0'; ++i) {
      // a pilha estÃ¡ em pi[0..t-1]
      switch (inf[i]) {
         char x;
         case '(': pi[t++] = inf[i];          // empilha
                   break;
         case ')': while (1) {                // desempilha
                      x = pi[--t];
                      if (x == '(') break;
                      posf[j++] = x;
                   }
                   break;
         case '+': 
         case '-': while (1) {
                      x = pi[t-1];
                      if (x == '(') break;
                      --t;                    // desempilha
                      posf[j++] = x;
                   }
                   pi[t++] = inf[i];          // empilha
                   break;
         case '*':
         case '/': while (1) {
                      x = pi[t-1];
                      if (x == '(' || x == '+' || x == '-') 
                         break;
                      --t;
                      posf[j++] = x;
                   }
                   pi[t++] = inf[i];
                   break;
         default:  posf[j++] = inf[i];
      }
   }
   free( pi);
   posf[j] = '\0';      
   return posf;
} 

    }

    return NULL; 
}

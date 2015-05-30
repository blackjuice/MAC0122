/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ARQUIVO

  Declaracoes da funcao que substitui um item lexico pelo seu 
  "valor" e da funcao que calcula o valor de uma expressao estao 
  neste arquivo.
*/

#ifndef _EVAL_H
#define _EVAL_H

#include "util.h"  /* tipo CelUtil */



/*-------------------------------------------------------------*/ 
/*  prototipos de funcoes e macros para funcoes                */

void itensParaValores (CelUtil *iniFila);

CelUtil *eval (CelUtil *iniPosfixa, Bool mostrePilhaExecucao);

#define mostreValor(pValor)        mostreUtil(pValor, VALOR)

#define mostreFilaValores(iniFila) mostreListaUtil(iniFila, VALOR) 

#define freeValor(pValor)          freeUtil(pValor)

#define freeFilaValores(iniFila)   freeListaUtil(iniFila)

#endif /* _EVAL_H */

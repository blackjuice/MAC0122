/*
 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

  AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
  DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
  TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM 
  DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
  E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
  POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
  SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
  REPROVAÇÃO DIRETA NA DISCIPLINA.

  Nome:  Lucas Sung Jun Hong
  NUSP:  8124329

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  
  http://www.tecgraf.puc-rio.br/~mgattass/fcg/trb09/IsmaelAndadePimentel/Trab3_CG/trbRR/image.c
  http://en.wikipedia.org/wiki/Assertion_%28software_development%29
  http://stackoverflow.com/questions/4747428/getting-rgb-array-from-image-in-c-sharp
  http://stackoverflow.com/questions/2332219/how-to-access-a-rgb-image-data
  http://social.msdn.microsoft.com/Forums/vstudio/en-US/79d828ff-7479-40e9-b02e-025ca4155a97/obtain-rgb-values-from-a-bitmap-image-in-c

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdio.h>  /* fprintf */
#include <stdlib.h> /* exit, EXIT_FAILURE  */

#include "imagem.h"   /* tipos e prototipos de de funcoes que manipulam imagens */
#include "io.h"      /* graveImagemPPM, carregueImagemPPM */
#include "graphic.h" /* myInit */
#include "main.h"    /* prototipos da funcoes deste arquivo e que serao chamadas
                         por graphics.c */

/*---------------------------------------------------------------*/
/* 
 *  C O N S T A N T E S 
 */

/* numero maximo de caracteres em um nome de arquivo */
#define MAX_NOME 128

/*---------------------------------------------------------------*/
/*
 *  P R O T Ó T I P O S
 */

static void 
mostreUso (char *nomePrograma);

/*---------------------------------------------------------------*/
/* 
 *  M A I N 
 */

int 
main(int argc, char *argv[])
{
  ImagemRGB *imgOriginal  = NULL; /* ponteiro para a imagem original */
  ImagemRGB *tela         = NULL; /* ponteiro para a imagem corrente ou atual */
  CelRegiao *listaRegioes = NULL; /* ponteiro para a lista de regioes */
  char nome[MAX_NOME];

  /* 1. pegue o nome do arquivo com a imagem da entrada padrao */
  nome = *argv[1];
  /* 2. carregue a imagem do arquivo*/
  imgOriginal = carregueImagemPPM (&nome);
  /* 3 crie a tela (imagem) em que trabalharemos */
  
  /* 4 copie a imagem lida para a tela */ 

  /* 5 crie a lista das regioes */

  /* 6 passe a bola para o OpenGL */  
  myInit(&argc, argv, tela, imgOriginal, listaRegioes);
  
  return 0; /* we never return here; this just keeps the compiler happy
               http://www.cs.umd.edu/class/fall2011/cmsc427/lectures.shtml */
}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S   
 *                 O B R I G A T O R I A S
 */

/*---------------------------------------------------------------*/
/* quit

   Chamada quando 'q' e teclada.
   Libera toda a memoria alocada dinamicamente.
   
   Esta funcao usa as funcoes freeImagemRGB e freeRegioes, ambas
   do modulo imagem.
 */

void 
quit (ImagemRGB *tela, ImagemRGB *img, CelRegiao *listaRegioes)
{
  printf("\nTchau! Tchau! Fui!\n");
  exit(EXIT_SUCCESS); /* a execução do programa termina neste ponto */
}

/*---------------------------------------------------------------*/
/* graveImagemRPG

   Chamada quando 'g' e teclada.
   Pede que o usuario digite o nome de um arquivo e 
   grava a imagem da tela nesse arquivo.

   Esta funcao usa a funcao graveImagemPPM do modulo io.
 */

void
graveImagemRGB(ImagemRGB *img)
{
  graveImagemPPM(*nomeArquivo, *img);
}


/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S   DA  
 *                     A U X I L I A R E S 
 */

static void 
mostreUso (char *nomePrograma)
{
  fprintf(stderr,"%s: Uso \n"
	  "meu_prompt> %s <nome arq. entrada>\n"
	  "    <nome arq. entrada> = nome arq. Portable PixMap Binary.\n",
	  nomePrograma, nomePrograma);
  exit(EXIT_FAILURE);
}

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

  IMDB: utils.c


  Referencias: Com exceÃ§Ã£o das rotinas fornecidas no esqueleto e em sala
  de aula, caso voce tenha utilizado alguma referencia, liste-as abaixo
  para que o seu programa nao seja considerada plagio.

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

/* 
 * IMPLEMENTACAO de funcoes de uso geral 
 *
 */

/* interface para este modulo */
#include "utils.h" 

#include <stdio.h>     /* fgets(), printf() */
#include <stdlib.h>    /* malloc(), NULL, EXIT_FAILURE */
#include <string.h>    /* strlen() */
#include <ctype.h>     /* tolower() */

/* tamanho maximo de um string neste programa como nome de arquivo 
   ou nome um filme */
#define TAM_STR 256

#define DEBUG


/*----------------------------------------------------------------------
    achePalavra(pal,tPal,texto,tTex)

    Para achar um filme com nome contendo o "string" definido pelo usuÃ¡rio, 
    vocÃª deve implementar a funÃ§Ã£o achePalavra com o seguinte protÃ³tipo:

    A funcao recebe o string pal com tamanho tPal, e outro string texto 
    com tamanho tTex. A funÃ§Ã£o deve retornar TRUE caso a sequÃªncia pal 
    ocorra em texto, e FALSE em caso contrÃ¡rio. 

*/

Bool
achePalavra(unsigned char *pal, int tPal, unsigned char *texto, int tTex)
{
    int k, r;

    /* Seguinte algoritmo (trivial) compara de esquerda para direita*/
    for (k = 1; k <= tTex-tPal+1; k++)
    {
	/* Voltamos a comparar quando nao temos a palavra */
	r = 0;
	while (r < tPal && pal[1+r] == texto[k+r]) r ++;
        /* Se confirmada igual ate a ultima letra, retorna TRUE */
	if (r == tPal) return TRUE;
    }
    /* Nao foi encontrada a palavra */
    return FALSE;
}


/*----------------------------------------------------------------------
    strCmp(const char *s1, const char *s2)

    Comportamento identico ao da funcao strcmp da interface string.h
    da libC. A unica diferenca e que esta funcao desconsidera se as
    letras sao maiusculas ou mininusculas.

    Retirada de  gLibc

    Ver http://fossies.org/dox/glibc-2.18/strcmp_8c_source.html
    ou  a copia nas notas de aula de MAC0122
      
    ------------------------------------------------------------------
    NAME
       strcmp - compare two strings

    SYNOPSIS
       #include <string.h>

       int strcmp(const char *s1, const char *s2);

    DESCRIPTION
       The  strcmp() function compares the two strings s1 and s2.  
       It returns an integer less than, equal to, or greater than
       zero if s1 is found, respectively, to be less than, to match, 
       or be greater than s2.

*/

int  
strCmp(const char *s1, const char *s2)
{
    const unsigned char *p1 = (const unsigned char *) s1;
    const unsigned char *p2 = (const unsigned char *) s2;
    unsigned char c1, c2;
 
  do
  {
      c1 = tolower((unsigned char) *p1++); /* tolower foi acrescentado */ 
      c2 = tolower((unsigned char) *p2++); /* tolower foi acrescentado */
      if (c1 == '\0')
	  return c1 - c2;
  }
  while (c1 == c2);
 
  return c1 - c2;
}

/* 
  Sobre a glibc:

  Copyright (C) 1991-2013 Free Software Foundation, Inc.
  This file is part of the GNU C Library.
 
  The GNU C Library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
 
  The GNU C Library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.
 
  You should have received a copy of the GNU Lesser General Public
  License along with the GNU C Library; if not, see
  <http://www.gnu.org/licenses/>. 

*/



/*----------------------------------------------------------------------
    leiaString(s,size)

    Esta funcao le da entrada padrao no maximo size-1 caracteres
    e armazena em s. A leitura para depois de um ENTER e o ENTER 
    _nao_ e incluido no string s. 
    A funcao retorna o numero de caracteres no string.

    Pre-condicao: size <= TAM_STR

    > man fgets
    char *fgets(char *s, int size, FILE *stream);

    fgets() reads in at most one less than size characters from stream
    and stores them into the buffer pointed to by s.  Reading stops
    after an EOF or a newline.  If a newline is read, it is stored
    into the buffer.  A terminating null byte ('\0') is stored
    after the last character in the buffer.
*/

int 
leiaString(char str[], int size)
{
    int len;
    char s[TAM_STR];

    /* remove qualquer newline que estava no buffer */
    scanf(" ");

    /* leitura do string: ler info sobre fgets() */
    fgets(s, TAM_STR, stdin);

    /* sobreescreve  um possivel newline do final com '\0' */
    len = strlen(s); 
    if (s[len-1] == ENTER) 
    {
	len--;
	s[len] = '\0';

    }

    if (len > size)
    {
	s[size-1] = '\0';
	len = size-1;
    }
    strncpy(str, s, size);

#ifdef DEBUG
    printf("leiaString: string lido '%s' tem %d caracteres\n", s, len);
#endif
    return len;
}

/*---------------------------------------------------
    mallocSafe()

    http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
*/
void * 
mallocSafe(size_t n)
{
    void * p;

    p = malloc(n);
    if (p == NULL) 
    {
	printf("ERRO na alocacao de memoria.\n\n");
	exit(EXIT_FAILURE);
    }

    return p;
}


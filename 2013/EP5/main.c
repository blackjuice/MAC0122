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

  IMDB: main.c 


  Referencias: Com exceÃ§Ã£o das rotinas fornecidas no esqueleto e em sala
  de aula, caso voce tenha utilizado alguma referencia, liste-as abaixo
  para que o seu programa nao seja considerada plagio.
	- http://www.ime.usp.br/~pf/algoritmos/aulas/mrgsrt.html
	- http://en.wikipedia.org/wiki/Merge_sort
	- http://www.sorting-algorithms.com/
	- http://www.tutorialspoint.com/c_standard_library/c_function_tolower.htm
	- http://www.dailyfreecode.com/Code/doubly-circular-link-list-circular-2427.aspx
	- http://jlmedina123.wordpress.com/2013/04/20/doubly-circular-linked-list/
	- http://en.wikipedia.org/wiki/Linked_list
	- http://www.youtube.com/watch?v=9bX9WaIVyAg


  \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/


#include <stdio.h>  /* printf(), scanf() */ 
#include <time.h>   /* CLOCKS_PER_SECOND */

#include "main.h"

/* crieListaFilmes(), crieFilme(), inseraFilme(), acheFilme(), mergeSortFilmes() */
#include "filmes.h" 

/* carregueListaFilmes(), graveListaFilmes(), mostreFilme(), mostreListaFilmes() */
#include "iofilmes.h" 

#include "utils.h"    /* mallocSafe(), leiaString() */



/*------------------------------------------------------------------- 
  P R O T O T I P O S 
*/

/* A funcao leiaOpcao so e usada neste arquivo. */
static char  leiaOpcao(); 


/*------------------------------------------------------------------- 
    M A I N 
*/
int 
main(int argc, char *argv[])
{
    ListaFilmes *lst = crieListaFilmes(); 
    char         opcao;
    clock_t start, end; /* usadas para medir tempo de processamento */
    double elapsed;
    /* declaracao das demais variaveis do main */

    /*-------------------------------------*/
    /*-------------------------------------*/
    /*-------------------------------------*/
    /*-------------------------------------*/
    /*-------------------------------------*/

    char nomeF[TAM_STR+1];
    char letra;
    /* int nPal;  tamanho do nome a ser procurado  */
    Filme *p;

    /*-------------------------------------*/
    /*-------------------------------------*/
    /*-------------------------------------*/
    /*-------------------------------------*/
    /*-------------------------------------*/

    /*-----------------------------------------------------*/
    /* iterara ate o usuario digitar 'x' para sair         */
    do 
    { 

	opcao = leiaOpcao();

	/* comeca a cronometrar */
	start = clock(); 

	switch (opcao) 
	{
	    /*---------------------------------------------*/
	case CARREGAR:
	{
	    carregueListaFilmes(lst);
	    break;
	}  
	    /*---------------------------------------------*/
	case GRAVAR:
	{
	    graveListaFilmes(lst);
	    break;
	}

	    /*---------------------------------------------*/
	case PROCURAR:
	{
	    printf ("Digite parte do nome a ser procurado: ");
	    leiaString (nomeF, TAM_STR);

	    /* while inside flm contains the word, keep rolling */
	    /* for (p = lst->cab->prox; contemFilme(lst, p) != 0; p = p->prox) */
	    for (p = lst->cab->prox; p != lst->cab; p = p->prox)
	    {
		/* achamos um filme com o nome parecido, serah ele mesmo? */
		if (achePalavra ((unsigned char*)nomeF, (leiaString (nomeF, TAM_STR)), (unsigned char*)p->nome, TAM_STR) == 0)
		{
		    mostreFilme(p);
		    printf ("Esse eh o filme procurado? [s/n/x] (x para sair): ");
		    scanf ("%c", &letra);

		    if (letra == 's' || letra == 'x')
			break;
		}
	    }

	    /* NAO ACHAMOS O FILME DENTRO: */
	    if (letra != 's')
		printf ("\nFilme nao encontrado.\n");

	    break;
	}
	    /*---------------------------------------------*/
	case INSERIR:
	{
	    Filme *flm = NULL;      

	    char  dist[TAM_DIST+1];  
	    int   votos;             
	    float nota;              
	    char  nome[TAM_STR+1];   
	    int   ano;               

	    printf("Digite o nome do filme: ");
	    leiaString(nome, TAM_STR);

	    printf("Digite o ano: ");
	    scanf("%d", &ano);

	    printf("Digite a nota: ");
	    scanf("%f", &nota);

	    printf("Digite o numero de votos: "); 
	    scanf("%d", &votos);

	    printf("Digite a distribuicao: ");
	    leiaString(dist, TAM_DIST+1);
   
	    flm = crieFilme(dist, votos, nota, nome, ano);
	    mostreFilme(flm);
	    
	    /* completar essa opcao */
	    insiraFilme (lst, flm);
	    break;
	}

	    /*---------------------------------------------*/
	case REMOVER:
	{
	    printf ("Digite parte do nome a ser procurado: ");
	    leiaString (nomeF, TAM_STR);

	    for (p = lst->cab->prox; p != lst->cab; p = p->prox)
	    {
		/* achamos um filme com o nome parecido, serah ele mesmo? */
		if (achePalavra ((unsigned char*)nomeF, (leiaString (nomeF, TAM_STR)), (unsigned char*)p->nome, TAM_STR) == 0)
		{
		    mostreFilme(p);
		    printf ("Esse eh o filme procurado? [s/n/x] (x para sair): ");
		    scanf ("%c", &letra);

		    if (letra == 's' || letra == 'x')
			break;
		}
	    }

	    /* NAO ACHAMOS O FILME DENTRO: */
	    if (letra != 's')
	    {
		printf ("\nFilme nao encontrado.\n");
	        break;
	    }

	    else
		removaFilme (lst, p);

	    break;
	}

      	    /*---------------------------------------------*/
	case ORDENAR_NOTA_M:
	{
	    mergeSortFilmes (lst, NOTA);
	    break;
	}

      	    /*---------------------------------------------*/
	case ORDENAR_NOME_M:
	{
	    mergeSortFilmes (lst, NOME);
	    break;
	}

      	    /*---------------------------------------------*/
	case ORDENAR_NOTA_Q:
	{
	    quickSortFilmes (lst, NOTA);
	    break;
	}

      	    /*---------------------------------------------*/
	case ORDENAR_NOME_Q:
	{
	    quickSortFilmes (lst, NOME);
	    break;
	}

	    /*---------------------------------------------*/
	case MOSTRAR:
	{
	    mostreListaFilmes (lst);
	    break;
	}

	    /*---------------------------------------------*/
	case MOSTRAR_MENOR:
	{
	    mostreMelhoresFilmes (lst);
	    break;
	}

	    /*---------------------------------------------*/
	case MOSTRAR_MAIOR:
	{
	    mostrePioresFilmes (lst);
	    break;
	}
      
	    /*---------------------------------------------*/
	case LIMPAR:
	{
	    break;
	}

      	    /*---------------------------------------------*/
	case SAIR:
	{
	    break;
	}

	default :
	{
	    printf("main: opcao '%c' nao reconhecida\n", opcao);
	    break;
	}
	
	} /* switch */
	
	/* trava o cronometro */  
	end = clock();
	
	/* calcula o tempo */
	elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\n(%g segundos)\n", elapsed);
    } 
    while (opcao != SAIR);


    return 0;
}


/*---------------------------------------------------------------------
  leiaOpcao()
   
  Le e retorna o caractere correspondente a opcao do usuario.
*/

char 
leiaOpcao()
{
    char opcao;

    printf(
	"\n================================================"
	"======================\n"
	"  (c) carregar um arquivo de dados\n"
	"  (g) gravar a lista atual em um arquivo\n"
	"  (p) procurar a nota de um filme\n"
	"  (i) inserir um filme\n"
	"  (r) remover um filme\n"
	"  (o) ordenar a lista de filmes por nota (mergeSort)\n"
	"  (O) ordenar a lista de filmes por nome (mergeSort)\n"
	"  (q) ordenar a lista de filmes por nota (quickSort, opcional)\n"
	"  (Q) ordenar a lista de filmes por nome (quickSort, opcional)\n"
	"  (m) mostrar todos os filmes\n"
	);

    printf(
	"  (<) mostrar N filmes com nota _menor_ que X e pelo menos V votos\n"
	"  (>) mostrar N filmes com nota _maior_ que X e pelo menos V votos\n"
	"  (l) limpar a lista de filmes\n"
	"  (x) sair do programa\n\n"
	);
    printf("Digite uma opcao: ");
    scanf(" %c", &opcao);

  /* main.c: warning: string length â€˜679â€™ is greater than the length 
     â€˜509â€™ ISO C90 compilers are required to support 
     [-Woverlength-strings] */

    return opcao;
}


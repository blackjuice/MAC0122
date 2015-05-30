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

  IMDB: iofilmes.c


  Referencias: Com exceÃ§Ã£o das rotinas fornecidas no esqueleto e em sala
  de aula, caso voce tenha utilizado alguma referencia, liste-as abaixo
  para que o seu programa nao seja considerada plagio.

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

/*--------------------------------------------------------------------*/
/* Interface para sa funcoes neste modulo                             */
#include "iofilmes.h"

#include <stdlib.h>   /* exit() */
#include <stdio.h>
#include <string.h>   /* strspn(), strncpy() */
#include <ctype.h>    /* isdigit() */

#include "filmes.h"


/* maior linha dos arquivos de entrada tem uns 240 caracteres */
#define TAM_LINHA  256 

/* imprime uma linha com tracos */
#define LINHA  printf("------------------------------------------"\
                      "--------------------------------------\n")

/* funcoes rIndex e erroLeitura sao usadas apenas neste arquivo */
static char *rIndex(char *pal, char letra); 

static void  erroLeitura(char *msg, char *lin);

/*----------------------------------------------------------------------
    carregueListaFilmes(lst)

    Faz a leitura da entrada padrao do nome um um arquivo que contem
    dados sobre filmes. Os dados devem estar no formato 
    utilizado pelo IMDB. Esses dados sao lidos e para cada filme
    e criada uma estrutura Filme. Ess essa estrutura e inserida na 
    lista de filmes representada pelo parametro lst.

    Author: Carlos Hitoshi Morimoto    
*/

void
carregueListaFilmes(ListaFilmes *lst)
{
    FILE  *arq;
    char   nomeArq[TAM_STR];  /* inclui  o '\0' */

    Filme *flm = NULL;

    char   linha[TAM_LINHA]; /* inclui o  '\0' */
    char  *pLinha, *qLinha;

    char   dist [TAM_DIST+1]; /* +1 para o '\0' */
    int    votos;
    char   nome [TAM_STR];   /* inclui  o '\0' */
    int    ano;
    float  nota;

    int   nLinhas = 0;    /* no. de linhas do arquivo */
    int   nIgnoradas = 0; /* no. de linhas ignoradas */
    int   nErroVotosNota = 0; /* no. de filmes com erro em votos ou nota */
    int   nErroAno = 0; /* no. de filmes com erro no ano */
    int   nAnoIgnorado = 0; /* no. ano ignorado */
    int   nFilmes = 0;    /* no. de filmes inseridos na lista */
    int   nFilmesRepetidos = 0; /* no. de filmes repetidos */

    if (lst == NULL)
    {
	AVISO(carregueListaFilmes: NULL recebido como parametro (lst));
	return;
    }

    printf("carregueLista: Digite o nome do arquivo: ");
    fgets(nomeArq, TAM_STR, stdin);

    scanf(" %s", nomeArq);
    printf("carregueLista: Nome do arquivo de entrada: '%s'\n", nomeArq);

    if ((arq=fopen(nomeArq, "r")) == NULL) 
    {
	printf("carregueLista: arquivo '%s' nao encontrado\n\n", nomeArq);
	/* exit(-1); */
	return; /* retorna a mesma lista */
    }

    while (fgets(linha, TAM_LINHA, arq)) 
    {
	/* numero de linhas do arquivo */
	nLinhas++;

	/* apontador para linha */
	pLinha = linha; 
	
	/* Verifique se a linha contem um filme.  
	   Para conter um filme a linha deve
               - comeÃ§ar com 6 espaÃ§os e
	       - ter um digito ou ponto na setima posicao 
	*/
	
	if (strspn(linha, " ") != 6 || 
	    !(linha[6] == '.' || isdigit(linha[6])))  /* distribuicao */ 
	{
	    nIgnoradas++;
	    continue;
	} 

	pLinha += 6; /* pula brancos */

	/*-------------------------------------------------*/
	/* 1 pegue a distribuicao de notas                 */
		
	/* distribuicao, 10 caracteres */
	strncpy(dist, pLinha, 10);
	dist[10] = '\0';
	pLinha += 10; /* pula distribuicao */

	/*-------------------------------------------------*/
	/* 2 pegue o numero de votos e nota                */
	    
	/* votos e nota, ocupam 16 posiÃ§Ãµes */
	if (sscanf(pLinha, "%d %f", &votos, &nota) != 2) 
	{
	    erroLeitura("votos ou nota invalidos", linha);
	    nErroVotosNota++;
	    continue;
	}
	pLinha += 16; /* pula votos e nota */
	    
	/*-------------------------------------------------*/
	/* 3 pegue o ano                                   */

	/* pula brancos e tabs */
	while (*pLinha == ' ' || *pLinha == '\t') pLinha++;
	    
	/* encontra ultimo '{' e joga comentarios fora */
	qLinha = rIndex(pLinha, '{');
	if (qLinha != NULL) *qLinha = '\0'; 
	    
	/* procura o ano no que sobrou da linha */
	qLinha = rIndex(pLinha, '(');
	if (qLinha == NULL) 
	{
	    erroLeitura("ano ausente", linha);
            nErroAno++;
	    continue;
	}
	    
	/* nao eh ano: eh (mini), (TV) ou (V) */
	if (!isdigit(qLinha[1]) && qLinha[1] !=  '?') 
	{
	    *qLinha = '\0';	/* joga fora */
		
	    /* pegue o parenteses anterior */
	    qLinha = rIndex(pLinha, '(');   
	    if (qLinha == NULL) 
	    {
		erroLeitura("ano ausente", linha);
		nErroAno++;
		continue;
	    }
	}
	/* pula o parenteses */
	qLinha++;
	    
	if (sscanf(qLinha, "%d", &ano) != 1) {
	    /* pode ser ano ignorado */
	    if (strspn(qLinha, "?") == 4)
	    {
		ano = 9999;
		nAnoIgnorado++;
	    }
	    else 
	    {
		erroLeitura("ano invalido", linha);
		nErroAno++;
		continue;
	    }
	}
	    
	/* joga fora pedaco final da linha com o ano */
	qLinha[-2] = '\0'; 
	    
	    
	/*-------------------------------------------------*/
	/* 3 pegue o nome                                  */

	/* O que sobra eh o nome */
	strncpy(nome, pLinha, TAM_STR);
	nome[TAM_STR-1] = '\0';

	/*-------------------------------------------------*/
	/* 4 se chegamos aqui tudo esta ok e ja temos      */
	/*   todos os dados sobre o filme                  */
	/*   crie uma estrutura para o filme e insira na   */
	/*   lista de filmes                               */

	flm = crieFilme(dist, votos, nota, nome, ano);
	
	if (contemFilme(lst, flm))
	{
	    nFilmesRepetidos++;
	    free(flm);
	}
	else
	{
	    insiraFilme(lst, flm);
	    nFilmes++;
	}

	/* para indicar o progresso da leitura */
	if (nFilmes % 1024 == 0)  
	{
	    /* indicador de progresso */
	    printf(".");     
		
	    /* imprime o '.' sem esperar que a linha toda fique pronta */
	    fflush(stdout);  
	}
    }

    fclose(arq);
    LINHA;
    printf("carregueFilme: relatorio da leitura do arquivo '%s'\n"
           "   no. linhas = %d\n"
           "   no. linhas ignoradas = %d\n"
	   "   no. erros em votos ou nota = %d\n"
	   "   no. erros no ano = %d\n"
	   "   no. anos ignorados = %d\n"
	   "   no. filmes repetidos = %d\n"
	   "   no. filmes inseridos na lista = %d\n"
	   "   no. filmes na lista = %d\n",
	   nomeArq,
	   nLinhas, nIgnoradas, nErroVotosNota, nErroAno, 
	   nAnoIgnorado,  nFilmesRepetidos, nFilmes,
	   lst->nFilmes);
    printf("carregueFilmes: leitura concluida\n");
    LINHA;
}

/*----------------------------------------------------------------------
    graveListaFilmes(lst) 

    Recebe um ponteiro lst para uma estrutura que representa uma lista 
    de filmes.

    A funcao le o nome de um arquivo da estrada padrao e grava a 
    lista de filmes em um arquivo com esse nome de acordo com o 
    formato do IMDB;

        - 6     espacos
        - %s    dist  (string com 10 caracteres)
        - %7d   votos 
        - %7.1  nota  
        - %s    nome
        - (%d)  ano

    Exemplo:

          0.0.003003      29   7.0  Always a Bridesmaid (2000)
    ....*....*....*....*....*....*....*....*....*....*....*....*
*/

void 
graveListaFilmes(ListaFilmes *lst) 
{
    FILE *arq;
    char nomeArq[TAM_STR];
    Filme *flm;

    if (lst == NULL)
    {
	AVISO(graveListaFilmes: NULL recebido como parametro);
	return;
    }

    printf("graveLista: digite o nome do arquivo: ");
    leiaString(nomeArq, TAM_STR);

    printf("graveLista: nome do arquivo de saida: '%s'\n", nomeArq);
    if ((arq = fopen(nomeArq, "w")) == NULL) 
    {
	fprintf(stderr,
		"graveLista: ERRO nao foi possivel criar o arquivo '%s'.\n\n", 
		nomeArq);
	return; 
    }
  
    for (flm = lst->cab->prox; flm != lst->cab; flm = flm->prox)
    {
	fprintf(arq, "      %s %7d %7.1f\t%s\t(%d)\n", 
		flm->dist, 
		flm->votos, 
		flm->nota, 
		flm->nome, 
		flm->ano);
    }
    
    fclose(arq);
    return;

}

/*----------------------------------------------------------------------
    rIndex(pal, letra)

    Recebe um string pal e um caractere letra e retorna
    o endereco do ultimo caractere de pal que eh igual a letra. 

    Retorna NULL pal nao contem o caractere letra

*/

static char *
rIndex(char *pal, char letra) 
{
    int index;
     
    index = strlen(pal);
    while (index > 0) {
	index--;
	if (pal[index] == letra)
	    return &pal[index];
    }

    return NULL;
}

/*----------------------------------------------------------------------
    erroLeitura(msg,lin)

    Imprime a mensagem de erro msg referente a algum problema na
    leitura da linha lin de um arquivo que contem filmes no 
    formato IMDB.
*/

static void 
erroLeitura(char *msg, char *lin)
{
    fprintf(stderr, 
	    "\ncarregueListaFilmes: entrada invalida ignorada (%s):\n\t%s\n", 
	    msg, lin);
}



/*----------------------------------------------------------------------
    mostreFilme(flm)

    Imprime as informacoes sobre o filme flm.

*/

void 
mostreFilme(Filme *flm)
{
    if (flm == NULL) 
    {
	AVISO(mostreFilme: NULL recebido como parametro);
	return;
    }

    LINHA;
    printf("%s (ano %d):\n"
	   "\t nota %4.1f "
	   "\t %6d votos "
	   "\t distribuicao [%s] \n",
	   flm->nome, flm->ano, flm->nota, flm->votos, flm->dist);

}


/*----------------------------------------------------------------------
    mostreListaFilmes(lst)

    Mostra as informacoes de todos os filmes na lista de filmes lst.

*/

void 
mostreListaFilmes(ListaFilmes *lst)
{
    Filme *p;

    if (lst->nFilmes == 0)
	printf ("AVISO: mostreListaFilmes: lista de filmes vazia");

    else 
    /* percorremos a lista */
	for (p = lst->cab->prox; p != lst->cab; p = p->prox)
	    mostreFilme(p);

}

/*----------------------------------------------------------------------
    mostreMelhoresFilmes(lst)

    Le da entrada padrao 

        - um numero N de filmes, 
        - uma nota maxima X e 
        - um numero minimo V de votos. 

    Imprime os N melhores filmes da lista lst com nota menor que 
    a nota maxima X e com pelo menos o numero minimo de votos V. 

    Pre-condicao: a funcao supoe que a lista de filmes esta em
                  ordem crescente de nota.
*/

void 
mostreMelhoresFilmes(ListaFilmes *lst)
{
    int numFlm, maxX, minV;
    int cont = 0;
    Filme *p;

    /* leitura entrada padrao */
    printf ("Qual o numero de filmes a serem mostrado: "); 
    scanf ("%d", &numFlm);
    printf ("Qual a nota maxima: "); 
    scanf ("%d", &maxX);
    printf ("Qual o numero minimo de votos: "); 
    scanf ("%d", &minV);

    for (p = lst->cab; p->nota <= maxX; p = p->prox)
	if (p->votos >= minV)
	{
	    cont++;
	    mostreFilme (p);
	}
    printf ("Esses sao os %d melhores filmes com nota " 
            "menor que %d e pelo menos %d votos.", cont, maxX, minV);
}

/*----------------------------------------------------------------------
    mostrePioresFilmes(lst)

    Le da entrada padrao 

        - um  numero N de filmes, 
        - uma nota minima X e 
        - um  numero minimo V de votos. 

    Imprime os N piores filmes da lista lst com nota maior que 
    a nota minima X e como pelo menos o numero minimo V de votos. 

    Pre-condicao: a funcao supoe que a lista de filmes esta em
                  ordem crescente de nota.

*/
void 
mostrePioresFilmes(ListaFilmes *lst)
{
    Filme *p;
    int numFlm, minX, minV;
    int cont = 0;

    /* leitura entrada padrao */
    printf ("Qual o numero de filmes a serem mostrado: "); 
    scanf ("%d", &numFlm);
    printf ("Qual a nota minima: "); 
    scanf ("%d", &minX);
    printf ("Qual o numero minimo de votos: "); 
    scanf ("%d", &minV);

    for (p = lst->cab; p->nota >= minX; p = p->prox)
	if (p->votos >= minV)
	{
	    cont++;
	    mostreFilme (p);
	}
     printf ("Esses sao os %d piores filmes com nota " 
             "maior que %d e pelo menos %d votos.", cont, minX, minV);
}

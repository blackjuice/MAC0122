/*****************************************************************/
/**                                                           	**/
/**   Lucas Sung Jun Hong		8124329			**/
/**   EXERCICIO-PROGRAMA 01					**/
/**								**/
/*****************************************************************/

#include <stdio.h>  /* scanf, printf,  ... */
#include <stdlib.h> /* srand, rand,    ... */
#include <string.h> /* strlen, strcmp, ... */  

/***************************CONSTANTES****************************/

/* tamanho maximo de um turtledorm */
#define MAX      128 

#define ACORDADO  '#'
#define DORMINDO  ' '
#define TAPINHA   'T'

#define TRUE  1
#define FALSE 0

#define ENTER  '\n'
#define FIM    '\0'
#define ESPACO ' '

/**************************PROTOTIPOS****************************/

/* PARTE I */

void	leiaTurtledorm		(int *n, int tdorm[MAX][MAX]);

void 	mostreTurtledorm	(int n, int tdorm[][MAX], char c);

void	atualizeTurtledorm	(int n, int tdorm[][MAX], int lin, int col);

int 	todosDormindo		(int n, int tdorm[][MAX]);

int	graveTurtledorm		(int n, int tdorm[][MAX]);

/* PARTE II */

void	sorteieTurtledorm	(int *n, int tdorm[][MAX]);

/* PARTE III */

void	resolvaTurtledorm	(int n, int tdorm[][MAX]);

/* FUNCOES AUXILIARES */
int 	randomInteger		(int low, int high);

/*****************************MAIN*******************************/

int main (int argc, char *argv[])
{
	char c;		/* para dar sortear ou ler arquivo */
	char cl;	/* para desistir, gravar, ou pedir ajuda */
	char ct;	/* para impressao do tabuleiro com '#' ou 'T' */

	int i, j;
	int lin, col;
	int fim;	/* indica se jogo foi completo ou nao */
	int x;		/* guarda entrada no inicio do jogo */
	int n;		/* tamanho do tdorm */
	int nplay = 0;	/* contagem de jogadas */

	int tdorm[MAX][MAX];

	printf ("(s)ortear ou (l)er turtledorm de arquivo: ");
	scanf ("%c", &c);

	/*para ler turtledorm*/
	if (c == 'l') 
	{
		leiaTurtledorm (&n , tdorm);
		printf ("Turtledorm inicial\n");

		ct = ACORDADO;
		mostreTurtledorm (n, tdorm, ct);

		printf ("Uma jogada definida por numeros inteiros entre 1 e %d\n", n);
	}
	
	/*para sortear turtledorm*/
	if (c == 's')
	{
		printf ("Digite tamanho do turtledorm: ");
		scanf ("%d", &n);

		/* Zeramos todas as casas do turtledorm */
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				tdorm [i][j] = 0;

		sorteieTurtledorm (&n, tdorm);
		ct = ACORDADO;
		mostreTurtledorm (n, tdorm, ct);

		printf ("Uma jogada definida por numeros inteiros entre 1 e %d\n", n - 1);
	}

	/* inicio do jogo. O loop tera fim somente se for 
	 * resolvido o tabuleiro, ou em caso de desistencia do usuario
	 */
	fim = FALSE;
	while (fim != TRUE)
	{
		printf ("\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n"
			"Digite 'd' para (d)esistir esta partida;\n"
			"Digite 'a' para solicitar (a)juda para uma solucao;\n"
			"Digite 'g' para (g)ravar turtledorm atual em um arquivo;\n"
			"Especifique uma posicao (linha e coluna) para 'dar tapinha.'\n"
			">>> ");

		/* x devolve 0 se entrada for caracter ou valor != 0, caso contrario */
		x = scanf ("%d", &lin);

		/* tarefas executadas quando um caracter for escolhido */
		if (x == 0)
		{
			scanf ("%c", &cl);

			if (cl == 'g')
			{
				i = graveTurtledorm (n, tdorm);
				if (i == 0)
					printf ("\n**Jogo salvo com sucesso**\n");
				else 	printf ("Erro ao salvar o jogo\n");
			}

			if (cl == 'd')
			{
				printf ("\nVoce acaba de desistir da sua tarefa de guardiao apos %d jogadas...\n", nplay);
				break;
			}

			if (cl == 'a')
				resolvaTurtledorm (n, tdorm);
		}

		/* tarefas executadas quando posicao for escolhida */
		else
		{
			scanf ("%d", &col);
			nplay++;
			printf ("A jogada %d foi escolhida em (%d, %d)\n", nplay, lin, col);
			lin--; col--;

			atualizeTurtledorm (n, tdorm, lin, col);
			fim = todosDormindo (n, tdorm);
			
			printf ("\n\n*Turtledorm apos a jogada %d*\n", nplay);

			mostreTurtledorm (n, tdorm, ct);

			/*se fim tem valor 1, o jogo foi concluido e termina programa */
			if (fim == TRUE)
			{
				printf ("\nTodos os turtles agora dormem tranquilamente apos %d jogadas.\nBom trabalho!\n\n", nplay);
				break;
			}	
		}
	}

	return EXIT_SUCCESS;
}

/*---------------------------------------------------------------*/
/*		IMPLEMENTACAO DAS FUNCOES DA PARTE I		 */

/* funcao imprime a configuracao do tabuleiro, preenchendo com '#' (em casos de turtle acordado)
 * e ' ' (turtle dormindo). Observe que depende do parametro "(char) c". Se c == TAPINHA,
 * imprimira um 'T' no lugar do '#', em que mostra posicao que resolve turtledorm.
 */
void mostreTurtledorm (int n, int tdorm[][MAX], char c)
{
	int i, j;
	int t, r = 1;

	printf ("     |");
	for (t = 1; t <= n; t++)
		printf ("  %d  |", t);
	printf ("\n");

	for (t = 0; t <= n; t++)
		printf ("-----+");
	printf ("\n");

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (j == 0) {
				printf ("  %d  |", r);
				r++;
			}

			if (c == ACORDADO)
			{
				if (tdorm[i][j] == 1)	printf ("  #  |");
				else			printf ("     |");
			}

			if (c == TAPINHA)
			{
				if (tdorm[i][j] == 1)	printf ("  T  |");
				else			printf ("     |");
			}
		}
		printf ("\n");

		for (t = 0; t <= n; t++)
			printf ("-----+");
		printf ("\n");
	}
}

/* funcao solicita o nome do arquivo que contem turtledorm
 * e obtem n e a matriz tdorm
 */
void leiaTurtledorm (int *n ,int tdorm[MAX][MAX])
{
	FILE *file;
	char arq[MAX];
	int i, j;

	printf ("Digite o nome do arquivo: ");
	scanf ("%s", arq);
	file = fopen (arq, "r");

	fscanf (file, "%d", &*n);

	for (i = 0; i < *n; i++)
		for (j = 0; j < *n; j++)
			fscanf (file, "%d", &tdorm[i][j]);

	fclose (file);
}

/* funcao solicita nome do novo arquivo a ser gravado e retorna EXIT_SUCCESS 
 * se operacao foi completa ou EXIT_FAILURE caso contrario
 */
int graveTurtledorm (int n, int tdorm[][MAX])
{
	FILE *file;
	char arq[MAX];
	int i, j;

	printf ("\nDigite o nome do novo arquivo: ");
	scanf ("%s", arq);
	file = fopen (arq, "w");
	fprintf (file, "%d\n", n);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			fprintf (file, "%d ", tdorm[i][j]);
		fprintf (file, "\n");
	}

	if (file == NULL)
	{
		fclose(file);
		return EXIT_FAILURE;
	}

	fclose(file);
	return EXIT_SUCCESS;
}

/* funcao verifica se cada casa contem 0, retornando TRUE
 * ou FALSE, caso contrario
*/
int todosDormindo (int n, int tdorm[][MAX])
{
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (tdorm[i][j] != 0)
				return FALSE;
	return TRUE;
}

/* funcao troca de 0 para 1 ou vice-versa na casa escolhida pelo usuario
 * alem das casas que se encontram encostadas a ela.
 */
void atualizeTurtledorm	(int n, int tdorm[][MAX], int lin, int col)
{
	if (tdorm[lin][col] == 1)
		tdorm[lin][col] = 0;
	else 	tdorm[lin][col] = 1;
	if (lin > 0)
	{
		if (tdorm[lin - 1][col] == 1)
			tdorm[lin - 1][col] = 0;
		else 	tdorm[lin - 1][col] = 1;
	}
	if (col > 0)
	{
		if (tdorm[lin][col - 1] == 1)
			tdorm[lin][col - 1] = 0;
		else 	tdorm[lin][col - 1] = 1;
	}
	if (lin < n - 1)
	{
		if (tdorm[lin + 1][col] == 1)
			tdorm[lin + 1][col] = 0;
		else 	tdorm[lin + 1][col] = 1;
	}
	if (col < n - 1)
	{
		if (tdorm[lin][col + 1] == 1)
			tdorm[lin][col + 1] = 0;
		else 	tdorm[lin][col + 1] = 1;
	}
}

/*---------------------------------------------------------------*/
/*		IMPLEMENTACAO DAS FUNCOES DA PARTE II		 */

/* funcao recebe semente e o nivel de dificuldade
 * e sorteia um x numero de tapinhas segundo o intervalo de dificuldade
 * modifica a matriz tdorm antes nula e imprime numero de turtles despertos.
 */
void sorteieTurtledorm (int *n, int tdorm[][MAX])
{
	int i, j;
	int lin, col;
	int cont = 0;		/* contagem de turtles despertos */

	int seed;

	char difficulty;

	int lowFacil;
	int highFacil;
	int facil;

	int lowMedio;
	int highMedio;
	int medio;

	int lowDificil;
	int highDificil;
	int dificil;

	/* intervalo para o nivel de dificuldade facil */
	lowFacil   = 0.05*(*n)*(*n);
	highFacil  = 0.20*(*n)*(*n);

	/* intervalo para o nivel de dificuldade medio */
	lowMedio   = 0.25*(*n)*(*n);
	highMedio  = 0.50*(*n)*(*n);

	/* intervalo para o nivel de dificuldade dificil */
	lowDificil  = 0.55*(*n)*(*n);
	highDificil = 0.85*(*n)*(*n);

	printf ("\nDigite um inteiro (semente): ");
	scanf ("%d", &seed);

	printf ("Escolha o nivel de dificuldade [f/m/d]: ");
	scanf (" %c", &difficulty);

	if (difficulty == 'f')
	{
		srand(seed);
		facil   = randomInteger(lowFacil  , highFacil);
		printf ("\nNumero de tapinhas sorteado: %5d\n", facil);

		for (i = 0; i < facil; i++)
		{
			/* ideia retirada de http://www.cplusplus.com/ */
			lin = 1 + ( rand()%(*n) ); lin--;
			col = 1 + ( rand()%(*n) ); col--;

			atualizeTurtledorm (*n, tdorm, lin, col);
		}		
	}

	if (difficulty == 'm')
	{
		srand(seed);
		medio   = randomInteger(lowMedio  , highMedio);
		printf ("\nNumero de tapinhas sorteado: %5d\n", medio);

		for (i = 0; i < medio; i++)
		{
			/* ideia retirada de http://www.cplusplus.com/ */
			lin = 1 + ( rand()%(*n) ); lin--;
			col = 1 + ( rand()%(*n) ); col--;

			atualizeTurtledorm (*n, tdorm, lin, col);
		}
	}

	if (difficulty == 'd')
	{
		srand(seed);
		dificil = randomInteger(lowDificil, highDificil);
		printf ("\nNumero de tapinhas sorteado: %5d\n", dificil);

		for (i = 0; i < dificil; i++)
		{
			/* ideia retirada de http://www.cplusplus.com/ */
			lin = 1 + ( rand()%(*n) ); lin--;
			col = 1 + ( rand()%(*n) ); col--;

			atualizeTurtledorm (*n, tdorm, lin, col);
		}
	}

	for (i = 0; i < *n; i++)
		for (j = 0; j < *n; j++)
			if (tdorm[i][j] == 1)
				cont++;

	printf ("Numero de turtles despertos: %5d\n\n", cont);


}

/*---------------------------------------------------------------*/
/*		IMPLEMENTACAO DAS FUNCOES DA PARTE III		 */

/* Por favor, leia:
 *	A funcao resolvaTurtledorm NAO apresenta solucao otima para o jogo devida a falta
 *	de logica algebrica. Foi usado um metodo de "chute", ideia retirada do site:
 *	http://www.hamusutaa.com/pilot/solution.html/
 *
 *	Ela funciona da seguinte forma:
 *		1- observa-se a primeira linha, da direita para a esquerda;
 *		2- acorda-se o turtle logo abaixo da casa que se encontra "acessa" na primeira linha;
 *		3- o processo se repete ate a modificacao da ultima linha
 *
 *	As posicoes das Tapinhas para resolver o tabuleiro modificam-se a cada tapinha realizada.
 *	Ou seja, a cada 'ajuda' solicitada, a funcao indica uma tapa diferente da anterior.
 *
 *	Cada tapinha necessaria foi contada e sua devida posicao guardada na matriz position,
 *	de tamanho [numero de tapinhas][2]. Como uma tabela, que guarda coordenadas.
 */
void resolvaTurtledorm (int n, int tdorm[][MAX])
{
	int i, j;
	int M[MAX][MAX];
	int position[MAX*MAX][2];
	int x = 0;
	char c = TAPINHA;
	int cont = 0;

	/* para evitar modificacao da tdorm, copiamos ela em M[][] */
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			M[i][j] = tdorm[i][j];

	/* Daremos a tapinha na casa abaixo de uma acessa */
	for (i = 0; i < n - 1; i++)
		for (j = n - 1; j >= 0; j--)
			if (M[i][j] == 1)
			{
				position[x][0] = i+1;
				position[x][1] = j; x++;
				atualizeTurtledorm (n, M, i+1, j);
				cont++;
			}

	printf ("Numero de jogadas para uma solucao: %d\n", cont);

	/* zerando a matriz M */
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			M[i][j] = 0;

	/* foi guardada cada posicao com a tapinha necessaria na matriz position */
	for (i = 0; i < cont; i++)
		M[ position[i][0] ][ position[i][1] ] = 1;

	mostreTurtledorm (n, M, c);
}

/*---------------------------------------------------------------*/
/*		IMPLEMENTACAO DAS FUNCOES DAS AUXILIARES	 */

/* devolve um inteiro aleatorio no intervalo fechado: [low..high]
 * Codigo copiado da biblioteca random de Eric Roberts
 * e comentario retirado do esqueleto randomInteger.c
 */

int randomInteger (int low, int high)
{
	int k;
	double d;

	d = (double) rand( ) / ((double) RAND_MAX + 1);
	k = d * (high - low + 1);

	return low + k;
}

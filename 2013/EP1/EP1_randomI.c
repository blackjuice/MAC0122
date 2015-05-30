#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int 
randomInteger(int low, int high);

void
mostreUso(char *nomePrograma);

int 
main(int argc, char *argv[])
{
  char *nomePrograma = argv[0]+2; /* +2 para nao aparecer o ./ */

  /* inicializacao com valores default */
  int n       = 3;     /* ordem da matriz: a dimensao default e 3x3 */
  int r       = 1;     /* numero de repeticoes */

  int semente;         /* semente para o gerador de numeros aleatorios */

  int lowFacil;        /* valor low  para randomInteger nivel facil */
  int highFacil;       /* valor high para randomInteger nivel facil */
  int facil;           /* para o sorteio randomInteger(lowFacil,highFacil) */

  int lowMedio;        /* valor low  para randomInteger nivel medio */
  int highMedio;       /* valor high para randomInteger nivel medio */
  int medio;           /* para o sorteio randomInteger(lowMedio,highMedio) */
  
  int lowDificil;      /* valor low  para randomInteger nivel dificil */
  int highDificil;     /* valor high para randomInteger nivel dificil */
  int dificil;         /* para o sorteio randomInteger(lowDificil,highDifici) */ 

  int i;

  printf("Programa para testar a funcao randInteger(low,high)\n");
 
  /* se executado sem opcao alguma mostre como usar o programa */
  if (argc == 1) mostreUso(nomePrograma);

  /* pegue as opcoes da linha de comando */
  while (--argc) 
    {
      if (sscanf(argv[argc], "-n%d", &n) == 1) ;
      else if (sscanf(argv[argc], "-r%d", &r) == 1) ;
      else 
	{ /* opcao invalida */
	  fprintf(stderr, "%s: opcao invalida '%s'\n", nomePrograma, argv[argc]); 
	  mostreUso(argv[0]); 
	}	
    }

  printf("RAND_MAX = %d\n", RAND_MAX);
  printf("INT_MAX  = %d\n", INT_MAX);

  printf("n = %d\n", n);
  printf("r = %d\n", r);
  
  /* intervalo para o nivel de dificuldade facil */
  lowFacil   = 0.05*n*n;
  highFacil  = 0.20*n*n;
  printf("Intervalo nivel facil  : de %d a %d\n", lowFacil, highFacil);
  
  /* intervalo para o nivel de dificuldade medio */
  lowMedio   = 0.25*n*n;
  highMedio  = 0.50*n*n;
  printf("Intervalo nivel medio  : de %d a %d\n", lowMedio, highMedio);

  /* intervalo para o nivel de dificuldade dificil */
  lowDificil  = 0.55*n*n;
  highDificil = 0.85*n*n;
  printf("Intervalo nivel dificil: de %d a %d\n\n", lowDificil, highDificil);


  for (i = 0; i < r; i++)
    {
      /* leia a semente */
      printf("Digite uma semente: ");
      scanf("%d", &semente);
      printf("  semente = %10d\n", semente);

      srand(semente);
      facil   = randomInteger(lowFacil  , highFacil);
      printf("  facil   = %10d\n", facil);

      srand(semente);
      medio   = randomInteger(lowMedio  , highMedio);
      printf("  medio   = %10d\n", medio);

      srand(semente);
      dificil = randomInteger(lowDificil, highDificil);
      printf("  dificil = %10d\n\n", dificil);
    }

  return EXIT_SUCCESS;
}

/*
// A funÃ§Ã£o RandomInteger devolve um inteiro 
// aleatÃ³rio entre low e high inclusive,
// ou seja, no intervalo fechado low..high.
// Vamos supor que 0 <= low <= high < INT_MAX.
// O cÃ³digo foi copiado da biblioteca random 
// de Eric Roberts.
*/
int 
randomInteger( int low, int high)
{
    int k;
    double d;
    d = (double) rand( ) / ((double) RAND_MAX + 1);
    k = d * (high - low + 1);
    return low + k;
}


/* Mostra o uso e abandona o programa */
void 
mostreUso(char *nomePrograma)
{
  printf("%s: uso: %s [-s<numero> | -n<numero>]\n"
         "    -n<numero> ordem da matriz de tapinhas\n"
	 "    -r<numero> numero de experimentos\n"
         "    Exemplo de uso: %s -s9001 -n6\n",
	 nomePrograma, nomePrograma, nomePrograma);
 
  exit(0);
}

/*	RECURSION	MAXIMUM # IN ARRAY	*/

#include <stdio.h>
#define MAX 100
/*Recursion function*/
int max (int n, int v[MAX])
{
   int g;
   /* when there is only one element inside array */
   if (n == 1)
	return v[0];
   /* otherwise, compare biggest element with the last one */
   g = max (n - 1 , v);
   if (v[n - 1] < g)
	return g;
   /* return if v[n - 1] is actually the highest value */
   return v[n - 1];
}

int min (int n, int v[MAX])
{
  int b;
  /* when there is only one # */
  if (n == 1)
	return v[0];
  /* comparison */
  b = min (n -1, v);
  if (v[n -1] > b)
	return b;
  return v[n - 1];
}

int main ()
{
   int n , v[MAX];
   int i;

   /* capturing the elements */
   printf ("n>0 = ");
   scanf ("%d" , &n);
   for (i = 0 ; i < n ; i++)
	scanf ("%d" , &v[i]);

   printf ("Maximum # in array : %d\n", max (n, v));
   printf ("Minimum # in array : %d\n", min (n, v));
}


/*

	RECURSION	MAXIMUM # IN ARRAY	

#include <stdio.h>
#define MAX 100
	
int max (int n , int v[MAX])
{
   int g;
   /* when there is only one element inside array 
   if (n == 1)
	return v[0];
   /* otherwise, compare biggest element with the last one 
   g = max (n - 1 , v);
   if (v[n - 1] < g)
	return g;
   /* return if v[n - 1] is actually the highest value 
   return v[n - 1];
}

int main ()
{
   int n , v[MAX];
   int i;

   /* capturing the elements 
   printf ("n>0 = ");
   scanf ("%d" , &n);
   for (i = 0 ; i < n ; i++)
	scanf ("%d" , &v[i]);

   printf ("Maximum # in array : %d\n", max (n, v)); 
}

*/

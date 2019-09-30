// ***
// *** You MUST modify this file
// ***

#include "josephus.h"
#include <stdio.h>
#include <stdbool.h>

#ifdef TEST_JOSEPHUS
// 100% of the score
void eliminate(int n, int k)
{
  // allocate an arry of n elements
  int * arr = malloc(sizeof(* arr) * n);
  // check whether memory allocation succeeds.
  // if allocation fails,
  if (arr == NULL)
    {
      fprintf(stderr, "malloc fail\n");
      return;
    }
  // initialize all elements
  int killed = 0;
  int alive = 1;
  int ctr = 1;
  int cnt_alive = n;
  int idx = 0;
  // everyone is alive now
  for (idx=0;idx<n;idx++)
  {
  	arr[idx] = alive;
  }
  // start the killing
  while (cnt_alive > 0)
  {
  	for (idx=0;idx<=n;idx++)
	{ 
	  if (ctr == k)
	  {
	  	if (arr[idx] == alive)
		{
	  	  arr[idx] = killed;
		  cnt_alive = cnt_alive - 1;
		  ctr = 1;
		  fprintf(stdout,"%d\n",idx);
		}
	  }
	  else if (arr[idx] == alive)
	  {
	    ctr = ctr + 1;
	  }
	}
  }
  free (arr);
}
#endif


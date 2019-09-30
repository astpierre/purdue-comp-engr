// ***
// *** You MUST modify this file, only the ssort function
// ***

#include "sort.h"
#include <stdio.h>
#include <stdbool.h>

static bool checkOrder(int * arr, int size)
// a static function is visible only in this file
// This function returns true if the array elements are
// in the ascending order.
// false, otherwise
{
  int ind;
  for (ind = 0; ind < (size - 1); ind ++)
    {
      if (arr[ind] > arr[ind + 1])
	{
	  return false;
	}
    }
  return true;
}

#ifdef TEST_SORT
void ssort(int * arr, int size)
{  
  int ind;		// Select sort
  int sub_ind;	// Select sort
  int tmp = 0;	// Swapping

  for (ind=0; ind < size; ++ind)
  	{	
	  for (sub_ind=ind+1; sub_ind<size; ++sub_ind)
	  {
	  	// Items for comparison
	    int next = arr[sub_ind];
		int current = arr[ind];
		
		// Making character arrays of values to fix 
		// lexicographical issue when comparing vals.
		// ex. of problem 1,2,10 instead of 1,10,2
		char current_len[1000];
		char next_len[1000];
		sprintf(current_len,"%d",current);
		sprintf(next_len,"%d",next);
		
		// sizeof returns length of arrays
		int cl = 0;
		int nl = 0;
		cl = sizeof current_len;
		nl = sizeof next_len;	
		
		// If lengths are equal, treat normally
		if (cl==nl)
		{ 
		  if (current > next)
		  {
		    // Swap locations in array
			tmp = arr[sub_ind];
		    arr[sub_ind] = arr[ind];
		    arr[ind] = tmp;
		  }
		}
		// If not, catch exception and override
		else if (cl > nl)
		{
			// Swap locations in array
			tmp = arr[sub_ind];
			arr[sub_ind] = arr[ind];
			arr[ind] = tmp;
		}
	  }
	}

  if (checkOrder(arr, size) == false)
    {
      fprintf(stderr, "checkOrder returns false\n");
    }
}
#endif

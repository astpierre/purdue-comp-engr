//You must modify specific portions of this file
#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>

#ifdef TEST_MERGE
void merge(int arr[], int l, int m, int r) 
{
	// l = index of start of left sub array
	// r = index of right sub array = n-1
	// m =  endpoint of the left sub array = l+(r-l)/2
	
    int n1 = m - l + 1; 	// # elements in the left sub array
    int n2 =  r - m; 		// # elements in trhe right sub array
  
    // Create temporary arrays dynamically to help with sorting
    int *L=malloc(sizeof(* L) * n1); 
    int *R=malloc(sizeof(* R) * n2); 
    // NOTE:
    //	L[] is the left sub array
    //	R[] is the right sub array 
 
    // Initialise variables
	int idx = l;
	int i;
	int l_ind = 0;
	int r_ind = 0;

	// Copy data to temp arrays L[] and R[]
	for (i=0; i<n1; i++)
	{
		L[i] = arr[l+i];
	}
	for (i=0; i<n2; i++)
	{
		R[i] = arr[m+i+1];
	}

	// Sort data back into array
	while (l_ind<n1 && r_ind<n2)
	{
		if ((int)L[l_ind] < (int)R[r_ind])
		{
			arr[idx++] = L[l_ind++];	
		}
		else
		{
			arr[idx++] = R[r_ind++];	
		}
	}

	// Check for remaining numbers
	while (l_ind<n1)
	{
		arr[idx++] = L[l_ind++];	
	}
	while (r_ind<n2)
	{
		arr[idx++] = R[r_ind++];
	}

	// Free memory
	free(L);
	free(R);
	
}
#endif

#ifdef TEST_MERGESSORT
void mergeSort(int arr[], int l, int r) 
{
 	// int l defines the start index of the left sub array
    // int r defines the end index of the right sub array

	// Variable declaration
	int m;
	
	// Recursion condition
	if (l<r)
	{
		m = (r+l)/2;
		mergeSort(arr,l,m);
		mergeSort(arr,m+1,r);
		merge(arr,l,m,r);
	}
} 
#endif


int main(int argc, char * * argv)
{
  	// read input file
  	if (argc != 3)
    {
      	fprintf(stderr, "need the name of input and output file\n");
      	return EXIT_FAILURE;
    }
  	// open file to read
  	FILE * fptr = fopen(argv[1], "r"); 
  	if (fptr == NULL)
    {
      	fprintf(stderr, "fopen fail\n");
      	// do not fclose (fptr) because fptr failed
      	return EXIT_FAILURE;
    }
  	// count the number of integers
  	int value;
  	int count = 0;
  	while (fscanf(fptr, "%d", & value) == 1)
    {
      	count ++;
    }
  	// allocate memory to store the numbers
  	int * arr = malloc(sizeof(int) * count);
  	if (arr == NULL) // malloc fail
    {
      	fprintf(stderr, "malloc fail\n");
      	fclose (fptr);
      	return EXIT_FAILURE;
    }
  	// return to the beginning of the file
 	fseek (fptr, 0, SEEK_SET);
  	int ind = 0;
  	while (ind < count)
    {
      	if (fscanf(fptr, "%d", & arr[ind]) != 1)
	{
	  	fprintf(stderr, "fscanf fail\n");
	  	fclose (fptr);
	  	free (arr);
	  	return EXIT_FAILURE;
	}
      	ind ++;
    }
  	fclose(fptr);

	#ifdef TEST_MERGESORT 
	// Call mergeSort for whole array
 	mergeSort(arr, 0, count-1); 
	#endif
  	
	//int i;
   	/* open the file for writing*/
  	FILE * fp = fopen(argv[2], "w"); 
  	if (fp == NULL)
    {
       	fprintf(stderr, "fopen fail\n");
    }
  	for (ind = 0; ind < count; ind ++)
    {
       	fprintf (fp,"%d\n", arr[ind]);
    }
 
  	free (arr);
	fclose(fp);

  	return EXIT_SUCCESS;
}

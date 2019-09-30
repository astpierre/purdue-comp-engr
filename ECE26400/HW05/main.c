// ***
// *** Please modify this file, as indicated
// ***

#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "sort.h"


void printArray(int * arr, int size)
{
	int ind;
	for (ind = 0; ind < size; ind ++)
    {
		fprintf(stdout, "%d\n", arr[ind]);
    }
}



//============================ONLY EDIT BELOW THIS COMMENT============================//
#ifdef TEST_COMP
int comparator(const void *a, const void *b) 
{ 
	// Comparating
	return (*(const int*)a - *(const int*)b);
} 
#endif


#ifdef TEST_COUNT
int countFromFile(char* file_name)
{
	// Open + check file
	FILE * fptr = fopen(file_name, "r");
	if (fptr == NULL)
	{
		fprintf(stderr, "fopen fail\n");
		return EXIT_FAILURE;
	}

	// Count ints
	int value;
	int count = 0;
	while (fscanf(fptr, "%d",&value) == 1)
	{
		count ++;
	}
	
	// Close file + return
	fclose(fptr);
	return count;
}
#endif

#ifdef TEST_FILL
void fillArray(int* arr, int count, char* file_name)
{
	// Open + check file
	FILE * fptr = fopen(file_name, "r");
	if (fptr == NULL)
	{
		fprintf(stderr, "fopen fail\n");	
	}

	// Fill array
	int ind = 0;
	while (ind < count)
	{
		if (fscanf(fptr, "%d", &arr[ind]) != 1)
		{
			fprintf(stderr, "fscanf fail\n");
			fclose(fptr);
			free(arr);
			
		}
		ind ++;
	}

	// Close file + return
	fclose(fptr);
	return;
}
#endif

#ifdef TEST_MAIN
int main(int argc, char * * argv)
{
	// argv[1] == file name
	// Open + check file
	FILE * fptr = fopen(argv[1], "r");
	if (fptr == NULL) 
	{
		fprintf(stderr, "fopen fail\n");
		return EXIT_FAILURE;
	}

	// Save the file name
	char * file_name = argv[1];

	// Get quantity of elements from file
	int count = 0;
	count = countFromFile(file_name);

	// Allocate memory to store the numbers (initialize an array)
	int * arr = malloc(sizeof(int) * count);
	if (arr == NULL)
	{
		fprintf(stderr, "malloc fail\n");
		fclose(fptr);
		return EXIT_FAILURE;
	}

	// Call fillArray(arr, count, file_name);
	fillArray(arr, count, file_name);

	// Use the qsort() function
	qsort(arr, count, sizeof(int), comparator);

	// Show results
	printArray(arr, count);
	
	// Cleanup
	free(arr);
	fclose(fptr);
	
	return EXIT_SUCCESS;
}
#endif


//
// MODIFY THIS FILE AS DIRECTED
//
#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "vector.h"



#ifdef TEST_COMP
int cmp(const void *a, const void *b) 
{
	// Typecasting
	Vector * typecasted_a = (Vector *)a;
	Vector * typecasted_b = (Vector *)b;
	
	// Return comparated value
	return ((typecasted_a->x)-(typecasted_b->x)); 
} 
#endif

#ifdef TEST_COUNT
int numberOfElements(char* in_file_name)
{
	// Open file
	FILE * fptr = fopen(in_file_name, "rb");
	if (fptr == NULL)
	{
		fprintf(stderr, "fopen fail\n");
		return EXIT_FAILURE;
	}

	// Point to end of file
	fseek(fptr, 0, SEEK_END);

	// Get size of file
	long where = 0;
	where = ftell(fptr);

	// Obtain number of elements
	float numelem = 0;
	numelem = where / sizeof(Vector);

	// Cleanup
	fclose(fptr);
	return numelem; 
}
#endif

#ifdef TEST_FILL
void fillVector(Vector* vector, int count, char * in_file_name)
{
   	// Open file
	FILE * fptr = fopen(in_file_name, "rb");
    
	// Fill vector
    fread(vector, sizeof(Vector), count, fptr);

	// Cleanup
	fclose(fptr);
}
#endif

#ifdef TEST_WRITE
void writeFile(Vector* vector, int count, char* out_file_name)
{
	// Open file
	FILE * fptr = fopen(out_file_name, "wb");
	
	// Write outputs
	fwrite(vector, sizeof(Vector), count, fptr);

	// Cleanup
	fclose(fptr);
}
#endif

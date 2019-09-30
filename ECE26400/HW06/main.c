// ***
// *** Please modify this file, as indicated
// ***

#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "vector.h"

/*-------------------------------MODIFY BELOW THIS LINE-------------------------------*/

#ifdef TEST_MAIN
int main(int argc, char * * argv)
{
	// argv[1] = in_file
	// argv[2] = out_file
	
	// Check to make sure we are supplied with correct inputs from terminal
	if (argc != 3)
	{
		fprintf(stderr, "need input file and output file locations\n");
		return EXIT_FAILURE;
	}

	// Save input file name
	char * in_file = argv[1];
	
	// Save output file name
	char * out_file = argv[2];

    // Get # of elements in file
	int count = 0;
	count = numberOfElements(in_file);
	
    // Allocate memory to store the numbers (initialize an array of structures)
	Vector * vector = malloc(sizeof(Vector) * count);
	if (vector == NULL)
	{
		fprintf(stderr, "malloc fail\n");
		return EXIT_FAILURE;
	}

	// Call fillVector(vector, count, in_file) to store elements in an array of structures
	fillVector(vector, count, in_file);

    // Use qsort() function, after defining the cmp() function WRT "x"
	qsort(vector, count, sizeof(Vector), cmp);

    // Call the writeFile() to save sorted vector to file
	writeFile(vector, count, out_file);

	// Cleanup
	free(vector);
    return EXIT_SUCCESS;
}
#endif

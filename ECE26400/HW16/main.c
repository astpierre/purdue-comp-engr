/****************** Modify this file at specified place ***********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw16.h"


#ifdef PRINT_FUN
// Print function for tn1 contained in tn2
void PrintTn1ContainedTn2 (bool tn1_contained_tn2, bool tn2_contained_tn1)
{
	if (tn1_contained_tn2)
		printf("tree1 is contained in tree2\n");
	else
		printf("tree1 is not contained in tree2\n");

	if (tn2_contained_tn1)
		printf("tree2 is contained in tree1\n");
	else
		printf("tree2 is not contained in tree1\n");

	if (tn1_contained_tn2 && tn2_contained_tn1)
		printf("tree1 and tree2 are mutually contained.\n");
	else
		printf("tree1 and tree2 are not mutually contained.\n");
}
#endif


/****************** DO NOT Modify this file above this line *******************/
#ifdef TEST_MAIN
int main(int argc, char **argv)
{
    // Check input arguments
    if(argc != 3) return EXIT_FAILURE;

    // Create 2 binary trees from input args
    treeNode * tn1 = BinaryTreeCreate(argv[1]);
    treeNode * tn2 = BinaryTreeCreate(argv[2]);

    // Check relationship between the two trees
    //  1. Check if tn1 is contained in tn2
    //  2. Check is tn2 is contained in tn1
    //  3. Pass the results to the print function given
    PrintTn1ContainedTn2(isContained(tn2,tn1), isContained(tn1,tn2));

    // Free all memory and return success
    FreeBinaryTree(tn1);
    FreeBinaryTree(tn2);
	return EXIT_SUCCESS;
}
#endif

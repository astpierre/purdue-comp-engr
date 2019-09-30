/****************** Modify this file at specified place ***********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw12.h"
/****************** DO NOT Modify this file above this line *******************/
#ifdef TEST_MAIN
int main(int argc, char **argv)
{
    // If argc != 4 then return EXIT_FAILURE
    if(argc != 4) return EXIT_FAILURE;

	// argv[1] - length of linked list
    int length = (int)strtol(argv[1],NULL,10);

	// argv[2] - value of k as mentioned in josephus algorithm
    int k = (int)strtol(argv[2],NULL,10);

	// argv[3] - value of elemDivisible
    int elemDivisible = (int)strtol(argv[3],NULL,10);

	// Create head node
    Node * head = NULL;
    head = CreateNode(length-1);

	// Create Linked list of length length
    LinkedListCreate(&head, length-2);
    
	// Run josephus
    Josephus(&head, k, elemDivisible);

	// Free the head node
    free(head);

	return EXIT_SUCCESS;
}
#endif

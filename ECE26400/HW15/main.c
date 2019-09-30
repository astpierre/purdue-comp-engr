/****************** Modify this file at specified place ***********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw15.h"
/****************** DO NOT Modify this file above this line *******************/

#ifdef TEST_MAIN
int main(int argc, char **argv)
{
    // Check for the right number of input arguments
    if(argc!=2) return EXIT_FAILURE;
	
    // Create head node to store the head of the LL
    Node * head = NULL;

    // Call function to create the rest of the LL, w the values of arr
    LinkedListCreate(&head, argv[1]);

	// Remove all duplicates in the linked list created above
    RemoveDuplicate(head);

    // Cleanup the LL and return success!
    Node * current = head;
    while(current!=NULL)
    {
        head = current->next;
        free(current);
        current=head;
    } 
	free(head);
    return EXIT_SUCCESS;
}
#endif

/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw13.h"
/****************** DO NOT Modify this file above this line *************************/
#ifdef TEST_MAIN
int countFromFile(char * file_name)
{
    FILE * fptr = fopen(file_name, "r");
    if(fptr==NULL) return EXIT_FAILURE;
    int value=0;
    int count=0;
    while(fscanf(fptr,"%d",&value)==1) count++;
    fclose(fptr);
    return count;
}

void fillArray(int * arr, int count, char * file_name)
{
    FILE * fptr = fopen(file_name, "r");
    if(fptr==NULL) return;
    int ind=0;
    while(ind<count)
    {
        if(fscanf(fptr,"%d",&arr[ind])!=1)
        {  fclose(fptr); free(arr);  }
        ind++;
    }
    fclose(fptr);
}

void DeleteList(Node ** head)
{
    Node * current = *head;
    Node * next = NULL;
    while(current!=NULL)
    {
        next=current->next;
        free(current);
        current=next;
    }
    *head=NULL;
}
int main(int argc, char **argv)
{
	// If argc is less than 2 then, return EXIT_FAILURE
    if(argc!=2) return EXIT_FAILURE;

    // argv[1] - location of input values
    FILE * finput = fopen(argv[1],"r");

	// Check for fopen fail
    if(finput==NULL) return EXIT_FAILURE;

    // Count number of integers in file
    int count = countFromFile(argv[1]);
    
	// Allocate memory to store the numbers
    int * arr = malloc(sizeof(int)*count);
    if(arr==NULL){  fclose(finput); return EXIT_FAILURE;  }

    // Read the file and store contents in array
    fillArray(arr,count,argv[1]);
	
    // Create head node to store the head of the linked list
    Node * head = NULL;
    //head = CreateNode((int)NULL);

	// Call function to create the rest of the linked list, w values of array
    LinkedListCreate(&head,count,arr);

	// Divide is a function to break the lists into smaller sublists
    Divide(&head);

    // Cleanup
    free(arr);
    fclose(finput);
	return EXIT_SUCCESS;
}

#endif

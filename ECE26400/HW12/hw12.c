/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include "hw12.h"

#ifdef LINKEDLIST
// Do not modify the below program, we are using ifdef block for
// ease of grading. Please include this flag in your Makefile
void LinkedListPrint(Node * head)
{
	Node *temp = head;
	while(temp!=NULL)
	{
		if(temp->next!=NULL) printf("%d,",temp->value);
		else printf("%d",temp->value);	
		temp=temp->next;
	}
	printf("\n");
}
#endif

/********** Do Not modify the file above this line, you should modify below ***********/
#ifdef TEST_CREATENODE
// CreateNode
//  Returns a node after alloc. memory and initializing values
Node * CreateNode(int value)
{
	// Allocate memory for the new Node * + check for fail
    Node * newNode = malloc(sizeof(Node));
    if(newNode == NULL) return NULL;
	
    // Create Node * with the value as 'value'
    newNode->value=value;

    // Set next pointer to NULL
    newNode->next=NULL;

    // Return the newly created node
    return newNode;
}


// DeleteNode
//  Updates a list after removing a specific node with value 
void DeleteNode(Node ** head, int v)
{
    // If nothing in list, do nothing
    if(*head==NULL) return;

    // Store head
    Node * temp = *head;

    // If the node we are looking for is at very first node
    if((temp->value) == v)
    {
        // Update the head and free the temp Node
        *head = temp->next;
        free(temp);
        return;
    }

    // Traverse! Break when reach node right before target
    while(((temp->next)!=NULL) && (((temp->next)->value) != v))
    {  temp = temp->next;  }

    // Check if we 'over-traversed'
    if((temp->next) == NULL) return;

    // Save the pointer to the next of node to be deleted
    Node * newNext = temp->next->next;

    // Unlink the node from linked list
    free(temp->next);

    // Append the rest of the list using pointer to the next of deleted node
    temp->next = newNext;
    
    return;
}
#endif

#ifdef TEST_LINKEDLISTCREATE
// LinkedListInsert
//  Inserts a new node in the ll at the begining
void LinkedListInsert(Node ** head, int v)
{
    Node * newNode = CreateNode(v);
    newNode->next = *head;
    *head = newNode;
}

// LinkedListCreate
//  Creates a ll of variable length with values set to indices
void LinkedListCreate(Node ** head, int length)
{
	// Check if length is not negative
    if(length < 0) return;

	// Create linked list of length as 'length'
    for(; length>=0; --length){  LinkedListInsert(head,length);  }
}
#endif

#ifdef TEST_JOSEPHUS
// 1. head: the head of the singly linkedlist.
// 2. k : this variable will be used for counting if count = k, the element will be out.
// 3. elemDivisible : this variable will be used for printing. When the number of
//    remaining nodes in linked list is divisible by elemDivisible then you should 
//    print the remaining LinkedList with print functin provided to you.
// CountNodes
//  Returns the number of nodes in a linked list
int CountNodes(Node * head)
{
    int nodes = 0;
    while(head != NULL)
    {
        head=head->next;
        nodes++;
    }
    return nodes;
}

// SearchNodes
//  Returns 1 if element exists in list, 0 if not found
int SearchNodes(Node * head, int v)
{
    Node * ptr = head;
    while(ptr != NULL)
    {
        if((ptr->value) == v) return 1;
        ptr = ptr->next;
    }
    // Only reached if not fount
    return 0;
}

// Josephus
//  Solves the Josephus problem 
void Josephus(Node ** head, int k, int elemDivisible)
{
    // Initialize some parameters
    int ctr=1;
    int origCount=CountNodes(*head);
    int count_alive=origCount;
    int i=0;

    // Begin killing ship-mates
    while(count_alive>1)
    {
        count_alive=CountNodes(*head);
        for(i=0;i<origCount;i++)
        {
            count_alive=CountNodes(*head);
            if(ctr==k+1)
            {
                if(SearchNodes(*head, i) == 1)
                {
                    DeleteNode(head,i);
                    count_alive=CountNodes(*head);
                    if(count_alive%elemDivisible == 0)
                    {  LinkedListPrint(*head);  }
                    ctr=1;
                }
            }
            else if(SearchNodes(*head, i) == 1) ctr++;
        }
    }
}
#endif

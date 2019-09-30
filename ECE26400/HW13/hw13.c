/****************** Modify this file at specified place *************************/
#include <stdio.h>
#include <stdlib.h>
#include "hw13.h"

#ifdef LINKEDLIST
// Do not modify this function, we are using this within ifdef block for
// ease of grading.
void LinkedListPrint(Node * * source)
{
	Node *temp = * source;
	while(temp!=NULL)
	{
		if(temp->next!=NULL)
		{  printf("%d,",temp->value);  }
		else
		{  printf("%d",temp->value);  }
		temp=temp->next;
	}
	printf("\n");
}
#endif
/********** Do Not modify the file above this line, you can modify below ******/
#ifdef TEST_CREATENODE
Node * CreateNode(int val)
{
    // Allocate mem for the new Node * + check for mem fail
    Node * newNode = malloc(sizeof(Node));

    // Create Node * with the value as "val"
    newNode->value=val;

    // Set next pointer to NULL
    newNode->next=NULL;

    // Return the newly create node
    return newNode;
}

void DeleteNode(Node ** head, int v)
{
    // If nothing in list, do nothing
    if(*head==NULL) return;

    // Store the head
    Node * temp = *head;

    // If the new node we are looking for is at the very first node
    if((temp->value) == v)
    {
        // Update the head and free temp node
        *head = temp->next;
        free(temp);
        return;
    }

    // Traverse! Break when reach node right before target
    while(((temp->next)!=NULL) && (((temp->next)->value)!=v))
    {  temp=temp->next;  }

    // Check if we over traversed...
    if((temp->next)==NULL) return;

    // Save the pointer to the next of node to be deleted
    Node * newNext = temp->next->next;

    // Unlink the node from the linked list
    free(temp->next);

    // Append the rest of the list using pointer to the next of deleted
    temp->next = newNext;

    return;
}
#endif

#ifdef TEST_LINKEDLISTCREATE
void LinkedListInsert(Node ** head, int v)
{
    Node * newNode = CreateNode(v);
    newNode->next=*head;
    *head=newNode;
}

void LinkedListCreate(Node ** source, int len, int* arr)
{
    // Check if length is non-negative
    if(len<0) return;

    // Create linkedlist of length 'len'
    for(; len>0; len--){  LinkedListInsert(source,arr[len-1]);  }
}

#endif

#ifdef TEST_SPLIT
int CountNodes(Node * head)
{
    int nodes = 0;
    while(head != NULL)
    {  head=head->next; nodes++;  }
    return nodes;
}

void SplitList(Node* source, Node** head1, Node** head2) 
{
    // Create two nodes for traversing
    Node * slow;
    Node * fast;

    // Concept: when fast==NULL, slow will point right before midpoint
    slow = source;
    fast = source->next;

    while(fast!=NULL)
    {
        fast=fast->next;
        if(fast!=NULL)
        {  slow=slow->next; fast=fast->next;  }
    }

    // Slow is now the point right before the midpoint at the list
    *head1 = source;
    *head2 = slow->next;

    // Add the terminating value for slow pointer
    slow->next = NULL;

    return;
} 
#endif


#ifdef TEST_DIV
void Divide(Node ** source) 
{ 
	// Declare a node, to hold the current head of source list
    Node * h = *source;

	// Declare nodes, to hold the two the heads of the two sub-lists
    Node * s1_h = NULL;
    Node * s2_h = NULL;

	// Check for the base case -- length 0 or 1
    if((CountNodes(h)==1) || (CountNodes(h)==0)) 
    {  free(h); return;  }
	  
	// Use SpiltList(...) to partition the list into sub lists
    SplitList(h,&s1_h,&s2_h);

    // Show newly created sublists
    LinkedListPrint(&s1_h);
    LinkedListPrint(&s2_h);

    // Recursively divide both sub-lists to find their respective mid-points
    Divide(&s1_h);
    Divide(&s2_h); 
}
#endif

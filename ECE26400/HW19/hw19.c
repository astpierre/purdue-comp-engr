// You can modify this file.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "hw19.h"

// DO NOT MODIFY THIS FUNCTION
void PrintAns(ListNode* head, ListNode* min1, ListNode* min2)
{
	int i;
	i = 0;
	while(i < head -> treenode->dimension)
	{
		if(i == 0)
			printf("(%d, ", min1->treenode->data[i]);
		else if(i == head -> treenode->dimension-1)
			printf("%d) <-> ", min1->treenode->data[i]);
		else
			printf("%d, ", min1->treenode->data[i]);
		i+=1;
	}

	i = 0;
	while(i < head -> treenode->dimension)
	{
		if(i == 0)
			printf("(%d, ", min2->treenode->data[i]);
		else if(i == head -> treenode->dimension-1)
			printf("%d)\n", min2->treenode->data[i]);
		else
			printf("%d, ", min2->treenode->data[i]);
		i+=1;
	}
}

#ifdef TEST_CENT
ListNode* FindCentroid(TreeNode* x, TreeNode* y)
{
	// Variable declaration
	int temp=0;
	int i=0;
	// Create a new node
	ListNode * newLNode = NULL;

	for(i=0; i<(x->dimension); i++)
	{
		temp = x->data[i] + y->data[i];
		newLNode->treenode->data[i] = temp/2;
	}
	for(i=0; i<(x->dimension); i++)
	{
		if(x->data[i] < y->data[i])
		{
			newLNode->treenode->left = x;
			newLNode->treenode->right = y;
			break;
		}
		else if(x->data[i] > y->data[i])
		{
			newLNode->treenode->left = y;
			newLNode->treenode->right = x;
			break;
		}
	}
	// If error...
	if(i==x->dimension) return NULL;
	return newLNode;
}
#endif

#ifdef TEST_DIST
int FindDist(TreeNode* x, TreeNode* y)
{
		// Find the eucledian distance between x->data and y->data
    long int distance = 0;
    long int tmp = 0;
    for(int i=0; i<x->dimension; i++)
    {
				tmp = 0;
        tmp = (y->data[i]) - (x->data[i]);
        distance = distance + (tmp*tmp);
    }
		return (int)distance;
}
#endif


#ifdef TEST_FUSE
ListNode * LinkedListInsertEnd(ListNode * head, ListNode * newNode)
{
  ListNode * curr = head;
	while(curr != NULL && curr->next != NULL) curr = curr->next;
  newNode->next = NULL;
  if (curr != NULL) curr->next = newNode;
  else head = newNode;
	return head;
}

void DeleteNextNode(ListNode ** head, ListNode ** target)
{
    // If nothing in list, do nothing
    if(*head==NULL) return;

    // Store the head
    ListNode * temp = *head;
		ListNode * trgt = *target;
    ListNode * newNext = NULL;

    // If the node we are looking for is at the very first node
    if(temp->treenode->data == trgt->treenode->data)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    // Traverse! Break when reach node right before target
    while(((temp->next) != NULL) &&
				 (temp->next->treenode->data != trgt->treenode->data))
		{  temp = temp->next;  }

    // Check if we over-traversed...
    if((temp->next) == NULL) return;

    // Save the pointer to the next of the node to be deleted
    newNext = temp->next->next;

    // Append the rest of the list using pointer to the next of deleted
    temp->next = newNext;
}

ListNode* Fuse(ListNode* head, ListNode* fuse1, ListNode* fuse2)
{
	// Create a new node
	ListNode * newLNode = FindCentroid(fuse1->treenode,fuse2->treenode);
	// Add the new ListNode to the list
	head = LinkedListInsertEnd(head, newLNode);
	// Remove the fuse1 and fuse2 from the list (Do NOT free)
	DeleteNextNode(&head, &fuse1);
	DeleteNextNode(&head, &fuse2);
	return head;
}
#endif

#ifdef TEST_CREATENODE
ListNode* CreateNode(int n, int dim, int* arr)
{
	ListNode * newLNode = malloc(sizeof(ListNode));
	TreeNode * newTNode = malloc(sizeof(TreeNode));
	newTNode->dimension = dim;
	newTNode->left = NULL;
	newTNode->right = NULL;
	newTNode->data = malloc(sizeof(int)*(dim));
	for(int i=0; i<newTNode->dimension; i++)
    {  memcpy(&newTNode->data[i], &arr[i], 1);  }
	newLNode->treenode = newTNode;
	return newLNode;
}
#endif


#ifdef TEST_LINKEDLISTCREATE
// Reverse a linked list
void reverseLinkedList(ListNode ** head)
{
    ListNode * prev = NULL;
    ListNode * curr = *head;
    ListNode * next = NULL;
    while(curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}
// Fill an array with count integers from a file
void fillArray(int * arr, int count, FILE * fptr)
{
    int ind=0;
    while(ind<count)
    {
        if(fscanf(fptr,"%d",&arr[ind]) != 1)
        {  fclose(fptr); free(arr);  }
        ind++;
    }
}
// Create a linked list of arrays by reading from a file
void LinkedListCreate(ListNode ** head, int n, int dim, FILE * fptr)
{
	// malloc an array of length dim
	int * arr = malloc(sizeof(int)*(dim));
	if(arr==NULL) {  printf("ERROR: LinkedListCreate\n"); return;  }

	int i=0;
	while(i<n)
	{
		fillArray(arr,dim,fptr);
		ListNode * newLNode = CreateNode(n,dim,arr);
		newLNode->next = *head;
		*head = newLNode;
		i+=1;
	}
  free(arr);
  reverseLinkedList(head);
	fclose(fptr);
}
#endif

#ifdef TEST_CLUSTER
void MakeCluster(ListNode ** head)
{
	// Find pair of ListNodes with least distance between them
  int minDis = -1;
  int tmpDis = 0;
  int i = 0;
  int minInd1 = 0;
  int minInd2 = 0;
  ListNode * minNode1 = NULL;
  ListNode * minNode2 = NULL;
  ListNode * tmp1 = * head;
  ListNode * tmp2 = NULL;
  int index1 = 0;
  int index2 = 0;

	if(tmp1->next == NULL) return;

	while(tmp1->next != NULL)
  {
    index2=0;
    tmp2 = *head;
    while(tmp2 != NULL)
    {
        if(index1 != index2)
        {
            tmpDis = FindDist(tmp1->treenode,tmp2->treenode);
            if((tmpDis < minDis) || (minDis == -1))
            {
                minInd1 = index1;
                minInd2 = index2;
                minDis = tmpDis;
            }
        }
        tmp2=tmp2->next;
        index2+=1;
    }
    tmp1 = tmp1->next;
    index1+=1;
  }

  // Point to the right min Nodes
  i=0;
  minNode1 = *head;
  while(i<minInd1) {  minNode1=minNode1->next; i++;  }
  i=0;
  minNode2 = *head;
  while(i<minInd2) {  minNode2=minNode2->next; i++;  }

	// Fuse the two nodes into one node
	*head = Fuse(*head,minNode1,minNode2);

	// Call print function
	PrintAns(*head,minNode1,minNode2);

	MakeCluster(head);
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"

// Linked list type definition
typedef struct listnode {
	struct listnode * next;
    int val;
}listnode;

// Linked list methods
void LinkedListDestroy(listnode ** head) {
    listnode * current = *head;
	while(current!=NULL) {
		*head = current->next;
		free(current);
		current=*head;
	}
}
listnode * CreateListNode(int val) {
	listnode * lnode = malloc(sizeof(listnode));
	lnode->next = NULL;
    lnode->val = val;
	return lnode;
}
int CountNodes(listnode ** head) {
	listnode * temp = *head;
    int nodes = 0;
    while(temp != NULL)
    {  temp=temp->next; nodes+=1;  }
    return nodes;
}
void LinkedListAppend(listnode ** head, int val) {
	listnode * newNode = CreateListNode(val);
	listnode * temp = *head;
	while(temp->next != NULL) temp = temp->next;
	temp->next = newNode;
    return;
}
int LinkedListValueExists(listnode * head, int val) {
	if(head == NULL) return 0;
    listnode * temp = head;
    while(temp != NULL) {
        if(temp->val == val) return 1;
        temp=temp->next;
    }
    return 0;
}
int GetListValueByIndex(listnode ** sequence, int idx) {
	int i = 0;
	listnode * temp = *sequence;
	while(i != idx) {
		temp = temp->next;
		i += 1;
	}
	return temp->val;
}
void PrintList(listnode ** head) {
	listnode * temp = *head;
	while(temp != NULL) {
		if(temp->next != NULL) {
			printf("[ %d ] -> \n",temp->val);
		}
		else {
			printf("[ %d ]\n",temp->val);
		}
		temp=temp->next;
	}
}

// Merge sort methods
listnode * Merge(listnode * upper, listnode * lower) {
    // Create a node to be the pointer to the sorted values
    listnode * sortedMerging = NULL;

	// Check for the base cases. (When either sub-list is NULL)
    if(upper==NULL) return lower;
    else if(lower==NULL) return upper;

	// Pick the larger between upper and lower, and recurse
    if(upper->val <= lower->val) {
        sortedMerging = upper;
        sortedMerging->next = Merge(upper->next,lower);
    } else {
        sortedMerging = lower;
        sortedMerging->next = Merge(upper,lower->next);
    }

    // Return the merged array
    return sortedMerging;
}
void SplitList(listnode * head, listnode** head1, listnode** head2) {
    // Create two nodes for traversing
    listnode * slow;
    listnode * fast;

    // Concept: when fast==NULL, slow will point right before midpoint
    slow = head;
    fast = head->next;

    while(fast!=NULL)
    {
        fast=fast->next;
        if(fast!=NULL)
        {  slow=slow->next; fast=fast->next;  }
    }

    // Slow is now the point right before the midpoint at the list
    *head1 = head;
    *head2 = slow->next;

    // Add the terminating value for slow pointer
    slow->next = NULL;

    return;
}
void MergeSort(listnode ** head) {
	// Declare a node, to hold the current head of source list
    listnode * temp = *head;

	// Declare nodes, to hold the two the heads of the two sub-lists
    listnode * s1_h = NULL;
    listnode * s2_h = NULL;

	// Check for the base case -- length 0 or 1
    if((CountNodes(&temp)==1) || (CountNodes(&temp)==0))
    {  return;  }

	// Use SpiltList(...) to partition the list into sub lists
    SplitList(temp,&s1_h,&s2_h);

	// Recursively sort the sub-lists by calling MergeSort() on the upper and lower sub-lists
    MergeSort(&s1_h);
    MergeSort(&s2_h);

    // Merge the two sorted lists together, using the Merge()
    * head = Merge(s1_h, s2_h);
}

// Generate sequence methods / helpers
void MakeLongArray(listnode ** head, long ** arrLong, int size) {
	long i = 0;
	long * arr = * arrLong;
	listnode * temp = *head;
	for(i=0; i<size; i++) {
		arr[i] = temp->val;
		temp=temp->next;
	}
}
void Generate_2p3q_Helper(listnode ** sequence, int length, int * idx) {
	// Grab the value at index in linked list
	int indexVal = GetListValueByIndex(sequence, *idx);

	// Calculate the next values in the sequence
	int timesTwo = indexVal * 2;
	int timesThree = indexVal * 3;

	// Don't add duplicates and check for terminal condition
	if(!LinkedListValueExists(*sequence, timesTwo)) {
		if(timesTwo < length) {
			// Add this approved element
			LinkedListAppend(sequence, timesTwo);
		} else {
			// Terminating condition met, sort and exit
			MergeSort(sequence);
			return;
		}
	}
	if(!LinkedListValueExists(*sequence, timesThree)) {
		if(timesThree < length) {
			// Add this approved element
			LinkedListAppend(sequence, timesThree);
		} else {
			// Terminating condition met, sort and exit
			MergeSort(sequence);
			return;
		}
	}

	// Increment the index and recurse
	*idx += 1;
	Generate_2p3q_Helper(sequence, length, idx);
}
long * Generate_2p3q_Seq(int length, int * seq_size) {
    /********************************************
	*	INPUT:
    *    length      number of long integers to
    *                be sorted
    *    seq_size    pointer to num of elements
    *                in the sequence, this func
    *                stores the value here
    *  	RETURN:
	*	 long * 	 pointer to an array of
	* 				 long integers
    ********************************************/

    // Variable declaration
    int size = 0;
	int idx = 0;
    long * long_arr = NULL;

    // Check for 0 or 1 number of elements (corner cases)
    switch (length) {
        case 0:
            size = 0;
            long_arr = malloc(sizeof(long) * size);
            if (long_arr == NULL) {
                fprintf(stderr, "malloc fail\n");
                *seq_size = 0;
                return NULL;
            }
            return long_arr;
        case 1:
            size = 0;
            long_arr = malloc(sizeof(long) * size);
            if (long_arr == NULL) {
                fprintf(stderr, "malloc fail\n");
                *seq_size = 0;
                return NULL;
            }
			long_arr[0] = 0;
            return long_arr;
    }

	// Create a linked list for building the sequence
	listnode * sequence = CreateListNode(1);
	Generate_2p3q_Helper(&sequence, length, &idx);

	// Count the nodes in the linked list sequence
	size = CountNodes(&sequence);
    *seq_size = size;

	// Allocate memory for an array of longs
    long_arr = malloc(sizeof(long) * size);
	if(long_arr == NULL) {
		fprintf(stderr, "malloc fail\n");
        *seq_size = 0;
        free(sequence);
		return NULL;
	}

	// Translate the sequence from linked list to an array
	MakeLongArray(&sequence, &long_arr, size);

	// Cleanup and return pointer to array
	LinkedListDestroy(&sequence);
    return long_arr;
}

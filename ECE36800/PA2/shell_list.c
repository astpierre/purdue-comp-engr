#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sequence.h"
#include "shell_list.h"

// Linked list methods
static Node * CreateShellNode(long value) {
	Node * lnode = malloc(sizeof(Node));
	lnode->next = NULL;
    lnode->value = value;
	return lnode;
}
static int CountShellNodes(Node ** head) {
	Node * temp = *head;
    int nodes = 0;
    while(temp != NULL)
    {  temp=temp->next; nodes+=1;  }
    return nodes;
}
static void LinkedListShellAppend(Node ** head, long value) {
	Node * newNode = CreateShellNode(value);
	Node * temp = *head;
	while(temp->next != NULL) temp = temp->next;
	temp->next = newNode;
    return;
}
static long GetValueByIndex(Node ** sequence, int idx) {
	int i = 0;
	Node * temp = *sequence;
	while(i != idx) {
		temp = temp->next;
		i += 1;
	}
	return temp->value;
}
static void ExchangeListOrder(Node ** head, int i, int j) {
    Node * i_ref = *head;
    Node * j_ref = *head;
    Node * prev_i_node = NULL;
    Node * prev_j_node = NULL;
    int ctr = 0;
    while(ctr < i) {
        prev_i_node = i_ref;
        i_ref = i_ref->next;
        ctr += 1;
    }

    ctr = 0; // RESET COUNTER
    while(ctr < j) {
        prev_j_node = j_ref;
        j_ref = j_ref->next;
        ctr += 1;
    }

    if(prev_i_node != NULL) prev_i_node->next = j_ref;
    else *head = j_ref;

    if(prev_j_node != NULL) prev_j_node->next = i_ref;
    else *head = i_ref;

    /* Swap the next pointers using a temp node */
    Node * tmp = j_ref->next;
    j_ref->next = i_ref->next;
    i_ref->next = tmp;
    return;
}

// Required methods
Node * List_Load_From_File(char * filename) {
    long temp = 0;
    FILE * fptr = fopen(filename, "rb");
    if(fptr == NULL) {
        printf("BAD FILENAME\n");
        fclose(fptr);
        return NULL;
    }
    fseek(fptr, 0, SEEK_SET);
    Node * head = NULL;
    if(fread(&temp, sizeof(long), 1, fptr) != 1) printf("BAD FREAD\n");
    else head = CreateShellNode(temp);
    while(feof(fptr) == 0) {
        if(fread(&temp, sizeof(long), 1, fptr) != 1) break;
        else LinkedListShellAppend(&head, temp);
    }
    fclose(fptr);
    return head;
}
int List_Save_To_File(char * filename, Node * list) {
    FILE * fptr = fopen(filename,"wb");
    if(fptr == NULL) {
        printf("error creating file");
        return EXIT_FAILURE;
    }
    if(CountShellNodes(&list) == 0) {
        return 0;
    }
    int counter = 0;
    Node * temp = list;
    while(temp != NULL) {
        if(fwrite(&temp->value, sizeof(long), 1, fptr) != 1)
        {  printf("List_Save_To_File: bad fwrite\n");  }
        counter += 1;
        temp = temp->next;
    }
    fclose(fptr);
    return counter;
}
Node * List_Shellsort(Node * list, double * n_comp) {
    // Generate the sequence for shell sorting
    long * sequence = NULL;
    int seq_size = 0;
    int list_length = CountShellNodes(&list);
    sequence = Generate_2p3q_Seq(list_length, &seq_size);

    // Step through elements in sequence
    long interval = 0;
    int i=0;
    int j=0;
    for(; seq_size > 0; seq_size--) {
        interval = sequence[seq_size - 1];
        for(j = interval; j < list_length; j++) {
            i = j - (int)interval;
            while(i >= 0) {
                *n_comp = *n_comp + 1.0;
                if(GetValueByIndex(&list, j) < GetValueByIndex(&list, i)){
                    ExchangeListOrder(&list, i+(int)interval, i);
                }
                i = i - (int)interval;
            }
        }
    }
    free(sequence);
    return list;
}

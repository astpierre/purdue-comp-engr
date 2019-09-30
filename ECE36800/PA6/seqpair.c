#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "seqpair.h"

/* Macros/defines */
static void insertion_sort_H( rectangle * arr, int lb, int ub );
static void insertion_sort_V( rectangle * arr, int lb, int ub );

/* Linked list functions */
list_node * list_node_create(int label) {
    list_node * newNode = malloc(sizeof(list_node));
    newNode->label = label;
    newNode->next = NULL;
    return newNode;
}
void list_free(list_node * head) {
    list_node * current = head;
    while(current != NULL) {
        head = current->next;
        free(current);
        current = head;
    }
    free(head);
}
void list_delete_value(list_node ** head, int v) {
    // If nothing in list, do nothing
    if(*head==NULL) return;

    // Store the head
    list_node * temp = *head;

    // If the new node we are looking for is at the very first node
    if((temp->label) == v) {
        // Update the head and free temp node
        *head = temp->next;
        free(temp);
        return;
    }

    // Traverse! Break when reach node right before target
    while(((temp->next)!=NULL) && (((temp->next)->label)!=v))
    {  temp=temp->next;  }

    // Check if we over traversed...
    if((temp->next)==NULL) return;

    // Save the pointer to the next of node to be deleted
    list_node * newNext = temp->next->next;

    // Unlink the node from the linked list
    free(temp->next);

    // Append the rest of the list using pointer to the next of deleted
    temp->next = newNext;

    return;
}
void list_insert(list_node ** head, int v) {
    list_node * newNode = list_node_create(v);
    newNode->next=*head;
    *head=newNode;
}
void list_print(list_node * head) {
	list_node * temp = head;
	while(temp!=NULL) {
		if(temp->next!=NULL) printf("%d,",temp->label);
		else printf("%d",temp->label);
		temp=temp->next;
	}
	printf("\n");
}
bool list_search(list_node * head, int v) {
    list_node * ptr = head;
    while(ptr != NULL) {
        if((ptr->label) == v) return true;
        ptr = ptr->next;
    }
    // Only reached if not found
    return false;
}

/* Adjacency linked list functions */
adj_list_node * adj_list_node_create(int label) {
    adj_list_node * newNode = malloc(sizeof(adj_list_node));
    newNode->list = NULL;
    newNode->next = NULL;
    newNode->label= label;
    return newNode;
}
void adj_list_free(adj_list_node * head) {
    adj_list_node * current = head;
    while(current != NULL) {
        head = current->next;
        list_free(current->list);
        free(current);
        current = head;
    }
    free(head);
}
void adj_list_delete_value(adj_list_node ** head, int v) {
    // If nothing in list, do nothing
    if(*head==NULL) return;

    // Store the head
    adj_list_node * temp = *head;

    // If the new node we are looking for is at the very first node
    if((temp->label) == v) {
        // Update the head and free temp node
        *head = temp->next;
        free(temp);
        return;
    }

    // Traverse! Break when reach node right before target
    while(((temp->next)!=NULL) && (((temp->next)->label)!=v))
    {  temp=temp->next;  }

    // Check if we over traversed...
    if((temp->next)==NULL) return;

    // Save the pointer to the next of node to be deleted
    adj_list_node * newNext = temp->next->next;

    // Unlink the node from the linked list
    list_free(temp->next->list);
    free(temp->next);

    // Append the rest of the list using pointer to the next of deleted
    temp->next = newNext;

    return;
}
void adj_list_insert(adj_list_node ** head, int label) {
    adj_list_node * newNode = adj_list_node_create(label);
    newNode->next=*head;
    *head=newNode;
}
void adj_list_print(adj_list_node * head) {
	adj_list_node * temp = head;
	while(temp!=NULL) {
        printf("(%d)\t", temp->label);
        list_print(temp->list);
		temp=temp->next;
	}
}
adj_list_node * adj_list_find(adj_list_node * head, int label) {
    adj_list_node * ptr = head;
    while(ptr != NULL) {
        if((ptr->label) == label) return ptr;
        ptr = ptr->next;
    }
    // Only reached if not found
    return NULL;
}

/* Packing rectangle functions */
void init_rectangle( rectangle * r, int l, double w, double h ) {
    /* Initialize all fields */
    r->width = w;
    r->height = h;
    r->label = l;
    r->h_sum = 0;
    r->v_sum = 0;
    r->x_0 = 0;
    r->x_f = 0;
    r->y_0 = 0;
    r->y_f = 0;
    return;
}
void generate_horizontal_adj_lists( int * seq0, int * seq1, adj_list_node ** before, adj_list_node ** after ) {
    int seq_size = NUMRECTANGLES;
    adj_list_node * bADJ = NULL;
    adj_list_node * aADJ = NULL;

    /* Create list of lists (horiz adj list) */
    for(int i=0; i<seq_size; i++) { /* Initialize adjacency lists */
        adj_list_insert(&bADJ, seq0[i]);
        adj_list_insert(&aADJ, seq0[i]);
    }
    /*  Fill in lists */
    for(int i=0; i<seq_size; i++) {
        list_node * after_list = list_node_create(seq0[i]);
        list_node * before_list = list_node_create(seq0[i]);

        /* The rectangles appearing before 'X' in S1 */
        for(int k=0; k<i; k++) {
            list_insert(&before_list, seq0[k]);
        }
        list_node * final_before = NULL;

        /* The rectangles appearing before 'X' in S2 */
        for(int j=0; j<seq_size; j++) {
            if(seq1[j] == seq0[i]) {
                list_delete_value(&before_list, seq1[j]);
                break;
            } else if(list_search(before_list, seq1[j]) == false) {
                list_delete_value(&before_list, seq1[j]);
            } else {
                list_insert(&final_before, seq1[j]);
            }
        }

        /* The rectangles appearing after 'X' in S1 */
        for(int k=seq_size-1; k>i; k--) {
            list_insert(&after_list, seq0[k]);
        }
        list_node * final_after = NULL;

        /* The rectangles appearing after 'X' in S2 */
        bool foundX = false;
        int idx = 0;
        while(!foundX) {
            if(seq1[idx] == seq0[i]) {
                foundX = true;
                list_delete_value(&after_list, seq1[idx]);
            }
            idx += 1;
        }
        for(int j=idx; j<seq_size; j++) {
            if(list_search(after_list, seq1[j]) == false) {
                list_delete_value(&after_list, seq1[j]);
            } else {
                list_insert(&final_after, seq1[j]);
            }
        }

        /* Update adjacency lists */
        list_node * current = final_after;
        if(current!=NULL) {
            while(current != NULL) {
                final_after = current->next;
                adj_list_node * adjN = adj_list_find(aADJ, current->label);
                list_insert(&(adjN->list), seq0[i]);
                free(current);
                current=final_after;
            }
        }
        current = final_before;
        if(current!=NULL) {
            while(current != NULL) {
                final_before = current->next;
                adj_list_node * adjN = adj_list_find(bADJ, current->label);
                list_insert(&(adjN->list), seq0[i]);
                free(current);
                current=final_before;
            }
        }
        list_free(before_list);
        list_free(after_list);
        list_free(final_before);
        list_free(final_after);
    }
    *before = bADJ;
    *after = aADJ;
    return;
}
void generate_vertical_adj_lists( int * seq0, int * seq1, adj_list_node ** below, adj_list_node ** above ) {
    int seq_size = NUMRECTANGLES;
    adj_list_node * bADJ = NULL;
    adj_list_node * aADJ = NULL;

    /* Create list of lists (vert adj list) */
    for(int i=0; i<seq_size; i++) { /* Initialize adjacency lists */
        adj_list_insert(&bADJ, seq0[i]);
        adj_list_insert(&aADJ, seq0[i]);
    }

    /*  Fill in lists */
    for(int i=0; i<seq_size; i++) {
        list_node * above_list = list_node_create(seq0[i]);
        list_node * below_list = list_node_create(seq0[i]);

        /* The rectangles appearing after 'X' in S1 */
        for(int k=(seq_size-1); k>i; k--) {
            list_insert(&above_list, seq0[k]);
        }
        list_node * final_above = NULL;

        /* The rectangles appearing before 'X' in S1 */
        for(int k=0; k<i; k++) {
            list_insert(&below_list, seq0[k]);
        }
        list_node * final_below = NULL;

        /* The rectangles appearing before 'X' in S2 */
        for(int j=0; j<seq_size; j++) {
            if(seq1[j] == seq0[i]) {
                list_delete_value(&above_list, seq1[j]);
                break;
            } else if(list_search(above_list, seq1[j]) == false) {
                list_delete_value(&above_list, seq1[j]);
            } else {
                list_insert(&final_above, seq1[j]);
            }
        }

        /* The rectangles appearing after 'X' in S2 */
        bool foundX = false;
        int idx = 0;
        while(!foundX) {
            if(seq1[idx] == seq0[i]) {
                foundX = true;
                list_delete_value(&below_list, seq1[idx]);
            }
            idx += 1;
        }
        for(int j=idx; j<seq_size; j++) {
            if(list_search(below_list, seq1[j]) == false) {
                list_delete_value(&below_list, seq1[j]);
            } else {
                list_insert(&final_below, seq1[j]);
            }
        }

        /* Update adjacency lists */
        list_node * current_A = final_above;
        if(current_A!=NULL) {
            while(current_A != NULL) {
                final_above = current_A->next;
                adj_list_node * adjN = adj_list_find(aADJ, current_A->label);
                list_insert(&(adjN->list), seq0[i]);
                free(current_A);
                current_A=final_above;
            }
        }
        list_node * current_B = final_below;
        if(current_B!=NULL) {
            while(current_B != NULL) {
                final_below = current_B->next;
                adj_list_node * adjN = adj_list_find(bADJ, current_B->label);
                list_insert(&(adjN->list), seq0[i]);
                free(current_B);
                current_B=final_below;
            }
        }

        list_free(below_list);
        list_free(above_list);
        list_free(final_below);
        list_free(final_above);
    }
    /* Assign to params */
    *below = bADJ;
    *above = aADJ;
    return;
}
static void insertion_sort_H( rectangle * arr, int lb, int ub ) {
    rectangle tmp;
    for(int i=ub; i > lb; i--) {
        if(arr[i].h_sum < arr[i-1].h_sum) {
            tmp = arr[i];
            arr[i] = arr[i-1];
            arr[i-1] = tmp;
        }
    }
    for(int i=lb+2; i<=ub; i++) {
        int j = i;
        rectangle piv = arr[i];
        while(piv.h_sum < arr[j-1].h_sum) {
            arr[j] = arr[j-1]; j--;
        }
        arr[j] = piv;
    }
}
static void insertion_sort_V( rectangle * arr, int lb, int ub ) {
    rectangle tmp;
    for(int i=ub; i > lb; i--) {
        if(arr[i].v_sum < arr[i-1].v_sum) {
            tmp = arr[i];
            arr[i] = arr[i-1];
            arr[i-1] = tmp;
        }
    }
    for(int i=lb+2; i<=ub; i++) {
        int j = i;
        rectangle piv = arr[i];
        while(piv.v_sum < arr[j-1].v_sum) {
            arr[j] = arr[j-1]; j--;
        }
        arr[j] = piv;
    }
}
void topo_horiz(rectangle * rectangles, adj_list_node * horizontal_list) {
    for(int i=0; i<NUMRECTANGLES; i++) {
        adj_list_node * ADJ = adj_list_find(horizontal_list, rectangles[i].label);
        list_node * L = ADJ->list;
        int sum = 0;
        if(L!=NULL) {
            while(L!=NULL) {
                sum+=L->label;
                L=L->next;
            }
        }
        rectangles[i].h_sum = sum;
    }
    insertion_sort_H(rectangles, 0, NUMRECTANGLES-1);
    return;
}
void topo_vert(rectangle * rectangles, adj_list_node * vertical_list) {
    for(int i=0; i<NUMRECTANGLES; i++) {
        adj_list_node * ADJ = adj_list_find(vertical_list, rectangles[i].label);
        list_node * L = ADJ->list;
        int sum = 0;
        while(L!=NULL) {
            sum+=L->label;
            L=L->next;
        }
        rectangles[i].v_sum = sum;
    }
    insertion_sort_V(rectangles, 0, NUMRECTANGLES-1);
    return;
}
void calc_horiz(rectangle * rectangles, adj_list_node * before, adj_list_node * after) {
    int size = NUMRECTANGLES;
    for(int i=0; i<size; i++) {
        if(rectangles[i].h_sum == 0) {
            rectangles[i].x_0 = 0.0;
            rectangles[i].x_f = rectangles[i].x_0 + rectangles[i].width;
        } else {
            adj_list_node * ADJ = adj_list_find(after, rectangles[i].label);
            list_node * L = ADJ->list;
            double max_choice = 0;
            if(L != NULL) {
                while(L != NULL) {
                    for(int j=0; j<size; j++) {
                        if(rectangles[j].label == L->label) {
                            if(rectangles[j].x_f > max_choice) {
                                max_choice = rectangles[j].x_f;
                            }
                        }
                    }
                    L = L->next;
                }
            }
            rectangles[i].x_0 = max_choice;
            rectangles[i].x_f = rectangles[i].x_0 + rectangles[i].width;
        }
    }
}
void calc_vert(rectangle * rectangles, adj_list_node * below, adj_list_node * above) {
    int size = NUMRECTANGLES;
    for(int i=0; i<size; i++) {
        if(rectangles[i].v_sum == 0) {
            rectangles[i].y_0 = 0.0;
            rectangles[i].y_f = rectangles[i].y_0 + rectangles[i].height;
        } else {
            adj_list_node * ADJ = adj_list_find(below, rectangles[i].label);
            list_node * L = ADJ->list;
            double max_choice = 0;
            if(L != NULL) {
                while(L != NULL) {
                    for(int j=0; j<size; j++) {
                        if(rectangles[j].label == L->label) {
                            if(rectangles[j].y_f > max_choice) {
                                max_choice = rectangles[j].y_f;
                            }
                        }
                    }
                    L = L->next;
                }
            }
            rectangles[i].y_0 = max_choice;
            rectangles[i].y_f = rectangles[i].y_0 + rectangles[i].height;
        }
    }
}
void label_sort(rectangle * arr, int lb, int ub) {
    rectangle tmp;
    for(int i=ub; i > lb; i--) {
        if(arr[i].label < arr[i-1].label) {
            tmp = arr[i];
            arr[i] = arr[i-1];
            arr[i-1] = tmp;
        }
    }
    for(int i=lb+2; i<=ub; i++) {
        int j = i;
        rectangle piv = arr[i];
        while(piv.label < arr[j-1].label) {
            arr[j] = arr[j-1]; j--;
        }
        arr[j] = piv;
    }
}

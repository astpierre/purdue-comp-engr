#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "avl_tree.h"

// Macros + definitions
#define RIGHT 1
#define LEFT 0
#define ERROR_CODE 0
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

// Functions
/* Create an AVL node and return its address */
avl_node * create_avl_node( int data ) {
    avl_node * new_node = NULL;
    new_node = (avl_node *)malloc(sizeof(avl_node));
    if(new_node == NULL) {
        printf("Err: bad malloc creating new avl node.\n");
        return NULL;
    }

    /* Initialize all fields */
    new_node->l_child = NULL;
    new_node->r_child = NULL;
    new_node->data = data;
    new_node->height = 0;
    return new_node;
}

/* Perform necesarry rotations on tn to restore AVL property. */
avl_node * avl_rebalance( avl_node * tn ) {
    if(tn == NULL) return NULL;
    /* Update the height of AVL tree */
    tn->height = MAX(height_avl(tn->l_child), height_avl(tn->r_child)) + 1;

    /* Capture balance of AVL tree */
    int balance = balance_avl(tn);

    /* Case 1: L->L */
    if((balance > 1) && (balance_avl(tn->l_child) >= 0)) return rotate_right(tn);
    /* Case 2: L->R */
    else if(balance > 1) {
        tn->l_child = rotate_left(tn->l_child);
        return rotate_right(tn);
    }
    /* Case 3: R->R */
    if((balance < -1) && (balance_avl(tn->r_child) <= 0)) return rotate_left(tn);
    /* Case 4: R->L */
    else if(balance < -1) {
        tn->r_child = rotate_right(tn->r_child);
        return rotate_left(tn);
    }
    return (tn);
}

/* Insert a single node in an AVL tree */
avl_node * insert_avl( avl_node * tn, int key ) {
    /* Recursive terminating condition */
    if(tn == NULL) {
        return create_avl_node(key);
    }

    /* Normal BST insert (recursively) */
    if(tn->data >= key) { /* Always go left when inserting a dup'. */
        tn->l_child = insert_avl(tn->l_child, key);
    } else {
        tn->r_child = insert_avl(tn->r_child, key);
    }

    /* Update the height of AVL tree */
    tn->height = MAX(height_avl(tn->l_child), height_avl(tn->r_child)) + 1;

    /* Capture balance of AVL tree */
    int balance = balance_avl(tn);

    /* Case 1: L->L */
    if((balance > 1) && (balance_avl(tn->l_child) >= 0)) return rotate_right(tn);
    /* Case 2: L->R */
    else if(balance > 1) {
        tn->l_child = rotate_left(tn->l_child);
        return rotate_right(tn);
    }
    /* Case 3: R->R */
    if((balance < -1) && (balance_avl(tn->r_child) <= 0)) return rotate_left(tn);
    /* Case 4: R->L */
    else if(balance < -1) {
        tn->r_child = rotate_right(tn->r_child);
        return rotate_left(tn);
    }
    return (tn);
}

/* Find the node with the smallest data value. */
avl_node * find_min( avl_node * tn ) {
    if(tn == NULL) return NULL;
    else if(tn->l_child == NULL) return tn;
    else return find_min(tn->l_child);
}

/* Find the node with the largest data value. */
avl_node * find_max( avl_node * tn ) {
    if(tn == NULL) return NULL;
    else if(tn->r_child == NULL) return tn;
    else return find_max(tn->r_child);
}

/* Delete a single node in an AVL tree with supplied key */
avl_node * delete_avl( avl_node * tn, int key ) {
    avl_node * temp = NULL;

    if(tn == NULL) return NULL;

    else if(key > tn->data) { /* Searching right children. */
        tn->r_child = delete_avl(tn->r_child, key);
        tn->height = MAX(height_avl(tn->l_child), height_avl(tn->r_child)) + 1;
        if(balance_avl(tn) > 1) {
            if(balance_avl(tn->l_child) >= 0) tn = rotate_right(tn);
            else {
                tn->l_child = rotate_left(tn->l_child);
                tn = rotate_right(tn);
            }
        } else if(balance_avl(tn) < -1) {
            if(balance_avl(tn->r_child) <= 0) tn = rotate_left(tn);
            else {
                tn->r_child = rotate_right(tn->r_child);
                tn = rotate_left(tn);
            }
        }
    } else if(key < tn->data) { /* Searching left children. */
        tn->l_child = delete_avl(tn->l_child, key);
        tn->height = MAX(height_avl(tn->l_child), height_avl(tn->r_child)) + 1;
        if(balance_avl(tn) < -1) {
            if(balance_avl(tn->r_child) <= 0) tn = rotate_left(tn);
            else {
                tn->r_child = rotate_right(tn->r_child);
                tn = rotate_left(tn);
            }
        }
    } else { /* We found the node, let's re-balance. */
        if(tn->l_child && tn->r_child) { /* Case 1: two children */
            temp = find_max(tn->l_child); // Replace w/ imm. predecessor
            tn->data = temp->data;
            tn->l_child = delete_avl(tn->l_child, tn->data);
        } else { /* Case 2: one or no children */
            temp = tn;
            if((tn->l_child == NULL) && (tn->r_child == NULL)) tn = NULL;
            else if((tn->l_child == NULL) && (tn->r_child != NULL)) tn=tn->r_child;
            else if((tn->l_child != NULL) && (tn->r_child == NULL)) tn=tn->l_child;
            free(temp);
            temp=NULL;
        }
    }
    if(tn == NULL) return NULL;
    else tn->height = MAX(height_avl(tn->l_child), height_avl(tn->r_child)) + 1;
    tn = avl_rebalance(tn);
    return tn;
}

/* Print an avl tree in inorder traversal */
void display_avl( avl_node * tn ) {
    if(tn == NULL) return;

    /* Get the pattern (TODO: use bits in a char). */
    int pattern = 0;
    if(tn->l_child != NULL) pattern += 2;
    if(tn->r_child != NULL) pattern += 1;

    /* Display and continue traversing. */
    printf("\t( %d )\t( %d )\n", tn->data, pattern);
    display_avl(tn->l_child);
    display_avl(tn->r_child);
}

/* Write avl tree to a file in binary format w. preorder fashion */
void write_avl_to_file( avl_node * tn, char * filename ) {
    /* Check terminating condition. */
    if(tn == NULL) return;

    /* Open our instruction file. */
    FILE * fptr = fopen(filename, "ab");
    if(fptr == NULL) {
        fclose(fptr);
        printf("%d\n", ERROR_CODE);
        return;
    }

    /* File writing variables / helpers. */
    char pattern = 0x00000000;
    if(tn->l_child != NULL) pattern |= 0x00000002;
    if(tn->r_child != NULL) pattern |= 0x00000001;

    /* Write and continue traversing. */
    fwrite((const void *)&(tn->data), sizeof(int), 1, fptr);
    fwrite((const void *)&(pattern), sizeof(char), 1, fptr);
    fclose(fptr);
    write_avl_to_file( tn->l_child, filename );
    write_avl_to_file( tn->r_child, filename );
}

/* Delete an AVL tree, freeing all memory */
void free_avl( avl_node * tn ) {
    if(tn == NULL) return;
    free_avl(tn->l_child);
    free_avl(tn->r_child);
    free(tn);
}

/* Return the height of AVL node */
int height_avl( avl_node * tn ) {
    if(tn == NULL) return -1;
    else return tn->height;
}

/* Get balance of AVL node */
int balance_avl( avl_node * tn ) {
    if(tn == NULL) { return 0; }
    return (height_avl(tn->l_child) - height_avl(tn->r_child));
}

/* Rotate left */
avl_node * rotate_left(avl_node * tn) {
    avl_node * tn_rc = tn->r_child;
    avl_node * tn_rc_lc = tn_rc->l_child;
    tn_rc->l_child = tn;
    tn_rc->l_child->r_child = tn_rc_lc;
    tn_rc->l_child->height = MAX(height_avl(tn_rc->l_child->l_child), height_avl(tn_rc->l_child->r_child)) + 1;
    tn_rc->height = MAX(height_avl(tn_rc->l_child), height_avl(tn_rc->r_child)) + 1;
    return tn_rc; /* new root */
}

/* Rotate right */
avl_node * rotate_right(avl_node * tn) {
    avl_node * tn_lc = tn->l_child;
    avl_node * tn_lc_rc = tn_lc->r_child;
    tn_lc->r_child = tn;
    tn_lc->r_child->l_child = tn_lc_rc;
    tn_lc->r_child->height = MAX(height_avl(tn_lc->r_child->l_child), height_avl(tn_lc->r_child->r_child)) + 1;
    tn_lc->height = MAX(height_avl(tn_lc->l_child), height_avl(tn_lc->r_child)) + 1;
    return tn_lc; /* new root */
}

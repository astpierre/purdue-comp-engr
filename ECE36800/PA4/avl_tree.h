#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

// Tree node type definitions
struct tNode {
	struct tNode * r_child;
	struct tNode * l_child;
    int data;
	int height;
};
typedef struct tNode avl_node;

// AVL tree function signatures
avl_node * create_avl_node( int data );
avl_node * insert_avl( avl_node * tn, int key );
avl_node * delete_avl( avl_node * tn, int key );
int height_avl( avl_node * tn );
int balance_avl( avl_node * tn );
avl_node * avl_rebalance( avl_node * tn );
avl_node * rotate_left( avl_node * tn );
avl_node * rotate_right( avl_node * tn );
avl_node * find_min( avl_node * tn );
avl_node * find_min( avl_node * tn );
void write_avl_to_file( avl_node * tn, char * filename );
void display_avl( avl_node * tn );
void free_avl( avl_node * tn );


#endif /* __AVL_TREE_H__ */

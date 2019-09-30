#ifndef __SEQPAIR_H__
#define __SEQPAIR_H__
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Global variable
int NUMRECTANGLES;

// Rectangle type definition
struct rectangle {
	int label;
	double width;
    double height;
	double h_sum;
	double v_sum;
	double x_0;
	double x_f;
	double y_0;
	double y_f;
};
typedef struct rectangle rectangle;

// List node type definition
struct list_node {
	int label;
	struct list_node * next;
};
typedef struct list_node list_node;

// List node type definition
struct adj_list_node {
	list_node * list;
	int label;
	struct adj_list_node * next;
};
typedef struct adj_list_node adj_list_node;

// Rectangle methods
void init_rectangle( rectangle * r, int l, double w, double h );
void topo_horiz(rectangle * rectangles, adj_list_node * horizontal_list);
void topo_vert(rectangle * rectangles, adj_list_node * vertical_list);
void generate_horizontal_adj_lists( int * seq0, int * seq1, adj_list_node ** before, adj_list_node ** after);
void generate_vertical_adj_lists( int * seq0, int * seq1, adj_list_node ** below, adj_list_node ** above );
void calc_horiz(rectangle * rectangles, adj_list_node * before, adj_list_node * after);
void calc_vert(rectangle * rectangles, adj_list_node * before, adj_list_node * after);
void label_sort(rectangle * arr, int lb, int ub);

// Linked list methods
list_node * list_node_create(int label);
void list_free(list_node * head);
void list_delete_value(list_node ** head, int v);
void list_insert(list_node ** head, int v);
bool list_search(list_node * head, int v);
void list_print(list_node * head);

// Adjacency list methods
void adj_list_delete_value(adj_list_node ** head, int v);
void adj_list_insert(adj_list_node ** head, int label);
void adj_list_print(adj_list_node * head);
adj_list_node * adj_list_find(adj_list_node * head, int label);
void adj_list_free(adj_list_node * head);

#endif /* __SEQPAIR_H__ */

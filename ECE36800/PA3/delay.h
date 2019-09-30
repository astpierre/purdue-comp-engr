#ifndef __DELAY_H__
#define __DELAY_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

// Tree node type definitions
struct tNode {
	struct tNode * rightChild;
	struct tNode * leftChild;
    struct tNode * parent;
    int sinkLabel;
    bool isSink;
	double leftWireLen;
    double rightWireLen;
    double sinkNodeCapacitance;
	double nodeCapacitance;
	double nodeResistance;
	double delay;
};
typedef struct tNode treeNode;

// Linked list type definitions
struct lNode {
	struct lNode * next;
	treeNode * tn;
};
typedef struct lNode list_t;
// List functions
list_t * CreateListNode(treeNode * tn);
void list_append(list_t * head, list_t * ln);
void FreeLinkedList(list_t * head);

// Stack type definitions
struct stack {
	treeNode * tn;
	struct stack * next;
};
typedef struct stack stackNode;

// Stack functions
void stack_init(stackNode ** sptr);
bool stack_empty(stackNode ** sptr);
treeNode * stack_peek(stackNode ** sptr);
stackNode * stack_pop(stackNode ** sptr);
stackNode * stack_push(stackNode ** sptr, treeNode ** tn);
void stack_free(stackNode ** sptr);

// Tree functions
treeNode * MakeTreeNode(double leftWireLen, double rightWireLen);
treeNode * MakeTreeSinkNode(int sinkLabel, double sinkNodeCapacitance);
void FreeBinaryTree(treeNode * root);

// RC Tree functions
void BinaryTreeReCreate(char * input_filename, char * output_filename1, char * output_filename2);
void postorderTraversal(treeNode * tn, double r_pul, double r_src, list_t ** head);
void UpdateChildren(treeNode * tn, double value);
void CalculateDelays(treeNode * tn, double r_pul, double r_src, list_t * head);
void BinaryTreePreOrderPrint(treeNode * tn);
void PrintDelays(treeNode * tn);
void WriteDelays(treeNode ** root, char * output_filename2);
void BinaryTreePreOrderWrite(treeNode * root, char * output_filename1);

#endif /* __DELAY_H__ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "delay.h"

// Macros + definitions
#define RIGHT 1
#define LEFT 0

// Helper functions
int getNumLines(char * filename) {
    FILE * fptr;
    int ctr = 0;
    fptr = fopen(filename, "r");
    char chr = '\0';
    while(chr != EOF) {
        chr=getc(fptr);
        if(chr == '\n') ctr+=1;
    }
    fclose(fptr);
    return ctr;
}

// Recreates tree and returns root
void BinaryTreeReCreate(char * input_filename, char * output_filename1, char * output_filename2) {
    // Open the input file and get the following
    double r_src = 0.0; // output resistance at source
    double r_pul = 0.0; // resistance per unit length
    double c_pul = 0.0; // capacitance per unit length

    // Save the number of lines in the file
    int numLines = getNumLines(input_filename);

    FILE * fptr = fopen(input_filename, "r");
    if(fptr == NULL) { // Check for error
        printf("Bad input filename\n");
        fclose(fptr);
        return;
    }

    // Read line 1 for source resistance and unit length R & C
    fseek(fptr, 0, SEEK_SET);
    fscanf(fptr, "%le %le %le\n", &r_src, &r_pul, &c_pul);

    // Temporary store variables
    double tmpLeftWireLen = 0.00;
    double tmpRightWireLen = 0.00;
    double tmpSinkCapacitance = 0.00;
    int tmpSinkLabel = 0;

    // Storing all nodes in a stack for reconstruction
    stackNode * nodeStack = NULL;
    stack_init(&nodeStack);
    treeNode * temp = NULL;

    int i = 0;
    while(i < numLines-1) { // read each line after the first
        char tmp = '\0';
        fread(&tmp, sizeof(tmp), 1, fptr);
        if(tmp == '(') { // NOT a sink node!
            fseek(fptr, -1, SEEK_CUR); // Rewind a char
            fscanf(fptr, "(%le %le)\n", &tmpLeftWireLen, &tmpRightWireLen);
            temp = MakeTreeNode(tmpLeftWireLen, tmpRightWireLen);
            nodeStack = stack_push(&nodeStack, &temp);
        }
        else { // Sink node!
            fseek(fptr, -1, SEEK_CUR); // Rewind a char
            fscanf(fptr, "%d(%le)\n", &tmpSinkLabel, &tmpSinkCapacitance);
            temp = MakeTreeSinkNode(tmpSinkLabel, tmpSinkCapacitance);
            nodeStack = stack_push(&nodeStack, &temp);
        }
        i+=1; // Incr ctr
    }
    // Done with the input file
    fclose(fptr);

    // The root is the first item on the stack given postorder traversal
    treeNode * root = NULL;
    root = stack_peek(&nodeStack);
    nodeStack = stack_pop(&nodeStack);
    root->nodeCapacitance = (((c_pul * root->leftWireLen)/2.0) +
                            ((c_pul * root->rightWireLen)/2.0));
    root->nodeResistance = 0.00;
    int side = RIGHT;

    // Initialize a stack to handle parents
    stackNode * parentStack = NULL;
    stack_init(&parentStack);
    parentStack = stack_push(&parentStack, &root);

    // Initialize the list of all treenodes
    list_t * nodeList = CreateListNode(root);

    // Construct the tree
    while(stack_empty(&nodeStack) != true) {
        treeNode * tn = NULL;
        tn = stack_peek(&nodeStack);
        nodeStack = stack_pop(&nodeStack);
        list_append(nodeList, CreateListNode(tn));
        if(side == RIGHT) { // insert at rightchild
            tn->parent = stack_peek(&parentStack);
            stack_peek(&parentStack)->rightChild = tn;
            if(tn->isSink == true) {
                tn->nodeCapacitance = ((c_pul * tn->parent->rightWireLen)/2.0 +
                                      tn->sinkNodeCapacitance);
                side = LEFT;
            } else {
                tn->nodeCapacitance = ((c_pul * tn->parent->rightWireLen)/2.0 +
                                      (c_pul * tn->leftWireLen)/2.0 +
                                      (c_pul * tn->rightWireLen)/2.0);
                parentStack = stack_push(&parentStack, &tn);
            }
        } else if(side == LEFT) { // insert at leftchild
            tn->parent = stack_peek(&parentStack);
            stack_peek(&parentStack)->leftChild = tn;
            if(tn->isSink == true) {
                tn->nodeCapacitance = ((c_pul * tn->parent->leftWireLen)/2.0 +
                                      tn->sinkNodeCapacitance);
                parentStack = stack_pop(&parentStack);
            } else {
                tn->nodeCapacitance = ((c_pul * tn->parent->leftWireLen)/2.0 +
                                      (c_pul * tn->leftWireLen)/2.0 +
                                      (c_pul * tn->rightWireLen)/2.0);
                parentStack = stack_push(&parentStack, &tn);
                side = RIGHT;
            }
        }
    }

    // Print the preorder traversal of binary search tree
    //BinaryTreePreOrderPrint(root);
    BinaryTreePreOrderWrite(root, output_filename1);

    // Calculate the delays at each of the leaf node
    CalculateDelays(root, r_pul, r_src, nodeList);

    // Print the delay of each leaf node
    //PrintDelays(root);
    WriteDelays(&root, output_filename2);

    // Free memory
    stack_free(&nodeStack);
    stack_free(&parentStack);
    FreeLinkedList(nodeList);
    //FreeBinaryTree(root);
    return;
}

/* Printer for debugging */
void DebugPrint(treeNode * tn) {
	if(tn == NULL) return;
    if(tn->isSink) {
        printf("\t%d(R=%le)(D=%le)\n",tn->sinkLabel, tn->nodeResistance, tn->delay);
    } else {
        printf("\t(%le %le)(R=%le)\n", tn->leftWireLen, tn->rightWireLen, tn->nodeResistance);
    }
    DebugPrint(tn->leftChild);
    DebugPrint(tn->rightChild);
}

/* Helper for the postorderTraversal to calculate delays */
void UpdateChildren(treeNode * tn, double value) {
    if(tn == NULL) return;
    UpdateChildren(tn->leftChild, value);
    UpdateChildren(tn->rightChild, value);
    tn->nodeResistance += value;
    return;
}

/* CalculateDelays recursive call */
void postorderTraversal(treeNode * tn, double r_pul, double r_src, list_t ** head) {
    if(tn == NULL) return;

    double updateValue = 0.00;
    if(tn->parent == NULL) {
        updateValue = r_src;
        UpdateChildren(tn, updateValue);
    } else if(tn->parent->rightChild == tn) {
        updateValue = tn->parent->rightWireLen * r_pul;
        UpdateChildren(tn, updateValue);
    } else if(tn->parent->leftChild == tn) {
        updateValue = tn->parent->leftWireLen * r_pul;
        UpdateChildren(tn, updateValue);
    } else printf("ERR, not finding correct parent...\n");

    postorderTraversal(tn->leftChild, r_pul, r_src, head);
    postorderTraversal(tn->rightChild, r_pul, r_src, head);

    if(tn->isSink) {
        // Calculate delay for sink node
        double divisor = tn->nodeResistance;
        double numerator = 0.00;
        double resistanceSquared = 0.0;
        list_t * tmp = *head;
        while(tmp != NULL) {
            resistanceSquared = pow(tmp->tn->nodeResistance, 2.0);
            numerator += tmp->tn->nodeCapacitance * resistanceSquared;
            tmp = tmp->next;
        }
        tn->delay = numerator / divisor;
    }

    // Update all the children (and self) removing most recent change
    UpdateChildren(tn, -updateValue);

    return;
}

/* Calculate delays at each leaf-node */
void CalculateDelays(treeNode * tn, double r_pul, double r_src, list_t * head) {
    treeNode * root = tn;
    postorderTraversal(root, r_pul, r_src, &head);
    return;
}

/* Print delays of leaf nodes in preorder fashion */
void PrintDelays(treeNode * tn) {
	if(tn == NULL) return;
    if(tn->isSink) {
        printf("%d(%le)\n",tn->sinkLabel, tn->delay);
    }
    PrintDelays(tn->leftChild);
    PrintDelays(tn->rightChild);
}

/* Print tree topology in preorder fashion */
void BinaryTreePreOrderPrint(treeNode * tn) {
	if(tn == NULL) return;
    if(tn->isSink) {
        printf("\t%d(%le)\n",tn->sinkLabel, tn->sinkNodeCapacitance);
    } else {
        printf("\t(%le %le)\n", tn->leftWireLen, tn->rightWireLen);
    }
    BinaryTreePreOrderPrint(tn->leftChild);
    BinaryTreePreOrderPrint(tn->rightChild);
}

/* Write tree topology in preorder fashion to output_filename1 */
void BinaryTreePreOrderWrite(treeNode * tn, char * output_filename1) {
	if(tn == NULL) return;

    FILE * fptr = fopen(output_filename1, "a");
    if(fptr==NULL) {  printf("Err opening output_filename1\n"); fclose(fptr); return;  }

    if(tn->isSink) {
        fprintf(fptr, "%d(%le)\n",tn->sinkLabel, tn->sinkNodeCapacitance);
        fclose(fptr);
    } else {
        fprintf(fptr, "(%le %le)\n",tn->leftWireLen, tn->rightWireLen);
        fclose(fptr);
    }
    BinaryTreePreOrderWrite(tn->leftChild, output_filename1);
    BinaryTreePreOrderWrite(tn->rightChild, output_filename1);
}

/* Write the delays of each leaf node in preorder fashion */
void WriteDelays(treeNode ** tn, char * output_filename2) {
    if((*tn) == NULL) return;
    if((*tn)->isSink) {
        FILE * fptr = fopen(output_filename2, "ab+");
        if(fptr==NULL) {  printf("Err opening output_filename2\n"); return;  }
        int sinkLabel_tmp = (*tn)->sinkLabel;
        double delay_tmp = (*tn)->delay;
        fwrite((const void *)&sinkLabel_tmp, sizeof(int), 1, fptr);
        fwrite((const void *)&delay_tmp, sizeof(double), 1, fptr);
        fclose(fptr);
    }
    WriteDelays(&((*tn)->leftChild), output_filename2);
    WriteDelays(&((*tn)->rightChild), output_filename2);
}

/* Stack functions */
void stack_free(stackNode ** sptr) {
    if(*sptr==NULL) return;
    stackNode * tmp;
    tmp = *sptr;
    while(tmp != NULL) {
        *sptr = tmp->next;
        free(tmp);
        tmp=*sptr;
    }
    return;
}
void stack_init(stackNode ** sptr) {
    *sptr = NULL;
}
bool stack_empty(stackNode ** sptr) {
    if(*sptr == NULL) return true;
    else return false;
}
stackNode * stack_push(stackNode ** sptr, treeNode ** tn) {
    stackNode * tmp = (stackNode *)malloc(sizeof(stackNode));
    if(tmp == NULL) printf("ERR malloc stackNode\n");
    tmp->tn = *tn;
    tmp->next = *sptr;
    *sptr = tmp;
    return *sptr;
}
treeNode * stack_peek(stackNode ** sptr) {
    return (*sptr)->tn;
}
stackNode * stack_pop(stackNode ** sptr) {
    stackNode * tmp = *sptr;
    *sptr = (*sptr)->next;
    free(tmp);
    return *sptr;
}

/* Linked list functions */
void list_append(list_t * head, list_t * ln) {
    if(head->next == NULL) head->next = ln;
    else {
        list_t * curr = head;
        while(true) {
            if(curr->next == NULL) {
                curr->next = ln;
                break;
            }
            curr = curr->next;
        }
    }
}
list_t * CreateListNode(treeNode * tn) {
    list_t * newNode = malloc(sizeof(list_t));
    newNode->tn = tn;
    newNode->next = NULL;
    return newNode;
}
void FreeLinkedList(list_t * head) {
    list_t * current = head;
    while(current != NULL) {
        head = current->next;
        free(current->tn);
        free(current);
        current = head;
    }
    free(head);
}

/* Tree functions */
treeNode * MakeTreeNode(double leftWireLen, double rightWireLen) {
    treeNode * newNode = NULL;
    newNode = (treeNode *)malloc(sizeof(treeNode));
    if(newNode == NULL) {
        printf("ERROR MALLOC FOR NEW TREENODE\n");
        return NULL;
    }
    newNode->leftWireLen = leftWireLen;
    newNode->rightWireLen = rightWireLen;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->isSink = false;
    newNode->parent = NULL;
    newNode->sinkLabel = -1;
    newNode->sinkNodeCapacitance = 0.00;
    newNode->delay = 0.00;
    newNode->nodeCapacitance = 0.00;
    newNode->nodeResistance = 0.00;
    return newNode;
}
treeNode * MakeTreeSinkNode(int sinkLabel, double sinkNodeCapacitance) {
    treeNode * newNode = NULL;
    newNode = (treeNode *)malloc(sizeof(treeNode));
    if(newNode == NULL) {
        printf("ERROR MALLOC FOR NEW SINKTREENODE\n");
        return NULL;
    }
    newNode->leftWireLen = 0.00;
    newNode->rightWireLen = 0.00;
    newNode->parent = NULL;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->isSink = true;
    newNode->sinkLabel = sinkLabel;
    newNode->sinkNodeCapacitance = sinkNodeCapacitance;
    newNode->nodeCapacitance = 0.00;
    newNode->delay = 0.00;
    newNode->nodeResistance = 0.00;
    return newNode;
}
void FreeBinaryTree(treeNode *root) {
    if(root == NULL) return;
    FreeBinaryTree(root->leftChild);
    FreeBinaryTree(root->rightChild);
    free(root);
}

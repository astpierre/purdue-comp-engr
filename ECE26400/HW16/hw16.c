/****************** Modify this file at specified place ***********************/
#include <stdio.h>
#include <stdlib.h>
#include "hw16.h"


/******** Do Not modify the file above this line, you can modify below ********/

#ifdef TEST_FREETREE
// FreeBinaryTree
//  This function frees up the memory from the root node
void FreeBinaryTree(treeNode *root)
{
    if(root == NULL) return;
    FreeBinaryTree(root->leftChild);
    FreeBinaryTree(root->rightChild);
    free(root);
}
#endif

#ifdef TEST_SEARCH
// search
//  This function rec searches for given value in a tree returns node w val
treeNode * search(treeNode * tn, int value)
{
    treeNode * tmpNode = NULL;
    // Cannot find
    if(tn == NULL) return NULL;

    // If found return the respective node
    if(tn->value == value) return tn;

    tmpNode = search(tn->leftChild,value);
    if(tmpNode != NULL) return tmpNode;
    tmpNode = search(tn->rightChild,value);
    if(tmpNode != NULL) return tmpNode;
    return NULL;
}
#endif


#ifdef TEST_SUBTREE
// isSubTree
//  This function checks if 'needle' is subtree of 'haystack'
bool isSubTree(treeNode * haystack, treeNode * needle)
{
    // Base case checks
    if(needle == NULL) return true;
    if(haystack == NULL) return false;

    // Checking if all the values of 'needle' are in 'haystack'
    if(haystack->value == needle->value)
    {
        return  ( 
                isSubTree(haystack->leftChild,needle->leftChild) &&
                isSubTree(haystack->rightChild,needle->rightChild)
                );
    }
    return false;
}
#endif


#ifdef TEST_CONTAINED
bool isContained(treeNode * haystack, treeNode * needle)
{
    // Search for the part of haystack where root of needle starts
    treeNode * tmpHS = NULL;
    tmpHS = search(haystack, needle->value);
    if(tmpHS == NULL) return false;

    // Return the result of helper function
    return(isSubTree(tmpHS,needle));
}
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

#ifdef TEST_MAIN
// Destroys a binary tree
void treeDestroy(treeNode * tn)
{
    if(tn == NULL) return;
    treeDestroy(tn->leftChild);
    treeDestroy(tn->rightChild);
    free(tn);
}

// Count the number of integers in a given file
int countFromFile(char * file_name)
{
    FILE * fptr = fopen(file_name, "r");
    if(fptr==NULL) return EXIT_FAILURE;
    int value=0, count=1;
    while(fscanf(fptr,"%d",&value)==1) count++;
    fclose(fptr);
    return count;
}

// Fill an array with count integers from a file
void fillArray(int * arr, int count, char * file_name)
{
    FILE * fptr = fopen(file_name, "r");
    if(fptr==NULL) return;
    int ind=0;
    while(ind<count)
    {
        if(fscanf(fptr,"%d",&arr[ind]) != 1)
        {  fclose(fptr); free(arr);  }
        ind++;
    }
    fclose(fptr);
}

// Return the last entry in a file to a location * val
void getLastEntry(int * val, int count, char * file_name)
{
    FILE * fptr = fopen(file_name, "r");
    if(fptr==NULL) return;
    int ind=0;
    while(ind<count)
    {
        if(fscanf(fptr,"%d",&val[0]) != 1)
        {  fclose(fptr); free(val);  }
        ind++;
    }
    fclose(fptr);
}

// Main entrance point for program
int main(int argc, char **argv)
{
    // Check input arguments
    if(argc != 2) return EXIT_FAILURE;

    // Count the number of integers in the input file
    int count = countFromFile(argv[1]);
    
    // Fill an array with all the integers (except the last one)
    int * arr = malloc(sizeof(int)*(count-1));
    if(arr==NULL) return EXIT_FAILURE;
    fillArray(arr,count-1,argv[1]);

    // The last entry is the search query
    int * search_query = malloc(sizeof(int)*1);
    if(arr==NULL) return EXIT_FAILURE;
    getLastEntry(search_query,1,argv[1]);

    // Create a binary search tree from the numbers in input file
    treeNode * t = CreateBST(arr,arr[0],0,count-2);

    // Print the tree in IN-ORDER fasion
    BinaryTreeInOrderPrint(t);

    // Compute the distance of the 'search_query' node
    FindDistance(t, search_query[0], 0);
    //if(distance == -1) PrintDistance(-1);

    // Print the distance of the node from the root node
    //PrintDistance(distance);

    // Free all memory
    treeDestroy(t);
    free(arr);
    free(search_query);
    return EXIT_SUCCESS; 
}
#endif

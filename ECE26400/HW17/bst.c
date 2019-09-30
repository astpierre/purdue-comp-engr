#include "bst.h"
///***** DO NOT MODIFY THIS FUNCTION ******/////
#ifdef TEST_PRINT
void PrintDistance(int distance)
{

    printf("\n%d\n",distance);

}
///***** DO NOT MODIFY THIS FUNCTION ******/////
void BinaryTreePrint(treeNode* tn)
{
        printf("Pre Order print of the Tree is: \n");
        BinaryTreePreOrderPrint(tn);
        printf("\nIn Order print of the Tree is: \n");
        BinaryTreeInOrderPrint(tn);
        printf("\nPost Order print of the Tree is: \n");
        BinaryTreePostOrderPrint(tn);
        printf("\n");
}
///***** DO NOT MODIFY THIS FUNCTION ******/////
// print the tree in pre order fashion
void BinaryTreePreOrderPrint(treeNode* tn)
{
        if(tn == NULL)
                return;
        printf("%d ",tn->value );
        BinaryTreePreOrderPrint(tn->leftChild);
        BinaryTreePreOrderPrint(tn->rightChild);
}
///***** DO NOT MODIFY THIS FUNCTION ******/////
// print the tree in in order fashion
void BinaryTreeInOrderPrint(treeNode* tn)
{
        if(tn == NULL)
                return;
        BinaryTreeInOrderPrint(tn->leftChild);
        printf("%d ",tn->value );
        BinaryTreeInOrderPrint(tn->rightChild);
}
///***** DO NOT MODIFY THIS FUNCTION ******/////
// print the tree in post order fashion
void BinaryTreePostOrderPrint(treeNode *tn)
{
        if(tn == NULL)
                return;
        BinaryTreePostOrderPrint(tn->leftChild);
        BinaryTreePostOrderPrint(tn->rightChild);
        printf("%d ",tn->value );
}
#endif

// Calculates dist of a node from the root
//  Given: tree and value to search
#ifdef TEST_DIST
treeNode * search(treeNode * tn, int val, int d)
{
    treeNode * tmpNode = NULL;
    // cannot find
    if(tn == NULL) return NULL;
    if(tn->value == val)
    {  PrintDistance(d); return tmpNode;  }
    tmpNode = search(tn->leftChild,val,d+1);
    if(tmpNode != NULL) return tmpNode;
    //{  PrintDistance(d); return tmpNode;  }
    tmpNode = search(tn->rightChild,val,d+1);
    if(tmpNode != NULL) return tmpNode;
    //{  PrintDistance(d); return tmpNode;  }
    return NULL;
}
/*int DistanceHelper(treeNode * tn, int val, int d)
{
    // IF SEARCH !IN TREE: return EXIT_FAILURE
    if(tn == NULL) return -1;
    // IF SEARCH FOUND: RETURN DISTANCE
    if(tn->value == val) return d;
    // ELSE: SEARCH LEFT, CHECK IF RETURN VAL > -1
    int check_L = DistanceHelper(tn->leftChild,val,d+1);
    if(check_L != -1) return check_L;
    // ELSE: SEARCH RIGHT, CHECK IF RETURN VAL > -1
    int check_R = DistanceHelper(tn->rightChild,val,d+1);
    return check_R;
    
    //return d;
}*/
int FindDistance(treeNode * t, int search_query, int distance)
{
    // Search for the value in the haystack
    treeNode * tmpHS = NULL;
    tmpHS = search(t,search_query,0);
    if(tmpHS == NULL) PrintDistance(-1);
    return 0;
}
#endif

#ifdef TEST_CREATEBST
// Constructs a new TreeNode
static treeNode * ConstructTreeNode(int value)
{
    treeNode * newNode;
    newNode = malloc(sizeof(treeNode));
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->value = value;
    return newNode;
}

// Inserts a value in BST as a new node
treeNode * InsertBST(treeNode * tn, int value)
{
    if(tn == NULL) 
    {
        // Create a new node
        return ConstructTreeNode(value);
    }

    // Do not insert same value twice
    if(tn->value == value) return tn;
    // If value < node
    if(tn->value > value) tn->leftChild = InsertBST(tn->leftChild, value);
    else if(tn->value < value) tn->rightChild = InsertBST(tn->rightChild, value);
    return tn;
}

// Creates a BST based on array
treeNode * CreateBST(int * a,int root, int start, int end)
{
    // Create a new node, alloc mem, assign val of root
    treeNode * newNode = ConstructTreeNode(root);

    // Insert the rest of the nodes into the BST
    for(int i=1; i<end; i++) newNode = InsertBST(newNode, a[i]);
    
    return newNode;
}
#endif

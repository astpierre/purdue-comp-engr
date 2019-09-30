// Compute the maximum depth of a tree
int maxDepth(treeNode * root)
{
    if(root==NULL) return(0);
    else
    {
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        // Return the larger
        if(leftDepth > rightDepth) return(leftDepth+1);
        else return(rightDepth+1);
    }
}

// Given a binary search tree, return the min data value found in tree
int minValueBST(treeNode * root)
{
    treeNode * current = root;
    while(current->left != NULL) current=current->left;
    return(current->data);
}

// Given a binar tree, print its nodes according to the "bottom-up" postorder
void printTree(treeNode * root)
{
    if(root==NULL) return;
    printTree(root->left);
    printf("%d\n",root->data);
    printTree(root->right);
}
void printPostOrder(treeNode * root)
{
    if(root==NULL) return;
    // First, recurse on both subtrees
    printTree(root->left);
    printTree(root->right);
    printf("%d\n", root->data);
}

// Given two trees, return 1 if they are structurally identical
int sameTree(treeNode * rootA, treeNode * rootB)
{
    if(rootA==NULL && rootB==NULL) return(1);
    else if(rootA!=NULL && rootB!=NULL)
    {
        return(rootA->data==rootB->data &&
                sameTree(rootA->left,rootB->left) &&
                sameTree(rootA->right,rootB->right));
    }
    else return(0);
}

// Returns true if a binary tree is a binary search tree
int isBST(treeNode * root)
{
    if(root==NULL) return(1);
    if(root->left!=NULL && maxValue(root->left) > root->data) return(0);
    if(root->right!=NULL && maxValue(root->right) <= root->data) return(0);
    if(!isBST(root->left) || !isBST(root->right)) return(0);
    return(1);
}

// Modify this file at said locations
#include "decode.h"
#include "list.h"
#include "utility.h"

#ifdef TEST_READHEADER
int CountNodes(ListNode * head)
{
  int nodes = 0;
  while(head != NULL)
  {  head=head->next; nodes++;  }
  return nodes;
}

ListNode * PopLList(ListNode * head)
{
  ListNode * list_pop = head;
  if (head->next != NULL) *head = *head->next;
  return list_pop;
}

TreeNode * readHeader(FILE * infptr)
{
  TreeNode * tree_head = NULL;
  TreeNode * tempTreeNode = NULL;
  TreeNode * tempTreeNodeL = NULL;
  TreeNode * tempTreeNodeR = NULL;
  ListNode * list_head = ListNode_create(tree_head);
  ListNode * tempListNode = NULL;
  ListNode * tempListNodeL = NULL;
  ListNode * tempListNodeR = NULL;
  unsigned char bit=0, whichbit=0, curbyte = 0, packet=0x00;
  unsigned int i;

  while(readBit(infptr, &bit, &whichbit, &curbyte) != -1)
  {
    if(bit == 1)
    {
      // Clear the packet
      packet=0;
      // Mask the packet
      for(i=0;i<8;i++)
      {
        readBit(infptr, &bit, &whichbit, &curbyte);
        packet |= ((0x01&bit) << (whichbit));
      }
      printf("%c\n",packet);
      tempTreeNode = TreeNode_create((unsigned char)packet, 0);
      tempListNode = ListNode_create(tempTreeNode);
      list_head = List_insert(list_head,tempListNode);
    }
    else if(bit == 0)
    {
      // If length of list == 1, return tree_head
      if(CountNodes(list_head) == 1) return list_head->tnptr;
      else if(CountNodes(list_head) > 1)
      {
        // Remove two nodes from linked list
        tempListNodeR = PopLList(list_head);
        tempListNodeL = PopLList(list_head);
        tempTreeNodeR = tempListNodeR->tnptr;
        tempTreeNodeL = tempListNodeL->tnptr;
        // Create parent tree node
        tempTreeNode = Tree_merge(tempTreeNodeL, tempTreeNodeR);
        // Add parent to linked list
        list_head = List_insert(list_head,ListNode_create(tempTreeNode));
      }
    }
  }
  return list_head->tnptr;
}
#endif


#ifdef TEST_DECODE

int decode(char * infile, char * outfile)
{
  // Read the header from input file
  FILE * finput = fopen(infile,"r");
  if(finput==NULL) return EXIT_FAILURE;
  TreeNode * tn_input = readHeader(finput);
  // Print generated tree from the header to outfile
  FILE * foutput = fopen(outfile,"w");
  if(foutput==NULL) return EXIT_FAILURE;
  Tree_print(tn_input, foutput);

  // Read the next four bytes from header (number of chars in file)
  int numChars = 0;
  if(fscanf(finput,"%d",&numChars)!=1) return EXIT_FAILURE;
  PrintNumberChar(numChars, foutput);
  return EXIT_SUCCESS;
}
#endif

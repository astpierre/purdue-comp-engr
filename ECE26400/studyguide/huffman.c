// main.c
#include "encode.h"
#include "constant.h"
#include <stdlib.h>
#include <string.h>
int main(int argc, char ** argv)
{
    // argv[1]: 'e'=encode, 'd'=decode
    // argv[2]: name of input file
    // argv[3]: name of output file
    if(argc!=4) return EXIT_FAILURE;
    if(strcmp(argv[1],"e") == 0) encode(argv[2],argv[3]);
    if(strcmp(argv[1],"d") == 0) decode(argv[2],argv[3]);
    return EXIT_SUCCESS;
}

// encode.h
#ifndef ENCODE_H
#define ENCODE_H
int encode(char * infile, char * outfile);
int decode(char * infile, char * outfile);
#endif

// encode.c
#include "encode.h"
#include "constant.h"
#include "freq.h"
#include "list.h"
#include "utility.h"
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <values.h>
#define ENCODEMODE 0
#define DECODEMODE 1

void buildCodeBookHelper(TreeNode * tn, int ** codebook, int * row, int col)
{
    if(tn==NULL) return;
    // Is it a leaf node?
    TreeNode * lc = tn->left;
    TreeNode * rc = tn->right;
    if((lc==NULL) && (rc==NULL))
    {
        // finish one code
        codebook[*row][0] = tn->value;
        (*row)++;
        return;
    }
    if(lc!=NULL)
    {
        // populate this column of the entire subtree
        int numRow = Tree_leaf(lc);
        int ind;
        for(ind= *row; ind<(*row)+numRow; ind++)
        {  codebook[ind][col] = 0;  }
        buildCodeBookHelper(lc,codebook,row,col+1);
    }
    if(rc!=NULL)
    {
        // populate this column of the entire subtree
        int numRow = Tree_leaf(rc);
        int ind;
        for(ind= *row; ind<(*row)+numRow; ind++)
        {  codebook[ind][col] = 1;  }
        buildCodeBookHelper(rc,codebook,row,col+1);
    }
}
void buildCodeBook(TreeNode * root, int ** codebook)
{
    int row=0;
    // col start at 1 b/c [0] stores the character
    buildCodeBookHelper(root, codebook, &row, 1);
}

int compress(char * infile, char * outfile, int ** codebook, int * mapping)
{
    FILE * infptr = fopen(infile, "r");
    FILE * outfptr = fopen(outfile, "a");
    unsigned char whichbit = 0;
    unsigned char curbyte = 0;
    while(!feof(infptr))
    {
        int onechar = fgetc(infptr);
        if(onechar != EOF)
        {
            int ind = mapping[onechar];
            int ind2 = 1;
            while(codebook[ind][ind2] != -1)
            {
                writeBit(outfptr,(codebook[ind][ind2]==1),&whichbit,&curbyte);
                ind2++;
            }
        }
    }
    padZero(outfptr, &whichbit, &curbyte);
    fclose(infptr);
    fclose(outfptr);
    return EXIT_SUCCESS;
}

static ListNode * MergeListNode(ListNode * head, int endec)
{
    ListNode * second = head->next;
    ListNode * third = second->next;
    TreeNode * tn1 = head->tnptr;
    TreeNode * tn2 = second->tnptr;
    free(head);
    free(second);
    head = third;
    TreeNode * mrg;
    if(endec == ENCODEMODE) mrg = Tree_merge(tn1,tn2);
    else mrg = Tree_merge(tn2,tn1);
    ListNode * ln = ListNode_create(mrg);
    if(endec == ENCODEMODE) head = List_insert(head, ln, SORTED);
    else head = List_insert(head, ln, STACK);
    return head;
}

static TreeNode * list2Tree(ListNode * head)
{
    while((head->next) != NULL) head=MergeListNode(head,ENCODEMODE);
    TreeNode * root = head->tnptr;
    free(head);
    return root;
}

int encode(char * infile, char * outfile)
{
    CharFreq frequencies[NUMLETTER];
    bzero(frequencies, sizeof(CharFreq)*NUMLETTER);
    unsigned int numChar = countFrequency(infile, frequencies);
    sortFrequency(frequencies);
    ListNode * head = List_build(frequencies);
    TreeNode * root = list2Tree(head);
    int numRow = Tree_leaf(root);
    int numCol = Tree_height(root);
    numCol++;
    int ** codebook = malloc(sizeof(*int)*numRow);
    int row;
    for(row=0; row<numRow; row++)
    {
        codebook[row] = malloc(sizeof(int)*numCol);
        int col;
        for(col=0; col<numCol; col++) codebook[row][col] = -1;
    }
    buildCodeBook(root, codebook);
    buildCodeBook(codebook, numRow);
    int mapping[NUMLETTER];
    int ind;
    for(ind=0; ind<NUMLETTER; ind++)
    {
        mapping[ind] = -1;
        int ind2;
        for(ind2=0; ind2<numRow; ind2++)
        {  if(codebook[ind2][0] == ind) mapping[ind] = ind2;  }
    }
    for(ind=0; ind<NUMLETTER; ind++)
    {  if(mapping[ind] != -1) printf("%c:%d\n",ind,mapping[ind]);  }
    Tree_header(root, numChar, outfile);
    compress(infile, outfile, codebook, mapping);

    for(ind=0; ind<numRow; ind++) free(codebook[ind]);
    free(codebook);
    Tree_destroy(root);
    return EXIT_SUCCESS;
}

static TreeNode * readHeader(FILE * infptr)
{
    int done = 0;
    unsigned char whichbit = 0;
    unsigned char curbyte = 0;
    unsigned char onebit = 0;
    ListNode * head = NULL;
    while(done==0)
    {
        readBit(infptr, &onebit, &whichbit, &curbyte);
        if(onebit==1)
        {
            int bitcount;
            unsigned char value=0;
            for(bitcount=0; bitcount<7; bitcount++)
            {
                value <<= 1;
                readbit(infptr, &onebit, &whichbit, &curbyte);
                value |= onebit;
            }
            TreeNode * tn = TreeNode_create(value, 0);
            ListNode * ln = ListNode_create(tn);
            head = List_insert(head, ln, STACK);
        }
        else
        {
            if(head->next == NULL) done = 1;
            else head=MergeListNode(head, DECODEMODE);
        }
    }
    TreeNode * root = head->tnptr;
    free(head);
    return root;
}

int decode(char * infile, char * outfile)
{
    FILE * infptr = fopen(infile, "r");
    TreeNode * root = readHeader(infptr);
    unsigned int numChar = 0;
    fread(&numChar, sizeof(unsigned int), 1, infptr);
    unsigned char newline;
    fread(&newline, sizeof(unsigned char), 1, infptr);
    unsigned char whichbit = 0;
    unsigned char curbyte = 0;
    unsigned char onebit = 0;
    FILE * outfptr = fopen(outfile, "w");
    while(numChar != 0)
    {
        TreeNode * tn = root;
        while((tn->left) != NULL)
        {
            readBit(infptr, &onebit, &whichbit, &curbyte);
            if(onebit == 0) tn = tn->left;
            else tn = tn->right;
        }
        printf("%c",tn->value);
        fprintf(outfptr, "%c", tn->value);
        numChar--;
    }
    Tree_destroy(root);
    fclose(infptr);
    fclose(outfptr);
    return EXIT_SUCCESS;
}

// tree.h
#ifndef TREE_H
#define TREE_H
typedef struct treenode
{
    struct treenode * left;
    struct treenode * right;
    char value;
    int freq;
} TreeNode;
TreeNode * TreeNode_create(char val, int freq);
TreeNode * Tree_merge(TreeNode * tn1, TreeNode * tn2);
int Tree_height(TreeNode * tn);
int Tree_leaf(TreeNode * tn);
void Tree_header(TreeNode * tn, unsigned int numChar, char * outfile);
void Tree_destroy(TreeNode * tn);
#endif

// tree.c
#include "tree.h"
#include "utility.h"
#incldue <stdio.h>
#include <stdlib.h>

TreeNode * TreeNode_create(char val, int freq)
{
    TreeNode * tn = malloc(sizeof(TreeNode));
    tn->left=NULL;
    tn->right=NULL;
    tn->value=val;
    tn->freq=freq;
    return tn;
}

TreeNode * Tree_merge(TreeNode * tn1, TreeNode * tn2)
{
    TreeNode * tn = malloc(sizeof(TreeNode));
    tn->left = tn1;
    tn->right = tn2;
    tn->value = 0;
    tn->freq = tn1->freq + tn2->freq;
    return tn;
}

static int Tree_heightHelper(TreeNode * tn, int height)
{
    if(tn==0) return height;
    int lh = Tree_heightHelper(tn->left, height+1);
    int rh = Tree_heightHelper(tn->right, height+1);
    if(lh < rh) return rh;
    if(rh < lh) return lh;
    return lh
}
int Tree_height(TreeNode * tn) return Tree_heightHelper(tn,0);

static void Tree_leafHelper(TreeNode * tn, int * num)
{
    if(tn==0) return;
    TreeNode * lc = tn->left;
    TreeNode * rc = tn->right;
    if((lc==NULL) && (rc==NULL))
    {  (*num)++; return;  }
    Tree_leafHelper(lc, num);
    Tree_leafHelper(rc, num);
}

int Tree_leaf(TreeNode * tn)
{
    int num = 0;
    Tree_leafHelper(tn, &num);
    return num;
}

static void char2bits(FILE * outfptr, int ch, unsigned char * whichbyte, unsigned char * curbyte)
{
    unsigned char mask = 0x40;
    while(mask > 0)
    {
        writeBit(outfptr, (ch&mask)==mask, whichbit, curbyte);
        mask >>= 1;
    }
}

static void Tree_headerHelper(TreeNode * tn, FILE * outfptr, unsigned char * whichbyte, unsigned char * curbyte)
{
    if(tn == NULL) return;
    TreeNode * lc = tn->left;
    TreeNode * rc = tn->right;
    if((lc==NULL) && (rc==NULL))
    {
        writeBit(outfptr, 1, whichbit, curbyte);
        char2bits(outfptr, tn->value, whichbit, curbyte);
        return;
    }
    Tree_headerHelper(lc, outfptr, whichbit, curbyte);
    Tree_headerHelper(rc, outfptr, whichbit, curbyte);
    writeBit(outfptr, 0, whichbit, curbyte);
}

void Tree_header(TreeNode * tn, unsigned int numChar, char * outfile)
{
    FILE * outfptr = fopen(outfile, "w");
    unsigned char whichbit = 0;
    unsigned char curbyte = 0;
    Tree_headerHelper(tn, outfptr, &whichbit, &curbyte);
    writeBit(outfptr, 0, &whichbit, &curbyte);
    padZero(outfptr, &whichbit, &curbyte);
    fwrite(&numChar, sizeof(unsigned int), 1, outfptr);
    unsigned char newline = '\n';
    fwrite(&newline, sizeof(unsigned char), 1, outfptr);
    fclose(outfptr);
}

void Tree_destroy(TreeNode * tn)
{
    if(tn == NULL) return;
    Tree_destroy(tn->left);
    Tree_destroy(tn->right);
    free(tn);
}

// list.h
#ifndef LIST_H
#define LIST_H
#include "tree.h"
#include "constant.h"
#include "freq.h"
#include <stdio.h>
#define QUEUE 0
#define STACK 1
#define SORTED 2
typedef struct listnode
{
    struct listnode * next;
    TreeNode * tnptr;
} ListNode;

ListNode * ListNode_create(TreeNode * tn);
ListNode * List_build(CharFreq * frequencies);
ListNode * List_insert(ListNode * head, ListNode * ln, int mode);
#endif

// list.c
#include "list.h"
#include "freq.h"
#include <stdlib.h>
ListNode * ListNode_create(TreeNode * tn)
{
    ListNode * ln = malloc(sizeof(ListNode));
    ln->next = NULL;
    ln->tnptr = tn;
    return ln;
}

ListNode * List_insert(ListNode * head, ListNode * ln, int mode)
{
    if(ln == NULL) return NULL;
    if(head == NULL) return ln;
    if(mode == STACK)
    {  ln->next = head; return ln;  }
    if(mode == QUEUE)
    {  ln->next = List_insert(head->next,ln,mode); return head;  }
    int freq1 = (head->tnptr)->freq;
    int freq2 = (ln->tnptr)->freq;
    if(freq1 > freq2)
    {  ln->next=head; return ln;  }
    head->next = List_insert(head->next, ln, mode);
    return head;
}

ListNode * List_build(CharFreq * frequencies)
{
    int ind = 0;
    while(frequencies[ind].freq == 0) ind++;
    if(ind == NUMLETTER) return NULL;
    ListNode * head = NULL;
    while(ind<NUMLETTER)
    {
        TreeNode * tn = TreeNode_create(frequencies[ind], value, frequencies[ind].freq);
        ListNode * ln = ListNode_create(tn);
        head = List_insert(head, ln, SORTED);
        ind++;
    }
    return head;
}

// utility.h
#ifndef UTILITY_H
#define UTILITY_H
#include <stdio.h>
int writeBit(FILE * fptr, unsigned char bit, unsigned char * whichbit, unsigned char * curbyte);
int padZero(FILE * fptr, unsigned char * whichbit, unsigned char * curbyte);
int readBit(FILE * fptr, unsigned char bit, unsigned char * whichbit, unsigned char * curbyte);
#endif

// utility.c
#include <stdio.h>
#include "utility.h"

int padZero(FILE * fptr, unsigned char * whichbit, unsigned char * curbyte)
{
    int rtv;
    while((*whichbit) != 0)
    {
        rtv = writeBit(fptr, 0, whichbit, curbyte);
        if(rtv==-1) return -1;
    }
    return rtv;
}

int readBit(FILE * fptr, unsigned char bit, unsigned char * whichbit, unsigned char * curbyte)
{
    int ret = 1;
    if((*whichbit) == 0) ret=fread(curbyte, sizeof(unsigned char), 1, fptr);
    if(ret != 1) return -1;
    unsigned char temp = (* curbyte) >> (7-(*whichbit));
    temp = temp & 0x01;
    *whichbit = ((*whichbit) + 1) % 8;
    *bit = temp;
    return 1;
}

int writeBit(FILE * fptr, unsigned char bit, unsigned char * whichbit, unsigned char * curbyte)
{
    if((*whichbit) == 0) *curbyte=0;
    unsigned char temp = bit << (7-(* whichbit));
    * curbyte |= temp;
    int value = 0;
    if((*whichbit) == 7)
    {
        int ret;
        ret = fwrite(curbyte, sizeof(unsigned char), 1, fptr);
        if(ret == 1) value = 1;
        else value = -1;
    }
    *whichbit = ((*whichbit) + 1) % 8;
    return value;
}

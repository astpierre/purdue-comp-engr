// partition.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int total=0;
void printPartition(int * arr, int length)
{
    int ind;
    // For odd/even numbers only
    /* for(ind=0; ind<length; ind++) if(arr[ind]%2 == 1) return; */
    for(ind=0; ind<length-1; ind++) printf("%d + ", arr[ind]);
    printf("%d\n", arr[length-1]);
    total+=1;
}

void partition(int * arr, int ind, int left)
{
    int val;
    if(left == 0) {  printPartition(arr, ind); return;  }
    // For using odd numbers only
    //for(val=1; val<=left; val+=2)
    // For using even numbers only
    //for(val=2; val<=left; val+=2)
    // For using sequences of increasing numbers only
    /*
    int min=1;
    if(ind!=0) min=arr[ind-1]+1;
    for(val=min; val<=left; val++)
    {
        arr[ind] = val;
        partition(arr, ind+1, left-val);
    }
    */

    for(val=1; val<=left; val++)
    {
        // For alternating odd/even
        int valid=0;
        if(ind==0) valid=1;
        else valid=(arr[ind-1]%2)!=(val%2);
        if(valid==1)
        {
            arr[ind] = val;
            partition(arr, ind+1, left-val);
        }
        //arr[ind] = val;
        //partition(arr, ind+1, left-val);
    }

}

int main(int argc, char * argv[])
{
    if(argc!=2) return EXIT_FAILURE;
    int n = (int)strtol(argv[1], NULL, 10);
    printf("Partitioning %d...\n", n);
    int * arr;
    arr = malloc(sizeof(int)*n);
    partition(arr, 0, n);
    free(arr);
    printf("Total partitions= %d\n", total);
    return EXIT_SUCCESS;
}

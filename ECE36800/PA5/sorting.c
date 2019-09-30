#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include "sorting.h"

/* Static helper function declarations for Quick Sort */
#define QSORT_MIN 18
#define swap(a,b) \
    do { \
        long tmp; \
        tmp = a; \
        a = b; \
        b = tmp; \
    } while(0)
static void qs( long * arr, int lb, int ub );
static int partition( long * arr, int lb, int ub );
static void insertion_sort( long * arr, int lb, int ub );
static int median_of_three( long * arr, int lb, int ub );

/* Static helper function declarations for Merge Sort */
#define MSORT_MIN 18
static void ms( long * arr, long * aux, int lb, int ub );
static void merge( long * arr, long * aux, int lb, int mid, int ub );

/* Quick Sort Algorithm & helpers */
void Quick_Sort( long * Array, int Size ) {
    qs(Array, 0, Size-1); // Apply quick sort
    return;
}
static void qs( long * arr, int lb, int ub ) {
    if((ub-lb) < QSORT_MIN) {  insertion_sort(arr, lb, ub); return;  }
    int median = median_of_three(arr, lb, ub);
    swap(arr[lb], arr[median]);
    int pivot_idx = partition(arr, lb, ub);
    qs(arr, lb, pivot_idx-1);
    qs(arr, pivot_idx+1, ub);
}
static int partition( long * arr, int lb, int ub ) {
    long pivot = arr[lb];
    int down = lb, up = ub+1;

    while(true) {
        while(arr[++down] < pivot) { /* Find leftmost long >= to piv */
            if(down == ub) break;
        }
        while(arr[--up] > pivot) { /* Find rightmost long <= to piv */
            if(up == lb) break;
        }

        /* If partitioned... */
        if(down >= up) break;

        /* Quick swapping */
        swap(arr[down], arr[up]);

    }
    swap(arr[lb], arr[up]);
    return up;
}
static int median_of_three( long * arr, int lb, int ub ) {
    int mid = lb + (ub-lb)/2;
    if(arr[ub] < arr[lb]) swap(arr[lb], arr[ub]);
    if(arr[mid] < arr[lb]) swap(arr[mid], arr[lb]);
    if(arr[ub] < arr[mid]) swap(arr[ub], arr[mid]);
    return mid;
}
static void insertion_sort( long * arr, int lb, int ub ) {
    for(int i=ub; i > lb; i--) {
        if(arr[i] < arr[i-1]) swap(arr[i], arr[i-1]);
    }
    for(int i=lb+2; i<=ub; i++) {
        int j = i;
        long piv = arr[i];
        while(piv < arr[j-1]) {
            arr[j] = arr[j-1]; j--;
        }
        arr[j] = piv;
    }
}

/* Merge Sort Algorithm & helpers */
void Merge_Sort( long * Array, int Size ) {
    if(Size < 2) return;
    long * aux = (long *)malloc(Size*sizeof(long));
    memcpy(&aux[0], &Array[0], Size*sizeof(long));
    ms(Array, aux, 0, Size-1);
    free(aux);
}
static void ms( long * arr, long * aux, int lb, int ub ) {
    if(ub-lb < MSORT_MIN) {
        insertion_sort(arr, lb, ub);
    } else {
        int mid = (ub+lb)/2;
        ms(arr, aux, lb, mid);
        ms(arr, aux, mid+1, ub);
        merge(arr, aux, lb, mid, ub);
    }
}
static void merge( long * arr, long * aux, int lb, int mid, int ub ) {
    memcpy(&aux[lb], &arr[lb], (ub-lb+1)*sizeof(long));
    int i=lb, j=mid+1;
    for(int k=lb; k<=ub; k++) {
        if(i > mid) arr[k] = aux[j++];
        else if(j > ub) arr[k] = aux[i++];
        else if(aux[j] < aux[i]) arr[k] = aux[j++];
        else arr[k] = aux[i++];
    }
}

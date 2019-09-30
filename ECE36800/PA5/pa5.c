#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "sorting.h"

// Macros and defines
#define MODE_MSORT "-m"
#define MODE_QSORT "-q"

// Helpers loading to/from binary file [utilities]
long * Load_Into_Array(char * filename, int * size) {
    FILE * fptr = fopen(filename, "rb");
    if(fptr == NULL) {
        printf("BAD FILENAME\n");
        fclose(fptr);
        return NULL;
    }
    fseek(fptr, 0, SEEK_END);
    long int nLongs = (ftell(fptr) / sizeof(long));
    long * arr = (long *)calloc(nLongs, sizeof(long));
    fseek(fptr, 0, SEEK_SET);
    for(int i=0; i < nLongs; i++) {
        if(fread(&arr[i], sizeof(long), 1, fptr) != 1) {
            printf("Bad read while loading into array.\n");
        }
    }
    fclose(fptr);
    *size=nLongs;
    return arr;
}
int Save_From_Array(char * filename, long * arr, int size) {
    FILE * fptr = fopen(filename,"wb");
    if(fptr == NULL) {
        printf("error creating file");
        return EXIT_FAILURE;
    }

    int i = 0;
    while(i < size) {
        if(fwrite(&arr[i], sizeof(long), 1, fptr) != 1)
        {  printf("Save_From_Array: bad fwrite\n");  }
        i += 1;
    }
    fclose(fptr);
    return i;
}
int Save_From_ArrayToText(char * filename, long * arr, int size) {
    FILE * fptr = fopen(filename,"w");
    if(fptr == NULL) {
        printf("error creating file");
        return EXIT_FAILURE;
    }

    int i = 0;
    while(i < size) {
        fprintf(fptr, "%ld\n", (long)arr[i]);
        i += 1;
    }
    fclose(fptr);
    return i;
}
void PrintArray(long * arr, int size) {
    printf("\nArray size: %d\n", size);
    for(int i = 0; i<size; i++) {
        printf("\t%ld\n", arr[i]);
    }
}

/* Main entrypoint */
int main(int argc, char ** argv) {
    /* Determine mode and check input args accordingly */
    char * mode = argv[1];

    if(strcmp(mode, MODE_QSORT) == 0) { /* Quick sort algorithm */
        char * in_file = argv[2];
        char * out_file = argv[3];
        int size = 0;

        long * arr = Load_Into_Array(in_file, &size); // load from input file
        clock_t start, end;
        start = clock();

        Quick_Sort(arr, size); // Run algorithm on array

        end = clock();
        FILE * fp = fopen("outputQ.txt", "a");
        fprintf(fp, "%f %f\n", (double)size, (double)end-start);
        fclose(fp);

        Save_From_ArrayToText(out_file, arr, size); // save to output file

        free(arr); // cleanup

    } else if(strcmp(mode, MODE_MSORT) == 0) { /* Merge sort algorithm */
        char * in_file = argv[2];
        char * out_file = argv[3];
        int size = 0;
        long * arr = Load_Into_Array(in_file, &size);
        clock_t start, end;
        start = clock();

        Merge_Sort(arr, size); // Run algorithm on array

        end = clock();
        FILE * fp = fopen("outputM.txt", "a");
        fprintf(fp, "%f %f\n", (double)size, (double)end-start);
        fclose(fp);

        Save_From_ArrayToText(out_file, arr, size); // save to output file

        free(arr); // cleanup

    }
    return EXIT_SUCCESS;
}

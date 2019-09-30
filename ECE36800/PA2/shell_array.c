#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_array.h"
#include "sequence.h"

// Helper functions
static int findSize(char * filename) {
    long temp = 0;
    int counter = 0;
    FILE * fptr = fopen(filename, "rb");
    if(fptr == NULL) {
        printf("BAD FILENAME\n");
        fclose(fptr);
        return 0;
    }
    fseek(fptr, 0, SEEK_SET);
    while(feof(fptr) == 0) {
        if(fread(&temp, sizeof(long), 1, fptr) != 1) break;
        else counter += 1;
    }
    fclose(fptr);
    return counter;
}
static void fillArray(long * arr, int size, char * filename) {
    int i = 0;
    long temp = 0;
    FILE * fptr = fopen(filename, "rb");
    if(fptr == NULL) {
        printf("BAD FILENAME\n");
        fclose(fptr);
        return;
    }
    fseek(fptr, 0, SEEK_SET);
    while(feof(fptr) == 0) {
        if(fread(&temp, sizeof(long), 1, fptr) != 1) break;
        else arr[i] = temp;
        i++;
    }
    fclose(fptr);
}

// Required methods
void Array_Shellsort(long * array, int size, double * n_comp) {
    // Generate the sequence for shell sorting
    long * sequence = NULL;
    int i = 0, j = 0, seq_size = 0;
    sequence = Generate_2p3q_Seq(size, &seq_size);

    // Step through elements in sequence
    long interval = 0, temp = 0;
    for(; seq_size > 0; seq_size--) {
        interval = sequence[seq_size - 1];
        for(j = interval; j < size; j++) {
            temp = array[j];
            i = j - (int)interval;
            while((i >= 0) && (temp < array[i])) {
                *n_comp = *n_comp + 1.0;
                array[i + (int)interval] = array[i];
                i = i - (int)interval;
            }
            *n_comp = *n_comp + 1.0;
            array[i + interval] = temp;
        }
    }
    free(sequence);
    return;
}
long * Array_Load_From_File(char * filename, int * size) {
    /* Get the number of long ints in binary file */
    *size = findSize(filename);

    /* Allocate memory for the number of long ints required */
    long * arr = NULL;
    if(*size == 0) {
        /* If the input file is empty, an array of size 0 should
           still be created and *size be assigned 0 */
           arr = malloc(sizeof(long)*0);
           if(arr == NULL){
               printf("Array_Load_From_File: bad malloc, exiting\n");
               return NULL;
           }
           return arr;
    }
    arr = malloc(sizeof(long)*(*size));
    /* You should return a NULL address and assign 0 to *size if
       could not open the file / fail to allocate suff memory. */
    if(arr == NULL){
        printf("Array_Load_From_File: bad malloc, exiting\n");
        return NULL;
    }

    /* Fill the array with long ints from binary file */
    fillArray(arr, *size, filename);

    /* Return the pointer to array */
    return arr;
}
int Array_Save_To_File(char * filename, long * array, int size) {
    /* The function saves array to an external file specified
       by filename in binary format. The output file and the
       input file have the same format. The integer returned
       should be the number oflong integers in the array that
       have been successfully saved into the file. If the size of
       the array is 0, an empty output file should be created. */
    FILE * fptr = fopen(filename,"wb");
    if(fptr == NULL) {
        printf("error creating file");
        return 0;
    }
    if(size == 0) {
        return 0;
    }
    int i = 0;
    int counter = 0;
    for(i=0; i<size; i++) {
        if(fwrite(&array[i], sizeof(array[i]), 1, fptr) != 1)
        {  printf("Array_Save_To_File: bad fwrite\n");  }
        counter += 1;
    }
    fclose(fptr);
    return counter;
}

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "seqpair.h"

/* Static helper function declarations */
static rectangle * Load_Rectangles( char * filename, int * size, int ** seq0, int ** seq1 );
static void write_coordinates( rectangle * rectangles, char * filename );

/* Static debugging function declarations [uncomment for use] */
//static void print_rectangles( rectangle * rectangleArr );
//static void print_sequence( int * sequence );


/* Main entrypoint */
int main( int argc, char ** argv ) {
    /* Check input args and initialize variables */
    if(argc != 3) printf("Usage: ./pa6 input/file output/file\n");
    char * inputFile = argv[1];
    char * outputFile = argv[2];
    int numberRectangles = 0;
    int * seq0 = NULL;
    int * seq1 = NULL;

    /* Load rectangles and sequences */
    rectangle * rectangles = Load_Rectangles(inputFile, &numberRectangles, &seq0, &seq1);

    /* Generate horizontal and vertical adjacency lists */
    adj_list_node * before = NULL; adj_list_node * after = NULL;
    adj_list_node * below = NULL; adj_list_node * above = NULL;
    generate_horizontal_adj_lists(seq0, seq1, &before, &after);
    generate_vertical_adj_lists(seq0, seq1, &below, &above);

    /* Calculate dimensions */
    topo_horiz(rectangles, after);
    calc_horiz(rectangles, before, after);
    topo_vert(rectangles, below);
    calc_vert(rectangles, below, above);
    label_sort(rectangles, 0, numberRectangles-1);
    write_coordinates(rectangles, outputFile);

    /* Cleanup */
    free(seq0);
    free(seq1);
    adj_list_free(before);
    adj_list_free(after);
    adj_list_free(below);
    adj_list_free(above);
    free(rectangles);
    return EXIT_SUCCESS;
}

/* Static helper functions [utilities] */
static rectangle * Load_Rectangles( char * filename, int * size, int ** seq0, int ** seq1 ) {
    /* Open and check file */
    FILE * fptr = fopen(filename, "r");
    if(fptr == NULL) {
        printf("BAD FILENAME\n");
        fclose(fptr);
        return NULL;
    }
    fseek(fptr, 0, SEEK_SET);

    if(fscanf(fptr, "%d\n", size) != 1) { /* Grab number of rectangles */
        return NULL;
    }
    NUMRECTANGLES = *size;

    /* Create an array of rectangles */
    rectangle * rectangleArr = (rectangle *)calloc(*size, sizeof(rectangle));
    double w=0;
    double h=0;
    int l=0;
    for(int i=0; i<*size; i++) {
        if(fscanf(fptr, "%d(%le,%le)\n", &l, &w, &h) != 3) {
            return NULL;
        }
        init_rectangle(&rectangleArr[i], l, w, h);
    }

    /* Get the two sequences from the file's last 2 lines */
    int * seq0_tmp = (int *)calloc(*size, sizeof(int));
    int * seq1_tmp = (int *)calloc(*size, sizeof(int));
    for(int i=0; i<(*size-1); i++){
        if(fscanf(fptr, "%d", seq0_tmp+i) != 1) {
            return NULL;
        }
    }
    if(fscanf(fptr, "%d\n", seq0_tmp+(*size-1)) != 1) {
        return NULL;
    }
    for(int i=0; i<(*size); i++){
        if(fscanf(fptr, "%d", seq1_tmp+i) != 1) {
            return NULL;
        }
    }

    /* Save the arrays of sequence ints */
    *seq0 = seq0_tmp;
    *seq1 = seq1_tmp;

    fclose(fptr);
    return rectangleArr;
}
static void write_coordinates( rectangle * rectangles, char * filename ) {
    FILE * fptr = fopen(filename, "w");
    if(fptr == NULL) { fclose(fptr); return; }

    int numberRectangles = NUMRECTANGLES;
    fseek(fptr, 0, SEEK_SET);
    for(int i=0; i<numberRectangles; i++) {
        fprintf(fptr,"%d(%le,%le)\n", rectangles[i].label, rectangles[i].x_0, rectangles[i].y_0);
    }
    fclose(fptr);
}

/* Debugging tools */
/*static void print_rectangles( rectangle * rectangleArr ) {
    int numberRectangles = NUMRECTANGLES;
    printf("Number of rectangles: %d\n", numberRectangles);
    for(int i=0; i<numberRectangles; i++) {
        printf("%d (%le, %le)\tx_0=%f x_f=%f\ty_0=%f y_f=%f\n", rectangleArr[i].label, rectangleArr[i].width, rectangleArr[i].height, rectangleArr[i].x_0, rectangleArr[i].x_f, rectangleArr[i].y_0, rectangleArr[i].y_f);
    }
    return;
}
static void print_sequence( int * sequence ) {
    int numberIntegers = NUMRECTANGLES;
    for(int i=0; i<(numberIntegers); i++) {
        printf("[ %d ] ", sequence[i] );
    }
    printf("\n");
    return;
}*/

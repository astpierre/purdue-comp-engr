#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "delay.h"

// Main entrypoint
int main(int argc, char ** argv) {
    // Check for input error
    if(argc != 4) return EXIT_FAILURE;

    char * input_filename = argv[1];
    char * output_filename1 = argv[2];
    FILE * fptr = fopen(output_filename1, "w");
    if(fptr==NULL) {  printf("Err creating output_filename1\n"); fclose(fptr); return EXIT_FAILURE;  }
    fclose(fptr);
    char * output_filename2 = argv[3];
    fptr = fopen(output_filename2, "wb");
    if(fptr==NULL) {  printf("Err creating output_filename2\n"); fclose(fptr); return EXIT_FAILURE;  }
    fclose(fptr);

    BinaryTreeReCreate(input_filename, output_filename1, output_filename2);

    return EXIT_SUCCESS;
}

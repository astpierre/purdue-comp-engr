#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "avl_tree.h"

// Macros and defines
#define MODE_BUILD "-b"
#define MODE_EVAL "-e"
#define INSTR_INSERT 'i'
#define INSTR_DELETE 'd'
#define MAX_HEIGHT INT_MAX
#define ERROR_CODE -1
#define OPEN_FAIL -1
#define WRONG_FMT 0
#define OPEN_SUCCESS 1
#define BST_FAIL 0
#define BST_PASS 1
#define HBAL_FAIL 0
#define HBAL_PASS 1

// Size of instruction input file [utility]
int count_instructions(char * instructions_file) {
    FILE * fptr = fopen(instructions_file, "rb");
    if(fptr == NULL) {
        printf("Err: failed to open input instructions file\n");
        fclose(fptr);
        return EXIT_FAILURE;
    }
    fseek(fptr, 0, SEEK_END);
    int size_bytes = ftell(fptr);
    fclose(fptr);
    int num_instructions = (size_bytes)/(sizeof(int)+sizeof(char));
    return num_instructions;
}
int count_nodes(char * tree_input_file) {
    FILE * fptr = fopen(tree_input_file, "rb");
    if(fptr == NULL) {
        printf("Err: failed to open input tree_input_file\n");
        fclose(fptr);
        return EXIT_FAILURE;
    }
    fseek(fptr, 0, SEEK_END);
    int size_bytes = ftell(fptr);
    fclose(fptr);
    int num_nodes = (size_bytes)/(sizeof(int)+sizeof(char));
    return num_nodes;
}

// Build mode helper
int build_avl_tree( char * instructions_file, char * output_file ) {
    /* Open our instruction file. */
    FILE * fptr = fopen(instructions_file, "rb");
    if(fptr == NULL) {
        fclose(fptr);
        printf("%d\n", ERROR_CODE);
        return EXIT_FAILURE;
    }
    fseek(fptr, 0, SEEK_SET);

    /* File reading variables / helpers. */
    int temp_int = 0;
    char temp_char = '\0';
    int num_instructions = count_instructions(instructions_file);
    int i = 0;

    /* Root of our AVL tree. */
    avl_node * root = NULL;

    /* Process the instruction file to build AVL tree. */
    while(i++ < num_instructions) {
        if(fread(&temp_int, sizeof(int), 1, fptr) != 1) { /* Get key */
            printf("Err: unable to read an integer from input file.\n");
            fclose(fptr);
            return EXIT_FAILURE;
        }
        if(fread(&temp_char, sizeof(char), 1, fptr) != 1) { /* Get instruction */
            printf("Err: unable to read a character from input file.\n");
            fclose(fptr);
            return EXIT_FAILURE;
        }

        if(temp_char == 'd') { /* Delete node w. key = temp_int */
            root = delete_avl(root, temp_int);

        } else if(temp_char == 'i') { /* Insert node w. key = temp_int */
            root = insert_avl(root, temp_int);

        } else { /* Bad input file format... */
            printf("Err: bad input file format...\n");
            fclose(fptr);
            return EXIT_FAILURE;
        }
    }
    fclose(fptr); // Close instruction file

    /* Output the height-balanced AVL tree in preorder fashion. */
    write_avl_to_file(root, output_file); printf("\n");

    free_avl(root); // Cleanup
    return EXIT_SUCCESS;
}

// Eval mode helper
int eval_avl_tree( char * tree_input_file ) {
    /* Open our input file. */
    FILE * fptr = fopen(tree_input_file, "rb");
    if(fptr == NULL) {
        fclose(fptr);
        return OPEN_FAIL;
    }
    /* File reading variables / helpers. */
    int temp_int = 0;
    char temp_char = '\0';
    int num_nodes = count_nodes(tree_input_file);
    int i = 0;

    fseek(fptr, 0, SEEK_SET);
    printf("\n\n%d\n\n", num_nodes);
    while(i++ < num_nodes) {
        if(fread(&temp_int, sizeof(int), 1, fptr) != 1) { /* Get key */
            printf("Err: unable to read an integer from input file.\n");
            fclose(fptr);
            return WRONG_FMT;
        }
        printf("\n\tnumber=%d\n",temp_int);
        if(fread(&temp_char, sizeof(char), 1, fptr) != 1) { /* Get instruction */
            printf("Err: unable to read a character from input file.\n");
            fclose(fptr);
            return WRONG_FMT;
        }
        printf("\n\tchar=%c\n",temp_char);
    }
    fclose(fptr); // Close instruction file
    return EXIT_SUCCESS;
}

// Main entrypoint
int main(int argc, char ** argv) {
    /* Determine mode and check input args accordingly */
    char * mode = argv[1];

    if(strcmp(mode, MODE_BUILD) == 0) { /* Build AVL tree */
        if(argc != 4) {
            return EXIT_FAILURE;
        }
        char * instructions_file = argv[2];
        char * output_file = argv[3];
        if(build_avl_tree(instructions_file, output_file) == EXIT_FAILURE) {
            return EXIT_FAILURE;
        }

    } else if(strcmp(mode, MODE_EVAL) == 0) { /* Evaluate AVL tree */
        if(argc != 3) {
            return EXIT_FAILURE;
        }
        int result = -100;
        if(result == OPEN_FAIL) {
            printf("%d,%d,%d\n",OPEN_FAIL, 0,0);
        } else if(result == WRONG_FMT) {
            printf("%d,%d,%d\n",WRONG_FMT, 0,0);
        } else {
            printf("%d,%d,%d\n",0,0,0);
        }
    }
    return EXIT_SUCCESS;
}

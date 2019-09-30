#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "shell_array.h"
#include "shell_list.h"

// Defines
#define MODE_ARRAY "-a"
#define MODE_LIST "-l"

// Helper functions
void LinkedListShellMainDestroy(Node ** head) {
    Node * current = *head;
	while(current!=NULL) {
		*head = current->next;
		free(current);
		current=*head;
	}
}

// Main entrypoint
int main(int argc, char * * argv) {
    // Check for input error
    if(argc != 4) return EXIT_FAILURE;

	// Get the mode of operation
	char * mode = argv[1];

	// Perform user specified task
    if(strcmp(mode, MODE_ARRAY) == 0) {
		// Read longs from the input binary file
		long * load_arr = NULL;
	    int filesize = 0;
	    load_arr = Array_Load_From_File(argv[2], &filesize);
        if(load_arr == NULL) return EXIT_FAILURE;
		// Sort the array of longs and print number of comparisons
		double n_comp = 0.0;
	    Array_Shellsort(load_arr, filesize, &n_comp);
	    printf("%le\n", n_comp);
		// Write array of longs to output binary file
		int longsWritten = Array_Save_To_File(argv[3], load_arr, filesize);
        if(longsWritten == EXIT_FAILURE) {
            free(load_arr);
            return EXIT_FAILURE;
        }
		// Cleanup
		free(load_arr);
	} else if(strcmp(mode, MODE_LIST) == 0) {
		// Read longs from the input binary file
		Node * shell_list = NULL;
	    shell_list = List_Load_From_File(argv[2]);
        if(shell_list == NULL) return EXIT_FAILURE;
		// Sort the list of longs and print number of comparisons
		double n_comp = 0.0;
		shell_list = List_Shellsort(shell_list, &n_comp);
		printf("%le\n", n_comp);
		// Write list of longs to output binary file
		int longsWritten = List_Save_To_File(argv[3], shell_list);
        if(longsWritten == EXIT_FAILURE) {
            LinkedListShellMainDestroy(&shell_list);
            return EXIT_FAILURE;
        }
		// Cleanup
		LinkedListShellMainDestroy(&shell_list);
	}
    return EXIT_SUCCESS;
}

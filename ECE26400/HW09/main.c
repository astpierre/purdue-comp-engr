// You may modify this file.
// For testing but this file will NOT be submitted.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "shuffle.h"

#ifdef TEST_MAIN
int main(int argc, char ** argv) 
{
	char deck[MAX_SIZE] = {'A', '2', '3', '4', '5', '6', '7', '8'};
	
	// Check for missing inputs
	if(argc != 3) 
    {  fprintf(stderr, "USAGE: <num_cards> <num_rnds>\n"); return EXIT_FAILURE;  }

	// Create a structure variable (corresponding to the original deck)
	CardDeck orig_deck;
	orig_deck.size = MAX_SIZE;

    // Use memcpy()
	memcpy(orig_deck.cards, deck, MAX_SIZE);

	// Read the number of cards from the terminal 
	orig_deck.size = strtol(argv[1], NULL, 10);
	
    // Check that number !> MAX_SIZE
    if(orig_deck.size > MAX_SIZE)
    {
       	fprintf(stderr, "USAGE: number of cards must not exceed MAX_SIZE\n"); 
    	return EXIT_FAILURE;
    }
	
	// Read the number of rounds to shuffle the deck
	int rounds = strtol(argv[2], NULL, 10);

	// Call repeat_shuffle()
	repeat_shuffle(orig_deck, rounds);
	
	return EXIT_SUCCESS;
}
#endif

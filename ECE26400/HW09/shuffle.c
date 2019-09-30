#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Helper functions
//static void _error_clean()
//{  exit(EXIT_FAILURE);  }

#ifdef TEST_DIV
void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck)
{
	// Dividing the decks into lower and upper decks
	for(int i=0; i < (orig_deck.size - 1); i++)
	{
		// Copy cards into upper and lower decks from original
		strncpy(upper_deck[i].cards, orig_deck.cards, i+1);
		strncpy(lower_deck[i].cards, orig_deck.cards+(i+1), orig_deck.size-i-1);

		// Update the size of the upper and lower decks
		upper_deck[i].size = i+1;
		lower_deck[i].size = orig_deck.size-i-1;
	}
}
#endif

#ifdef TEST_INTER
void combine(CardDeck combined_deck, CardDeck upper_deck, CardDeck lower_deck, int rounds)
{
    /*************************************************************************/
    /**** CHECK FOR EMPTY UPPER/LOWER DECKS   *******************************/
    /*************************************************************************/
	// Check that upper deck !empty, if so, empty lower and print
	if (upper_deck.size == 0)
    {
        // If empty, add remaining lower_deck cards
        for(int i=0; i < (lower_deck.size); i++)
        {
            // Use memcpy() to copy each card to new deck
            memcpy(&combined_deck.cards[combined_deck.size], &lower_deck.cards[i], 1);
            
            // Update the size of new_deck
            combined_deck.size = combined_deck.size + 1; 
        }

        // Recursive call to repeat, decrement rounds
        repeat_shuffle(combined_deck, rounds-1);
        return;
    }
    // Check that lower deck !empty, if so, empty upper and print
	if (lower_deck.size == 0)
    {
        // If so, add remaining upper_deck cards
        for(int i=0; i < (upper_deck.size); i++)
        {
            // Use memcpy() to copy each card to new deck
            memcpy(&combined_deck.cards[combined_deck.size], &upper_deck.cards[i], 1);
           
            // Update the size of combined_deck
            combined_deck.size = combined_deck.size + 1; 
        }
        
        // Recursive call to repeat, decrement rounds
        repeat_shuffle(combined_deck, rounds-1);
        return;
    }
   
    /*************************************************************************/
    /**** CONTINUE BUILDING COMBINED DECK   *********************************/
    /*************************************************************************/
    // Make a new upper deck for recursive calling
    CardDeck new_upper_deck;
    new_upper_deck.size = 0;

    // Make a copy of combined deck
    CardDeck new_combined_deck_a;
    new_combined_deck_a.size = combined_deck.size;
    for(int i=0; i < (combined_deck.size); i++)
    {  memcpy(&new_combined_deck_a.cards[i], &combined_deck.cards[i], 1);  }

	// Pick from upper deck, add to new deck
    memcpy(&new_combined_deck_a.cards[new_combined_deck_a.size], &upper_deck.cards[0], 1);
    new_combined_deck_a.size += 1;
    
    // Fill the new upper deck with cards
    for(int i=1; i < (upper_deck.size); i++)
    {
        memcpy(&new_upper_deck.cards[i-1], &upper_deck.cards[i], 1);
        new_upper_deck.size += 1;
    }
    
    // Call reursively
    combine(new_combined_deck_a, new_upper_deck, lower_deck, rounds);
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    // Make a new lower deck for recursive calling
    CardDeck new_lower_deck;
    new_lower_deck.size = 0;
    
    // Make a copy of combined deck
    CardDeck new_combined_deck_b;
    new_combined_deck_b.size = combined_deck.size;
    for(int i=0; i < (combined_deck.size); i++)
    {  memcpy(&new_combined_deck_b.cards[i], &combined_deck.cards[i], 1);  }

	// Pick from lower deck, add to new deck
    memcpy(&new_combined_deck_b.cards[new_combined_deck_b.size], &lower_deck.cards[0], 1);
    new_combined_deck_b.size += 1;
    
    // Fill the new lower deck with cards
    for(int i=1; i < (lower_deck.size); i++)
    {  memcpy(&new_lower_deck.cards[i-1], &lower_deck.cards[i], 1); new_lower_deck.size += 1;  }
    
    // Call reursively
    combine(new_combined_deck_b, upper_deck, new_lower_deck, rounds);
    /*************************************************************************/
    /*************************************************************************/
}
#endif

#ifdef TEST_INTER
void interleave(CardDeck upper_deck, CardDeck lower_deck, int repeat)
{
	// Instantiate deck to hold interleaved decks
	CardDeck new_deck;
    new_deck.size = 0;

	// Call combine() to do the interleaving
    combine(new_deck, upper_deck, lower_deck, repeat);
}
#endif

#ifdef TEST_SHUF
//repeat holds the number of shuffles that are yet to be performed.
void shuffle(CardDeck orig_deck, int repeat)
{
    // Declare a variable to hold the number of pairs
	int number_pairs = orig_deck.size - 1;
	if(number_pairs == 0) return;

	// Instantiate pointers to hold both upper and lower decks (after division)
	CardDeck * upper_deck = NULL;
	CardDeck * lower_deck = NULL;

	// allocate memory based on number of pairs
	upper_deck = malloc(number_pairs*sizeof(CardDeck));
    if(upper_deck == NULL) return;
	lower_deck = malloc(number_pairs*sizeof(CardDeck));
    if(lower_deck == NULL) {  free(upper_deck); return;  }

	// Call divideDeck to fill upper_deck and lower_deck
	divide(orig_deck, upper_deck, lower_deck);

	// Run a loop through all the pairs and call interleave for each
	for(int i = 0; i < number_pairs; i++) {  interleave(upper_deck[i], lower_deck[i], repeat);  }

	// Free memory allocated to upper and lower decks
	free(upper_deck);
	free(lower_deck);
}
#endif

#ifdef TEST_RSHUF
void repeat_shuffle(CardDeck orig_deck, int k)
{
	// Check if k ≤ 0
    if(k <= 0) {  printDeck(orig_deck); return;  }
	
	// Call shuffle()
    shuffle(orig_deck, k);

    // If reach here, malloc failed, return
    return;
}
#endif

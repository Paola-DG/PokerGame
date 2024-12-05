#ifndef DECK_H
#define DECK_H

#define DECK_SIZE 52
#define RANK_SIZE (ACE + 1)

typedef enum {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
} Suit;

typedef enum {
    TWO = 2,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
} Rank;


typedef struct {
    Suit suit;
    Rank rank;
} Card;



/**
 * Receives pointer to deck (card array) of DECK_SIZE
 * Initializes deck of DECK_SIZE for HEARTS, DIAMONDS, CLUBS, and SPADES
 */
void initialize_deck(Card deck[DECK_SIZE]);

/**
 * Receives pointer to deck (card array) of DECK_SIZE
 * Randomly shuffles
 */
void shuffle_deck(Card deck[DECK_SIZE]);

/**
 * Receives card struct to be printed
 * Prints the card Suit + Rank - i.e. CLUBS 9
 */
void print_card(Card card);

#endif
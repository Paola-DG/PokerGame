#ifndef POKER_GAME_H
#define POKER_GAME_H

#include "deck.h"

#define PLAYER_HOLE_CARDS 2
#define TOTAL_PLAYERS 4
#define COMMUNITY_CARDS 5

// TODO: define Player struct
typedef struct {
    char name[32];
    int chips;
    Card card[PLAYER_HOLE_CARDS];
} Player;

// TODO: define dealer struct
typedef struct {
    Card deck[DECK_SIZE];
    int deck_idx;
} Dealer;


// TODO: define a table where all components are shared, i.e. players, dealer, community cards, etc.
typedef struct {
    Dealer *dealer;
    Player players[TOTAL_PLAYERS];
    Card community_Cards[COMMUNITY_CARDS];
} Table;


// void setup_table(Table *table);

// /**
//  * Function will deal hole cards from dealer deck to all players
//  */
// void deal_cards(Table *table);

// void play_round(Table *table);

// void decide_winner(Table *table);

// void bubble_sort(Card *cards, int size);


#endif
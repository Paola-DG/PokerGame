#ifndef POKER_GAME_H
#define POKER_GAME_H

#include <stdlib.h>
#include "utils.h"

// macro for clearing screen depending on os
#ifdef _WIN32
    #define CLEAR_SCREEN() system("cls")
#else // linux/mac
    #define CLEAR_SCREEN() system("clear")
#endif


#include "deck.h"

#define PLAYER_HOLE_CARDS 2
#define TOTAL_PLAYERS 4
#define COMMUNITY_CARDS 5
#define BIG_BLIND 10

enum HandRanks {
    ROYAL_FLUSH = 0,
    STRAIGHT_FLUSH = 1,
    FOUR_OF_A_KIND = 2,
    FULL_HOUSE = 3,
    FLUSH = 4,
    STRAIGHT = 5,
    THREE_OF_A_KIND = 6,
    TWO_PAIR = 7,
    ONE_PAIR = 8,
    HIGH_CARD = 9
};

// TODO: define Player struct
typedef struct {
    int player_number;
    int chips;
    Card cards[PLAYER_HOLE_CARDS];

    int current_bet;        // Current bet for the round
    int folded;             // if player has folded from match
} Player;

// TODO: define dealer struct
typedef struct {
    Card* deck;
    int deck_idx;
} Dealer;


// TODO: define a table where all components are shared, i.e. players, dealer, community cards, etc.
typedef struct {
    Dealer *dealer;
    Player *players;
    Card community_cards[COMMUNITY_CARDS];
    int community_card_idx;

    int pot;                // Total pot for match
    int current_bet;        // Current round's bet that players must match
    int small_blind;        
    int big_blind;
    int small_blind_idx;    // idx of the small blind player
    int big_blind_idx;      // idx of the big blind player
} Table;

void display_main_menu();

void show_rules();

/**
 * Receives player array. Function does not check if array is initialized so must check before.
 * Function will create a Player struct up to TOTAL_PLAYERS time and add them to array.
 */
void setup_players(Player players[TOTAL_PLAYERS]);

/**
 * Receives pointer to dealer and deck array.
 * Function will assign deck to dealer and a starting index.
 */
void setup_dealer(Dealer *dealer, Card deck[DECK_SIZE]);

/**
 * Receives pointer to table, dealer and array of players
 * Will initialize a table with the received dealer and players
 */
void setup_table(Table *table, Dealer *dealer, Player players[TOTAL_PLAYERS]);

/**
 * Receives pointer to table
 * Function will rotate small and big blind to the next player
 */
void rotate_blinds(Table *table);

/**
 * Receives pointer to table
 * Function will deal hole cards from dealer deck to all players
 */
void deal_hole_cards(Table *table);

/**
 * Receives pointer to table and number of community cards to be dealt
 * Function will deal cards_to_deal from dealer's deck into table's community_cards
 */
void deal_community_card(Table *table, int cards_to_deal);

/**
 * Receives pointer to table struct
 * Function will check for the best hand between all players
 * @returns pointer to winner player
 */
int decide_winner(Table *table, Player *winners[], int player_best_hand_rank[]);

#endif
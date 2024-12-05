#include <stdio.h>
#include "poker_game.h"

const int COMBINED_CARDS_SIZE = PLAYER_HOLE_CARDS + COMMUNITY_CARDS;

/**
 * Combines player hole cards and community cards into one array.
 * Result stored -> combined_cards
 */
static void combine_cards(Card hole_cards[PLAYER_HOLE_CARDS], Card community_cards[COMMUNITY_CARDS], Card combined_cards[COMBINED_CARDS_SIZE]) {
    int i = 0;
    for (int j = 0; j < PLAYER_HOLE_CARDS; j++, i++) {
        combined_cards[i] = hole_cards[j];
    }

    for (int j = 0; j < COMMUNITY_CARDS; j++, i++) {
        combined_cards[i] = community_cards[j];
    }
}

/**
 * Receives pointer to array of cards and array size
 * Sorts cards in rank ascending order
 */
static void bubble_sort(Card *cards, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
                if (cards[j].rank > cards[j + 1].rank) {
                    Card temp = cards[j];
                    cards[j] = cards[j + 1];
                    cards[j + 1] = temp;
            }
        }
    }
}

/**
 * Accepts array of cards size COMBINED_CARDS_SIZE
 * Check card array for royal flush
 * @returns - 1 if found or -1 if not found
 */
static int is_royal_flush(Card combined_cards[COMBINED_CARDS_SIZE]) {
    Rank royal_flush[] = { TEN, JACK, QUEEN, KING, ACE };

    const int ROYAL_FLUSH_SIZE = sizeof(royal_flush) / sizeof(royal_flush[0]);


    for (Suit s = HEARTS; s <= SPADES; s++) {
        int match_count = 0;
        // Check presence of royal flush cards in current suit
        for (int i = 0; i < COMBINED_CARDS_SIZE; i++) {
            for (int j = 0; j < ROYAL_FLUSH_SIZE; j++) {
                if (combined_cards[i].rank == royal_flush[j] && combined_cards[i].suit == s) {
                    match_count++;
                    break;
                }
            }
        }
        
        if (match_count == ROYAL_FLUSH_SIZE) {
            return 1;
        }
    }

    return -1;
}

/**
 * Accepts array of cards size COMBINED_CARDS_SIZE
 * Check card array for straight flush
 * @returns - 1 if found or -1 if not found
 */
static int is_straight_flush(Card combined_cards[COMBINED_CARDS_SIZE]) {
    int STRAIGHT_FLUSH_SIZE = 5;

    bubble_sort(combined_cards, COMBINED_CARDS_SIZE);

    for (Suit s = HEARTS; s <= SPADES; s++) {
        int consecutive_count = 1;
  
        for (int i = 0; i < COMBINED_CARDS_SIZE; i++) {
            if (i > 0 && combined_cards[i].suit == s) {
                if (combined_cards[i].rank == combined_cards[i - 1].rank + 1) {
                    consecutive_count++;

                    if (consecutive_count == STRAIGHT_FLUSH_SIZE) {
                        return 1;
                    }
                } else {
                    // Sequence is broken so reset
                    consecutive_count = 1;
                }
            }
        }
    }

    return -1;
}

/**
 * Accepts array of cards size COMBINED_CARDS_SIZE
 * Check card array for four of a kind
 * @returns - 1 if found or -1 if not found
 */
static int is_four_of_a_kind(Card combined_cards[COMBINED_CARDS_SIZE]) {
    const int HAND_SIZE = 4;

    int rank_counts[RANK_SIZE] = {0};

    for (int i = 0; i < COMBINED_CARDS_SIZE; i++) {
        rank_counts[combined_cards[i].rank]++;
        if (rank_counts[combined_cards[i].rank] == HAND_SIZE) {
            return 1;
        }
    }

    return -1;
}

/**
 * Accepts array of cards size COMBINED_CARDS_SIZE
 * Check card array for full house
 * @returns - 1 if found or -1 if not found
 */
static int is_full_house(Card combined_cards[COMBINED_CARDS_SIZE]) {
    int rank_counts[RANK_SIZE] = {0};

    for (int i = 0; i < COMBINED_CARDS_SIZE; i++) {
        rank_counts[combined_cards[i].rank]++;
    }

    int three_kind_found = 0, one_pair_found = 0;

    for (int i = TWO; i < RANK_SIZE; i++) {
        if (rank_counts[i] == 3) {   
            three_kind_found = 1; 
        }
        else if (rank_counts[i] == 2) {
            one_pair_found = 1;
        }

        if (three_kind_found && one_pair_found) { return 1; }
    }

    return -1;
}

/**
 * Accepts array of cards size COMBINED_CARDS_SIZE
 * Check card array flush
 * @returns - 1 if found or -1 if not found
 */
static int is_flush(Card combined_cards[COMBINED_CARDS_SIZE]) {
    const int FLUSH_SIZE = 5;

    for (Suit s = HEARTS; s <= SPADES; s++) {
        int match_count = 0;
        for (int i = 0; i < COMBINED_CARDS_SIZE; i++) {
            if (combined_cards[i].suit == s) { match_count++; }
            if (match_count == FLUSH_SIZE) { return 1;}
        }
    }

    return -1;
}

/**
 * Accepts array of cards size COMBINED_CARDS_SIZE
 * Check card array for a straight
 * @returns - 1 if found or -1 if not found
 * 
 * TODO: Add ace-low check (A, 2, 3, 4, 5) - Ace is being used as high card instead of low
 */
static int is_a_straight(Card combined_cards[COMBINED_CARDS_SIZE]) {
    const int STRAIGHT_SIZE = 5;

    bubble_sort(combined_cards, COMBINED_CARDS_SIZE);

    int consecutive_count = 1;
    for (int i = 1; i < COMBINED_CARDS_SIZE; i++) {
        // skip if they're the same
        if (combined_cards[i].rank == combined_cards[i - 1].rank ) { continue; }

        if (combined_cards[i].rank == combined_cards[i - 1].rank + 1) {
            consecutive_count++;

            if (consecutive_count == STRAIGHT_SIZE) {
                return 1;
            }
        } else {
            // Sequence is broken so reset
            consecutive_count = 1;
        }
    }
    return -1;
}

/**
 * Accepts array of cards size COMBINED_CARDS_SIZE
 * Check card array for three of a kind
 * @returns - 1 if found or -1 if not found
 */
static int is_three_of_a_kind(Card combined_cards[COMBINED_CARDS_SIZE]) {
    const int HAND_SIZE = 3;

    int rank_counts[RANK_SIZE] = {0};

    for (int i = 0; i < COMBINED_CARDS_SIZE; i++) {
        rank_counts[combined_cards[i].rank]++;
        if (rank_counts[combined_cards[i].rank] == HAND_SIZE) {
            return 1;
        }
    }

    return -1;
}

/**
 * Receives pointer to dealer
 * Function will deal card from dealer's deck and increase dealer's deck_idx
 * @returns - 
 */
static Card deal_card(Dealer *dealer) {
    Card card = dealer->deck[dealer->deck_idx];
    (dealer->deck_idx)++;
    return card;
}

void setup_players(Player players[TOTAL_PLAYERS]) {
    for (int i = 0; i < TOTAL_PLAYERS; i++) {
        Player p;

        p.player_number = i;
        p.chips = 100;

        players[i] = p;
    }
}

void setup_dealer(Dealer *dealer, Card deck[DECK_SIZE]) {
    dealer->deck = deck;
    dealer->deck_idx = 0;
}

void setup_table(Table *table, Dealer *dealer, Player players[TOTAL_PLAYERS]) {
    table->dealer = dealer;
    table->players = players;
    table->community_card_idx = 0;

    table->pot = 0;
    table->small_blind = BIG_BLIND / 2;
    table->big_blind = BIG_BLIND;

    table->small_blind_idx = 0;
    table->big_blind_idx = table->small_blind_idx + 1; // Big blind is 1 player more than small blind
}

void rotate_blinds(Table *table) {
    table->small_blind_idx = (table->small_blind_idx + 1) % TOTAL_PLAYERS;
    table->big_blind_idx = (table->small_blind_idx + 1) % TOTAL_PLAYERS;
}

void deal_hole_cards(Table *table) {
    const int DEAL_SIZE = 2;
    Dealer *dealer = (table->dealer);

    for (int i = 0; i < TOTAL_PLAYERS; i++) {
        Player *curr_player = &(table->players[i]);

        for (int j = 0; j < DEAL_SIZE; j++) {
            curr_player->cards[j] = deal_card(dealer);
        }
    }
}

void deal_community_card(Table *table, int cards_to_deal) {
    if (table->community_card_idx >= COMMUNITY_CARDS || table->community_card_idx + cards_to_deal >= COMMUNITY_CARDS) {
        printf("You can't deal community cards that go above the total %d\n", COMMUNITY_CARDS);
        return;
    }

    Dealer *dealer = table->dealer;
    for (int i = 0; i < cards_to_deal; i++) {
        table->community_cards[table->community_card_idx] = deal_card(dealer);
        (table->community_card_idx)++;
    }
}

Player* decide_winner(Table *table) {
    const int WINNING_HANDS = 10;

    // Array to store winning hand for each player. 
    int player_best_hand_rank[TOTAL_PLAYERS] = {0};

    // Find each player's best hand
    for (int i = 0; i < TOTAL_PLAYERS; i++) {
        // Combine community table cards + curr player cards into one array to simplify
        Card combined_cards[COMBINED_CARDS_SIZE];
        combine_cards(table->players[i].cards, table->community_cards, combined_cards);

        // Check for winning hand
        if (is_royal_flush(combined_cards)) {
            player_best_hand_rank[i] = ROYAL_FLUSH;
        } else if (is_straight_flush(combined_cards)) {
            player_best_hand_rank[i] = STRAIGHT_FLUSH;
        } // etc with all hands
        else {
            player_best_hand_rank[i] = HIGH_CARD;
        }  
    }

    int winner = 0;
    int best_rank = HIGH_CARD + 1;
    // find which player has best hand
    // TODO: handle ties
    for (int i = 0; i < TOTAL_PLAYERS; i++) {
        if (player_best_hand_rank[i] < best_rank) {
            best_rank = player_best_hand_rank[i];
            winner = i;
        }
    }

    return &(table->players[winner]);
}
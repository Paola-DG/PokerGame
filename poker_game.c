#include <stdio.h>
#include "utils.h"
#include "poker_game.h"

const int COMBINED_CARDS_SIZE = PLAYER_HOLE_CARDS + COMMUNITY_CARDS;

void display_main_menu() {
    CLEAR_SCREEN();
    printf("------------------------------------------------------------------------------------------\n");
    printf("                                     Texas Hold\'em - Poker Game \n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("\n--- Main Menu ---\n");
    printf("1. Start New Game\n");
    printf("2. View Rules\n");
    printf("q. Exit Program\n");
}

void show_rules(){
    CLEAR_SCREEN();
    printf("------------------------------------------------------------------------------------------\n");
    printf("                                    Texas Hold\'em - Poker Rules \n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("\n");
    
    printf(" GOAL \n");
    printf("    Win the pot, which is the total of all bets placed during the hand.\n");
    printf("\n");
    
    printf(" DEALING \n");
    printf("    Each player is dealt two cards face down, called [hole cards]. \n");
    printf("    The dealer then deals community cards face up in stages: \n");
    printf("        + The  flop: Three cards are dealt. \n");
    printf("        + The  turn: One card is dealt. \n");
    printf("        + The river: One final card is dealt. \n");
    
    printf("\n");
    printf(" BETTING \n");
    printf("    Players can check, call, raise, or fold. \n");
    printf("    The options available depend on what the previous players have done. \n");
    printf("        For example, if no one has bet yet, a player can check or bet. \n");
    printf("        If a player bets, others can call, raise, or fold. \n");
    printf("\n");
    
    printf(" WINNING \n");
    printf("    The player with the best hand at the end of the final betting round wins the pot. \n");
    printf("    If two players have the same hand, it's called a [split pot] or [tie]. \n");
    printf("\n");
    
    printf(" POKER HAND RANKINGS \n");
    printf("    1. Royal Flush \n");
    printf("        A Royal Flush is the best hand in poker and is made up of an ace, king, queen, \n");
    printf("        jack and ten of all the same suit. \n");
    printf("\n");
    
    printf("    2. Straight Flush \n");
    printf("        Five cards of the same suit in sequential order. \n");
    printf("\n");
    
    printf("    3. Four-of-a-Kind \n");
    printf("        Any four numericaly matching cards. \n");
    printf("\n");
    
    printf("    4. Full House \n");
    printf("        Combination of three of a kind and a pair in the same hand. \n");
    printf("\n");
    
    printf("    5. Flush \n");
    printf("        Five cards of the same suit, in any order. \n");
    printf("\n");
    
    printf("    6. Straight \n");
    printf("        Five cards of the same suit, in sequential order. \n");
    printf("\n");
    
    printf("    7. 3-of-a-Kind \n");
    printf("        Any three numerically matching cards. \n");
    printf("\n");
    
    printf("    8. Two Pair \n");
    printf("        Two different pairs in the same hand. \n");
    printf("\n");
    
    printf("    9. One Pair \n");
    printf("        Any two numerically matching cards. \n");
    printf("\n");
    
    printf("    10. High Card \n");
    printf("        The highest ranked card in your hand with an ace being the highest and two \n");
    printf("        being the lowest \n");
    printf("\n");
    
    printf("Press Q to go back: ");
    while (getch() != 'q') {}
}



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
    // Define the ranks required for a Royal Flush
    Rank royal_flush[] = { TEN, JACK, QUEEN, KING, ACE };
    const int ROYAL_FLUSH_SIZE = sizeof(royal_flush) / sizeof(royal_flush[0]);

    // Check each suit individually
    for (Suit s = HEARTS; s <= SPADES; s++) {
        int match_count = 0; // Track how many cards match the required ranks

        for (int i = 0; i < COMBINED_CARDS_SIZE; i++) {
            if (combined_cards[i].suit == s && combined_cards[i].rank == royal_flush[match_count]) {
                match_count++;
            }

            // Stop early if all required cards are found
            if (match_count == ROYAL_FLUSH_SIZE) {
                return 1; // Royal Flush found
            }
        }
    }
    return -1; // No Royal Flush
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
 * Accepts array of cards size COMBINED_CARDS_SIZE
 * Check card array for one pair
 * @returns - 1 if found or -1 if not found
 */
static int is_one_pair(Card combined_cards[COMBINED_CARDS_SIZE]) {
    int rank_counts[RANK_SIZE] = {0};

    // Count occurrences of each rank
    for (int i = 0; i < COMBINED_CARDS_SIZE; i++) {
        rank_counts[combined_cards[i].rank]++;
    }

    // Check for at least one pair
    for (int i = TWO; i < RANK_SIZE; i++) {
        if (rank_counts[i] == 2) {
            return 1; // Found a pair
        }
    }

    return -1; // No pair found
}

/**
 * Accepts array of cards size COMBINED_CARDS_SIZE
 * Check card array for two pair
 * @returns - 1 if found or -1 if not found
 */
static int is_two_pair(Card combined_cards[COMBINED_CARDS_SIZE]) {
    int rank_counts[RANK_SIZE] = {0};
    int pair_count = 0;

    // Count occurrences of each rank
    for (int i = 0; i < COMBINED_CARDS_SIZE; i++) {
        rank_counts[combined_cards[i].rank]++;
    }

    // Count the number of pairs
    for (int i = TWO; i < RANK_SIZE; i++) {
        if (rank_counts[i] == 2) {
            pair_count++;
        }
    }

    return (pair_count >= 2) ? 1 : -1; // Return 1 if two or more pairs found
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
    if (table->community_card_idx >= COMMUNITY_CARDS || table->community_card_idx + cards_to_deal > COMMUNITY_CARDS) {
        printf("You can't deal community cards that go above the total %d\n", COMMUNITY_CARDS);
        return;
    }

    Dealer *dealer = table->dealer;
    for (int i = 0; i < cards_to_deal; i++) {
        table->community_cards[table->community_card_idx] = deal_card(dealer);
        (table->community_card_idx)++;
    }
}

int decide_winner(Table *table, Player *winners[], int player_best_hand_rank[]) {
    const int WINNING_HANDS = 10;

    for (int i = 0; i < TOTAL_PLAYERS; i++) {
        Player *curr_player = &(table->players[i]);

        // Skip folded players
        if (curr_player->folded) {
            player_best_hand_rank[i] = WINNING_HANDS + 1; // Set rank to an invalid high value
            continue;
        }

        Card combined_cards[COMBINED_CARDS_SIZE];
        combine_cards(curr_player->cards, table->community_cards, combined_cards);

        // Determine best hand for this player
        if (is_royal_flush(combined_cards) == 1) {
            player_best_hand_rank[i] = ROYAL_FLUSH;
        } else if (is_straight_flush(combined_cards) == 1) {
            player_best_hand_rank[i] = STRAIGHT_FLUSH;
        } else if (is_four_of_a_kind(combined_cards) == 1) {
            player_best_hand_rank[i] = FOUR_OF_A_KIND;
        } else if (is_full_house(combined_cards) == 1) {
            player_best_hand_rank[i] = FULL_HOUSE;
        } else if (is_flush(combined_cards) == 1) {
            player_best_hand_rank[i] = FLUSH;
        } else if (is_a_straight(combined_cards) == 1) {
            player_best_hand_rank[i] = STRAIGHT;
        } else if (is_three_of_a_kind(combined_cards) == 1) {
            player_best_hand_rank[i] = THREE_OF_A_KIND;
        } else if (is_two_pair(combined_cards) == 1) {
            player_best_hand_rank[i] = TWO_PAIR;
        } else if (is_one_pair(combined_cards) == 1) { 
            player_best_hand_rank[i] = ONE_PAIR;
        } else {
            player_best_hand_rank[i] = HIGH_CARD;
        }
    }

    // Step 2: Determine the best hand rank and find winners
    int best_rank = WINNING_HANDS + 1; // Initialize with the worst possible rank
    int winner_count = 0;

    for (int i = 0; i < TOTAL_PLAYERS; i++) {
        if (player_best_hand_rank[i] < best_rank) {
            // New best rank found
            best_rank = player_best_hand_rank[i];
            winner_count = 1;
            winners[0] = &(table->players[i]); // Update the winner list
        } else if (player_best_hand_rank[i] == best_rank) {
            // Tie: Add player to winners list
            winners[winner_count++] = &(table->players[i]);
        }
    }

    return winner_count; // Return the number of winners
}
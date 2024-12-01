#include "poker_game.h"

const int COMBINED_CARDS_SIZE = PLAYER_HOLE_CARDS + COMMUNITY_CARDS;

static void combine_cards(Card hole_cards[PLAYER_HOLE_CARDS], Card community_cards[COMMUNITY_CARDS], Card combined_cards[COMBINED_CARDS_SIZE]) {
    int i = 0;
    for (int j = 0; j < PLAYER_HOLE_CARDS; j++, i++) {
        combined_cards[i] = hole_cards[j];
    }

    for (int j = 0; j < COMMUNITY_CARDS; j++, i++) {
        combined_cards[i] = community_cards[j];
    }
}

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

static int is_royal_flush(Card hole_cards[PLAYER_HOLE_CARDS], Card community_cards[COMMUNITY_CARDS]) {
    Card combined_cards[COMBINED_CARDS_SIZE];
    Rank royal_flush[] = { TEN, JACK, QUEEN, KING, ACE };

    combine_cards(hole_cards, community_cards, combined_cards);

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

static int is_straight_flush(Card hole_cards[PLAYER_HOLE_CARDS], Card community_cards[COMMUNITY_CARDS]) {
    Card combined_cards[COMBINED_CARDS_SIZE];
    int STRAIGHT_FLUSH_SIZE = 5;

    combine_cards(hole_cards, community_cards, combined_cards);
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

static int is_four_of_a_kind(Card hole_cards[PLAYER_HOLE_CARDS], Card community_cards[COMMUNITY_CARDS]) {
    Card combined_cards[COMBINED_CARDS_SIZE];
    const int HAND_SIZE = 4;

    combine_cards(hole_cards, community_cards, combined_cards);

    int rank_counts[RANK_SIZE] = {0};

    for (int i = 0; i < COMBINED_CARDS_SIZE; i++) {
        rank_counts[combined_cards[i].rank]++;
        if (rank_counts[combined_cards[i].rank] == HAND_SIZE) {
            return 1;
        }
    }

    return -1;
}

static int is_full_house(Card hole_cards[PLAYER_HOLE_CARDS], Card community_cards[COMMUNITY_CARDS]) {
    Card combined_cards[COMBINED_CARDS_SIZE];

    combine_cards(hole_cards, community_cards, combined_cards);

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

static int is_flush(Card hole_cards[PLAYER_HOLE_CARDS], Card community_cards[COMMUNITY_CARDS]) {
    Card combined_cards[COMBINED_CARDS_SIZE];
    const int FLUSH_SIZE = 5;

    combine_cards(hole_cards, community_cards, combined_cards);

    for (Suit s = HEARTS; s <= SPADES; s++) {
        int match_count = 0;
        for (int i = 0; i < COMBINED_CARDS_SIZE; i++) {
            if (combined_cards[i].suit == s) { match_count++; }
            if (match_count == FLUSH_SIZE) { return 1;}
        }
    }

    return -1;
}

// TODO: Add ace-low check (A, 2, 3, 4, 5) - Ace is being used as high card instead of low
static int is_a_straight(Card hole_cards[PLAYER_HOLE_CARDS], Card community_cards[COMMUNITY_CARDS]) {
    Card combined_cards[COMBINED_CARDS_SIZE];
    const int STRAIGHT_SIZE = 5;

    combine_cards(hole_cards, community_cards, combined_cards);
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

static int is_three_of_a_kind(Card hole_cards[PLAYER_HOLE_CARDS], Card community_cards[COMMUNITY_CARDS], Card combined_cards[COMBINED_CARDS_SIZE]) {
    
}


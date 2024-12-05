#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "deck.h"

void initialize_deck(Card deck[DECK_SIZE]) {
    const int SET_SIZE = DECK_SIZE / 4;
    for (int i = HEARTS; i <= SPADES; i++) {
        for (int j = TWO; j <= ACE; j++) {
            deck[i * SET_SIZE + j - TWO].rank = j;
            deck[i * SET_SIZE + j - TWO].suit = i;
        }
    }
}

void shuffle_deck(Card deck[DECK_SIZE]) {
    for (int i = DECK_SIZE - 1; i > 0; i--) {
        int rand_idx = rand() % (i + 1);
        Card tmp = deck[i];
        deck[i] = deck[rand_idx];
        deck[rand_idx] = tmp;
    }
}

void get_suit(Suit s, char *suit) {
        switch (s) {
            case HEARTS:
                strcpy(suit, "HEARTS");
                break;
            case DIAMONDS:
                strcpy(suit, "DIAMONDS");
                break;
            case CLUBS:
                strcpy(suit, "CLUBS");
                break;
            case SPADES:
                strcpy(suit, "SPADES");
                break;
        }
}

void get_rank(Rank r, char *rank) {
    switch (r) {
        case JACK:
            strcpy(rank, "JACK");
            break;
        case QUEEN:
            strcpy(rank, "QUEEN");
            break;
        case KING:
            strcpy(rank, "KING");
            break;
        case ACE:
            strcpy(rank, "ACE");
            break;
        default:
            sprintf(rank, "%d", r);
    }
}

void print_card(Card card) {
    char suit[16], rank[16];

    get_suit(card.suit, suit);
    get_rank(card.rank, rank);

    printf("%s %s\n", suit, rank);
}

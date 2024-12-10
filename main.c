#include <stdio.h>
#include <time.h>

#include "poker_game.h"

#define PLAYER_IDX 1

void start_game(void);

int main(){
    // set random seed
    srand(time(NULL));

    // Game loop
    while (1) {
        display_main_menu();
        char input = getch();
        switch (input) {
            case '1':
                CLEAR_SCREEN();
                start_game();
                break;
            case '2':
                show_rules();
                break;
        }

        if (input == 'q') {
            break;
        }
    }
    return 0;
}

void setup_game(Table *table, Dealer *dealer, Player players[TOTAL_PLAYERS], Card deck[DECK_SIZE]) {
    initialize_deck(deck);
    shuffle_deck(deck);

    setup_players(players);
    setup_dealer(dealer, deck);
    setup_table(table, dealer, players);
}

char bot_decision(Player *bot) {
    if (bot->chips <= 0) return 'f'; // Fold if no chips

    int decision = rand() % 100; //  random number 0-99

    if (decision < 5) {
        return 'r'; // 5% chance to raise
    } else if (decision < 85) {
        return 'c'; // 80% chance to call
    } else {
        return 'f'; // 15% chance to fold
    }
}

void betting_round(Table *table, int player_index) {
    int active_players = TOTAL_PLAYERS;
    int betting_complete = 0;
    int has_acted[TOTAL_PLAYERS] = {0};  // Track if each player has acted

    while (!betting_complete) {
        betting_complete = 1;

        for (int i = 0; i < TOTAL_PLAYERS; i++) {
            Player *curr_player = &(table->players[i]);
            // Skip folded players
            if (curr_player->folded) {
                continue;
            }

            // Skip players who have already acted and matched the current bet
            if (has_acted[i] && curr_player->current_bet == table->current_bet) {
                continue;
            }

            if (i == player_index) {
                // Human
                printf("\nPlayer %d (You) - Chips: %d\n", i, curr_player->chips);
                printf("Action? (c: call, r: raise, f: fold): ");
                char action = getch();
                printf("%c\n", action); 

                switch (action) {
                    case 'c': // Call
                        {
                            int call_amount = table->current_bet - curr_player->current_bet;
                            if (curr_player->chips < call_amount) {
                                printf("You went all-in with %d chips.\n", curr_player->chips);
                                call_amount = curr_player->chips;
                                curr_player->folded = 1; // All-in players are locked in
                                active_players--;
                            }
                            curr_player->chips -= call_amount;
                            curr_player->current_bet += call_amount;
                            table->pot += call_amount;
                        }
                        break;

                    case 'r': // Raise
                        {
                            printf("Enter raise amount: ");
                            int raise_amount;
                            scanf("%d", &raise_amount);

                            if (raise_amount > curr_player->chips) {
                                printf("You don't have enough chips to raise that amount!\n");
                                i--;  // Retry input
                                continue;
                            }

                            printf("You raised by %d chips.\n", raise_amount);
                            curr_player->chips -= raise_amount;
                            curr_player->current_bet += raise_amount;
                            table->current_bet = curr_player->current_bet;
                            table->pot += raise_amount;
                            betting_complete = 0;  // Betting continues
                        }
                        break;

                    case 'f': // Fold
                        printf("You folded.\n");
                        curr_player->folded = 1;
                        active_players--;
                        break;

                    default:
                        printf("Invalid action. Try again.\n");
                        i--;  // Retry input
                        break;
                }
            } else {
                // Bot player action
                char bot_action = bot_decision(curr_player);

                switch (bot_action) {
                    case 'c': // Call
                        {
                            int bot_call_amount = table->current_bet - curr_player->current_bet;
                            if (curr_player->chips < bot_call_amount) {
                                printf("Player %d (Bot) went all-in with %d chips.\n", i, curr_player->chips);
                                bot_call_amount = curr_player->chips;
                                curr_player->folded = 1;
                                active_players--;
                            }
                            printf("Player %d (Bot) called with %d chips.\n", i, bot_call_amount);
                            curr_player->chips -= bot_call_amount;
                            curr_player->current_bet += bot_call_amount;
                            table->pot += bot_call_amount;
                        }
                        break;

                    case 'r': // Raise
                        {
                            int bot_raise_amount = (rand() % 10) + 1;  // raise between 1-10
                            if (curr_player->chips < bot_raise_amount) {
                                printf("Player %d (Bot) went all-in with %d chips.\n", i, curr_player->chips);
                                bot_raise_amount = curr_player->chips;
                                curr_player->folded = 1;
                                active_players--;
                            }
                            printf("Player %d (Bot) raised by %d chips.\n", i, bot_raise_amount);
                            curr_player->chips -= bot_raise_amount;
                            curr_player->current_bet += bot_raise_amount;
                            table->current_bet = curr_player->current_bet;
                            table->pot += bot_raise_amount;
                            betting_complete = 0;
                        }
                        break;

                    case 'f': // Fold
                        printf("Player %d (Bot) folded.\n", i);
                        curr_player->folded = 1;
                        active_players--;
                        break;
                }
            }

            // Mark player as having acted
            has_acted[i] = 1;
        }

        // Check if all active players have matched the current table bet or folded
        for (int i = 0; i < TOTAL_PLAYERS; i++) {
            Player *curr_player = &(table->players[i]);
            if (!curr_player->folded && curr_player->current_bet < table->current_bet) {
                betting_complete = 0; 
                break;
            }
        }
    }

    printf("\nBetting round complete. Pot size: %d chips\n", table->pot);
    printf("Press any key to continue to next round.\n");
    getch();
}

void print_player_cards(Table *table) {
    printf("Your Hole Cards:\n");
    for (int j = 0; j < PLAYER_HOLE_CARDS; j++) {
        print_card(table->players[PLAYER_IDX].cards[j]);
    }
    printf("\n");
}

void print_community_cards(Table *table) {
    printf("Community Cards:\n");
    for (int i = 0; i < table->community_card_idx; i++) {
        print_card(table->community_cards[i]);
    }
    printf("\n");
}

void preflop(Table *table) {
    CLEAR_SCREEN();
    printf("------------------------------------------------------------------------------------------\n");
    printf("                                     Texas Hold'em - Poker Game \n");
    printf("------------------------------------------------------------------------------------------\n");

    printf("\n--- Pre-Flop ---\n");
    deal_hole_cards(table);

    print_player_cards(table);

    // Initialize preflop stage variables
    table->current_bet = table->big_blind;  // Start with the big blind amount
    table->pot = 0;

    // Step 2: Big Blind and Small Blind Contributions
    Player *small_blind_player = &(table->players[table->small_blind_idx]);
    Player *big_blind_player = &(table->players[table->big_blind_idx]);

    small_blind_player->current_bet = table->small_blind;
    big_blind_player->current_bet = table->big_blind;

    table->pot += table->small_blind + table->big_blind;

    printf("\n--- Pre-Flop Betting Round ---\n");
    printf("Small Blind: Player %d bets %d\n", table->small_blind_idx, table->small_blind);
    printf("Big Blind: Player %d bets %d\n\n", table->big_blind_idx, table->big_blind);

    betting_round(table, PLAYER_IDX);
}

void flop(Table *table) {
    CLEAR_SCREEN();
    printf("\n--- The Flop ---\n");
    deal_community_card(table, 3);

    print_player_cards(table);
    print_community_cards(table);

    betting_round(table, PLAYER_IDX);
}

void turn(Table *table) {
    CLEAR_SCREEN();
    printf("\n--- The Turn ---\n");
    deal_community_card(table, 1);

    print_player_cards(table);
    print_community_cards(table);

    betting_round(table, PLAYER_IDX);
}

void river(Table *table) {
    CLEAR_SCREEN();
    printf("\n--- The River ---\n");
    deal_community_card(table, 1);

    print_player_cards(table);
    print_community_cards(table);

    betting_round(table, PLAYER_IDX);
}

void showdown(Table *table) {
    printf("\n--- Showdown ---\n");

    Player *winners[TOTAL_PLAYERS]; 
    int player_best_hand_rank[TOTAL_PLAYERS] = {0}; // Store best hand ranks for all players

    int winner_count = decide_winner(table, winners, player_best_hand_rank);

    printf("\n--- Results ---\n");
    for (int i = 0; i < TOTAL_PLAYERS; i++) {
        printf("Player %d: ", i);
        if (table->players[i].folded) {
            printf("Folded\n");
        } else {
            printf("Best Hand: ");
            switch (player_best_hand_rank[i]) {
                case ROYAL_FLUSH: printf("Royal Flush\n"); break;
                case STRAIGHT_FLUSH: printf("Straight Flush\n"); break;
                case FOUR_OF_A_KIND: printf("Four of a Kind\n"); break;
                case FULL_HOUSE: printf("Full House\n"); break;
                case FLUSH: printf("Flush\n"); break;
                case STRAIGHT: printf("Straight\n"); break;
                case THREE_OF_A_KIND: printf("Three of a Kind\n"); break;
                case TWO_PAIR: printf("Two pair\n"); break;
                case ONE_PAIR: printf("One pair\n"); break;
                default: printf("High Card\n"); break;
            }
        }
    }

    if (winner_count == 1) {
        // Single winner
        printf("\nPlayer %d wins the pot of %d chips!\n", winners[0]->player_number, table->pot);
        winners[0]->chips += table->pot;
    } else {
        // Tie: divide pot equally
        printf("\nIt's a tie! Pot of %d chips split between %d players.\n", table->pot, winner_count);
        int split_amount = table->pot / winner_count;
        for (int i = 0; i < winner_count; i++) {
            winners[i]->chips += split_amount;
        }
    }

    printf("Press any key to continue\n");
    getch();
}



void start_game(void) {
    int player_chips = 0, has_chips = 0;
    while (1) {
        Player players[TOTAL_PLAYERS];
        Dealer dealer;
        Table table;
        Card deck[DECK_SIZE];

        setup_game(&table, &dealer, players, deck);

        if (has_chips) {
            players[PLAYER_IDX].chips = player_chips;
        }
        preflop(&table);
        flop(&table);
        turn(&table);
        river(&table);
        showdown(&table);

        int curr_chips = players[PLAYER_IDX].chips;
        if ( curr_chips > 0) {
            player_chips = curr_chips;
            has_chips = 1;
        }

        printf("Do you want to play another game? y/n: ");
        int input;
        do {
            input = getch();

        } while ( input != 'y' && input != 'n');
        
        if (input == 'n') {
            break;
        }
    }
}

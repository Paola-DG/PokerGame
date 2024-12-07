#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h> //Use {system("clear");} to clear screen.

#include "poker_game.h"

//DEFINE variables
#define BLIND_BET 1
#define PLAYER_IDX 1

//GLOBAL variables
int userInput; //variable that determines if the user wants to start new game (1), view rules (2), or exit the program (0). 
int userMainMenu; //variable that determines if the user wants to go to the main menu (1).
int playerTurn; //variable that determines if the user wants to fold(0), call(1), or raise(2).
char anotherRound; //varable that determines if the user wants to play another round (Y or N).

float userChips; //variable that stores the chips that the user has.
float raiseAmount; //variable that stores the amount of money the bet has increased.
float currentPot; //variable that stores the amount of money the pot has.
int numRounds; //variable that stores the number of rounds that the user has played (before going to the main menu).
int bigBlindBet = BLIND_BET * 2; //variable that stores the amount that the big blind bet cost.

Player players[TOTAL_PLAYERS];
Dealer dealer;
Table table;
Card deck[DECK_SIZE];

//function prototype
void displayMainMenu(void); //function that displays the main menu of the program.
void showRules(void); //function that displays the rules of the  Texas Hold’em - Poker Rules.
void newGame(void); //function that displays the poker game.
void showHeader(int newGame); //function that displays the title (and if newGame = 1, will display the blind bets and wallet).
void anotherGame(void); //
void playerActions(void); //function that 
void dealerButton(void); //function that displays if you are the dealer, small blind, or big blind.

void preflop(Table *table);

int main(){
    //local variables
    userChips = 0.000000;
    numRounds = 0;
    
    // MAIN MENU window
    displayMainMenu();
    
    while(userInput != 0 && userInput != 1 && userInput != 2){
        printf(" Invalid Input. Type again your response \n");
        printf(" Player Choice: "); //to-do: delete after input
        scanf("%d", &userInput);
    }
    
    if(userInput == 0){
        // EXIT - Close the program
        system("clear");
        printf(" Program Closed. Have a great day!");
    }else if(userInput == 2){
        // VIEW RULES
        system("clear");
        showRules(); //new window - Show Rules window.
    }else{
        // NEW GAME
        system("clear");
        newGame(); //new window - New Game window.
    }
    return 0;
}

//functions definition
void displayMainMenu(void){
    showHeader(0); //showing title
    printf("\n");
    printf("---------------------------\n");
    printf(" Start New Game || press 1 \n");
    printf("---------------------------\n");
    printf("---------------------------\n");
    printf("   View Rules   || press 2 \n");
    printf("---------------------------\n");
    printf("---------------------------\n");
    printf("  Exit Program  || press 0 \n");
    printf("---------------------------\n");
    printf("\n");
    
    printf(" Player Choice: ");//to-do: delete after input
    scanf("%d", &userInput);
}

void showRules(void){
    printf("------------------------------------------------------------------------------------------\n");
    printf("                                    Texas Hold’em - Poker Rules \n");
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
    
    //Go back to Main Menu.
    printf(" Do you want to return to Main Menu? || press 1: ");
    scanf("%d", &userMainMenu);
    
    while(userMainMenu != 1){
        printf(" Do you want to return to Main Menu? || press 1: ");
        scanf("%d", &userMainMenu);
    }
    
    if(userMainMenu == 1){
        userMainMenu = 0;
        system("clear");
        main(); //Go back to main function.
    }
}

void newGame(void){
    //local variables
    int minToGamble = bigBlindBet * 4; //variable that stores the minimum amout the user needs to be able to gamble.
    currentPot = bigBlindBet;
    
    srand(time(NULL)); //initializes the rand() function, giving different cards.
    numRounds++;
    showHeader(1); //showing title and blind bets

    if(userChips != 0.000000){
       // SETUP NEXT ROUND
       if(userChips < minToGamble){
           printf(" You do not have enough money to keep playing. Go back to main menu to start a new game! \n");
           while(userMainMenu != 1){
                printf(" Press 1 to return to Main Menu: ");
                scanf("%d", &userMainMenu);
            }
            
            if(userMainMenu == 1){
                userMainMenu = 0;
                system("clear");
                main(); //Go back to main function.
            }
            
       }else{
            //shuffle cards
            initialize_deck(deck);
            shuffle_deck(deck);
        
            //assign blinds - first round, user has the dealer button
            setup_players(players);
            setup_dealer(&dealer, deck);
            setup_table(&table, &dealer, players);
        
            //assign dealer button
            system("clear");
            showHeader(3);
            
            //deal hole cards
            preflop(&table);
            
            //pre-flop betting round
            playerActions();
            
       }
        
    }else{
        // SETUP NEW GAME
        printf(" Enter the amount of money you want to gamble: $"); //initialize chips
        scanf("%f", &userChips);
        
        while(userChips <= 0 || userChips < minToGamble){
            printf(" Invalid Input. Type again your response \n");
            printf(" Enter the amount of money you want to gamble: $");
            scanf("%f", &userChips);
        }
    
        //shuffle cards
        initialize_deck(deck);
        shuffle_deck(deck);
        
        //
        setup_players(players);
        setup_dealer(&dealer, deck);
        setup_table(&table, &dealer, players);
        
        //assign dealer button
        system("clear");
        showHeader(2);
        
        //deal hole cards
        preflop(&table);
        
        //pre-flop betting round
        playerActions();
        
        //flop betting round
        system("clear");
        showHeader(4);
        playerActions();
        
        //turn betting round
        system("clear");
        showHeader(4);
        playerActions();
        
        //final betting round
        system("clear");
        showHeader(4);
        playerActions();
        
        //determine winner
        system("clear");
        showHeader(5);
        
        anotherGame();
    }
}

void anotherGame(void){
    printf(" End of the game. Wallet: %.2f \n", userChips);
    printf(" Do you want to play another round? (Y/N): ");
    scanf("%s", &anotherRound);
            
    while(anotherRound != 'Y' && anotherRound != 'y' && anotherRound != 'N' && anotherRound != 'n'){
        printf(" Invalid Input. Type again your response \n");
        printf(" Do you want to play another round? (Y/N): ");
        scanf("%s", &anotherRound);
    }
    if(anotherRound == 'Y' || anotherRound == 'y'){
        system("clear");
        newGame(); //Go back to newGame window.
    }else{
        system("clear");
        main(); //Go back to Main window.
    }
}

void preflop(Table *table){
    deal_hole_cards(table);
    printf("Your hole cards:\n");
    for (int i = 0; i < 2; i++) {
        print_card(table->players[PLAYER_IDX].cards[i]);
    }
}

void playerActions(void){
    if(userChips <= 0){
        printf(" You do not have enough money to keep playing. Go back to main menu to start a new game! \n");
           while(userMainMenu != 1){
                printf(" Press 1 to return to Main Menu: ");
                scanf("%d", &userMainMenu);
            }
            
            if(userMainMenu == 1){
                userMainMenu = 0;
                system("clear");
                main(); //Go back to main function.
            }
    }else{
        printf("\n");
        printf("---------------------------\n");
        printf(" Fold  || press 0 \n");
        printf("---------------------------\n");
        printf("---------------------------\n");
        printf(" Call  || press 1 \n");
        printf("---------------------------\n");
        printf("---------------------------\n");
        printf(" Raise || press 2 \n");
        printf("---------------------------\n");
        printf("\n");
        
        printf(" Player Choice: ");//to-do: delete after input
        scanf("%d", &playerTurn);
        
        while(playerTurn != 0 && playerTurn != 1 && playerTurn != 2){
            printf(" Invalid Input. Type again your response \n");
            printf(" Player Choice: "); //to-do: delete after input
            scanf("%d", &playerTurn);
        }
        if(playerTurn == 0){
           anotherGame();
           
        }else if(playerTurn == 1){
            printf(" CALL \n");
            
        }else{
            printf(" Enter the amount of money you want to raise the bet: $");
            scanf("%f", &raiseAmount);
            
            int x = 0;
            while( x != 1){
                if(raiseAmount <= currentPot){
                    printf(" To raise, the amount has to be greater that $%.2f \n", currentPot);
                    printf(" Type again your bet: $");
                    scanf("%f", &raiseAmount);
                }else if(raiseAmount > userChips){
                    printf(" You do not have enough money to bet. Wallet: $%.2f \n", userChips);
                    printf(" Type again your bet: $");
                    scanf("%f", &raiseAmount);
                }else{
                    userChips -= raiseAmount;
                    currentPot += raiseAmount;
                    x = 1;
                }
            }
            
        }
    }
}

void dealerButton(void){
    if(numRounds %3 == 2){
        printf(" You are the Big Blind \n");
        userChips -= bigBlindBet;
    }else if(numRounds % 3 == 0){
         printf(" You are the Small Blind \n");
         userChips -= BLIND_BET;
    }else{
        printf(" You have the Dealer Button \n");
    }
}

void showHeader(int newGame){
    //local variables
    int minToGamble = bigBlindBet * 4; //variable that stores the minimum amout the user needs to be able to gamble.

    printf("------------------------------------------------------------------------------------------\n");
    printf("                                     Texas Hold’em - Poker Game \n");
    printf("------------------------------------------------------------------------------------------\n");
    
    switch (newGame){
        case 1:
        printf("--------------------------------------------------------------------\n");
        printf(" Blind Bet: $%d | Big Blind Bet: $%d | Minimum amount to play: $%d  \n", BLIND_BET, bigBlindBet, minToGamble);
        printf("--------------------------------------------------------------------\n");
    
        printf("--------------------------------------------------------------------\n");
        printf(" Welcome to Round %d | Wallet: $%.2f \n", numRounds, userChips);
        printf("--------------------------------------------------------------------\n");
        break;
        
        case 2:
        printf("--------------------------------------------------------------------\n");
        dealerButton();
        printf("--------------------------------------------------------------------\n");
        
        printf("--------------------------------------------------------------------\n");
        printf(" Wallet: $%.2f \n", userChips);
        printf("--------------------------------------------------------------------\n");
        break;
        
        case 3:
        printf("--------------------------------------------------------------------\n");
        dealerButton();
        printf("--------------------------------------------------------------------\n");
        
        printf("--------------------------------------------------------------------\n");
        printf(" Welcome to Round %d | Wallet: $%.2f \n", numRounds, userChips);
        printf("--------------------------------------------------------------------\n");
        break;
        
        case 4:
        printf("--------------------------------------------------------------------\n");
        printf(" Pot: $%.2f | Wallet: $%.2f \n", currentPot, userChips);
        printf("--------------------------------------------------------------------\n");
        
        printf("--------------------------------------------------------------------\n");
        printf(" Your Hole Cards: \n");
        printf("--------------------------------------------------------------------\n");
        
        printf("--------------------------------------------------------------------\n");
        printf(" Table Hole Cards: \n");
        printf("--------------------------------------------------------------------\n");
        break;
        
        case 5:
        printf("--------------------------------------------------------------------\n");
        printf(" Table Hole Cards: \n");
        printf("--------------------------------------------------------------------\n");
        
        printf("--------------------------------------------------------------------\n");
        printf(" Your Poker Hand:       X   |   Your Cards:     X\n");
        printf(" Bobby's Poker Hand:    X   |   Bobby's Cards:  X\n");
        printf(" Robby's Poker Hand:    X   |   Robby's Cards:  X\n");
        printf("--------------------------------------------------------------------\n");
        
        printf("--------------------------------------------------------------------\n");
        printf(" Winner X, earns $%.2f \n", currentPot);
        printf("--------------------------------------------------------------------\n");
        
        
        
        
        break;
        
    }

}

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h> //Use {system("clear");} to clear screen.

//DEFINE variables
#define BLIND_BET 1
#define DECK_SIZE 52

//STRUCT data types
typedef struct{
    int face;
    int suit;
}Card; //e.g. two hearts.

typedef struct{
    Card cards[5];
}Hand; //e.g. User's Cards[two hearts, queen spades] + Table Cards[six diamonds, seven clubs, four spades].

typedef struct{
    Card deckCards[DECK_SIZE];
    int numCardsDealt;
}Deck;

//GLOBAL variables
int userInput; //variable that determines if the user wants to start new game (1), view rules (2), or exit the program (0). 
int userMainMenu; //variable that determines if the user want to go to the main menu (1).

float userChips; //variable that stores the chips that the user has.
int numRounds; //variable that stores the number of rounds that the user has played (before going to the main menu).
int bigBlindBet = BLIND_BET * 2; //variable that stores the amount that the big blind bet cost.


struct Hand handUser, handBot1, handBot2; //variables that store the hand(cards) that each user/bot has.
struct Deck deck; //variable that stores the 52 cards of the set.

char *faceStrings[] = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
char *suitStrings[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
char *rankStrings[] = {"Royal Flush", "Straight Flsuh", "Four-of-a-Kind", "Full House", "Flush", "Straight", "Three-of-a-Kind", "Two Pair", "One Pair", "High Card"};

//function prototype
void displayMainMenu(void); //function that displays the main menu of the program.
void showRules(void); //function that displays the rules of the  Texas Hold’em - Poker Rules.
void newGame(void); //function that displays the poker game.
void showHeader(int newGame); //function that display the title (and if newGame = 1, will display the blind bets and wallet).

void generateHands(void); //function that give to the players 2 cards (alternating giving).
struct Card dealCard(); //

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

struct Card dealCard(){
    
}

void generateHands(void){
    for(int i = 0; i < 2; i++){
        handUser.cards[i] = dealCard();
        handBot1.cards[i] = dealCard();
        handBot2.cards[i] = dealCard();
    }
}

void newGame(void){
    //local variables
    int minToGamble = bigBlindBet * 4; //variable that stores the minimum amout the user needs to be able to gamble.

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
            //assign blinds
            
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
        
        system("clear");
        showHeader(1);
        
        //shuffle cards
        //assign blinds - first round, user has the dealer button
    }
}

void showHeader(int newGame){
    //local variables
    int minToGamble = bigBlindBet * 4; //variable that stores the minimum amout the user needs to be able to gamble.

    printf("------------------------------------------------------------------------------------------\n");
    printf("                                     Texas Hold’em - Poker Game \n");
    printf("------------------------------------------------------------------------------------------\n");
    
    if(newGame == 1){
        printf("--------------------------------------------------------------------\n");
        printf(" Blind Bet: $%d | Big Blind Bet: $%d | Minimum amount to play: $%d  \n", BLIND_BET, bigBlindBet, minToGamble);
        printf("--------------------------------------------------------------------\n");
    
        printf("--------------------------------------------------------------------\n");
        printf(" Welcome to Round %d | Wallet: $%.2f \n", numRounds, userChips);
        printf("--------------------------------------------------------------------\n");  
    }

}


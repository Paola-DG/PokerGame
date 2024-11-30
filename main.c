#include <stdio.h>
#include <stdlib.h> //Use {system("clear");} to clear screen

//GLOBAL variables
int userInput; //variable that determines if the user wants to start new game (1), view rules (2), or exit the program (0). 
int userMainMenu; //variable that determines if the user want to go to the main menu (1).

//function prototype
int displayMainMenu(void); //function that display the main menu of the program.
void showRules(void); //function that display the rules of the  Texas Hold’em - Poker Rules.

int main(){
    //local variables
    
    
    // MAIN MENU window
    displayMainMenu();
    
    while(userInput != 0 && userInput != 1 && userInput != 2){
        printf("Invalid Input. Type again your response \n");
        printf("Player Choice: "); //to-do: delete after input
        scanf("%d", &userInput);
    }
    
    if(userInput == 0){
        // EXIT - Close the program
        printf("EXIT PROGRAM");
    }else if(userInput == 2){
        // VIEW RULES
        system("clear");
        showRules(); //new window - Show Rules window.
    }else{
        // NEW GAME
        system("clear");
        printf("NEW GAME"); //new window - New Game window.
    }
    return 0;
}

//functions definition
int displayMainMenu(void){
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
    
    printf("Player Choice: ");//to-do: delete after input
    scanf("%d", &userInput);
}

void showRules(void){
    printf("------------------------------------------------------------------------------------------\n");
    printf("                                    Texas Hold’em - Poker Rules \n");
    printf("------------------------------------------------------------------------------------------\n");
    printf("\n");
    
    printf("GOAL \n");
    printf("    Win the pot, which is the total of all bets placed during the hand.\n");
    printf("\n");
    
    printf("DEALING \n");
    printf("    Each player is dealt two cards face down, called [hole cards]. \n");
    printf("    The dealer then deals community cards face up in stages: \n");
    printf("        + The  flop: Three cards are dealt. \n");
    printf("        + The  turn: One card is dealt. \n");
    printf("        + The river: One final card is dealt. \n");
    
    printf("\n");
    printf("BETTING \n");
    printf("    Players can check, call, raise, or fold. \n");
    printf("    The options available depend on what the previous players have done. \n");
    printf("        For example, if no one has bet yet, a player can check or bet. \n");
    printf("        If a player bets, others can call, raise, or fold. \n");
    printf("\n");
    
    printf("WINNING \n");
    printf("    The player with the best hand at the end of the final betting round wins the pot. \n");
    printf("    If two players have the same hand, it's called a [split pot] or [tie]. \n");
    printf("\n");
    
    printf("POKER HAND RANKINGS \n");
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
    printf("Do you want to return to Main Menu? || press 1: ");
    scanf("%d", &userMainMenu);
    
    while(userMainMenu != 1){
        printf("Do you want to return to Main Menu? || press 1: ");
        scanf("%d", &userMainMenu);
    }
    
    if(userMainMenu == 1){
        system("clear");
        main(); //Go back to main function.
    }
}

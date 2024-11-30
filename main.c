#include <stdio.h>
#include <stdlib.h> //Use {system("clear");} to clear screen

int main()
{
    // variables
    int userInput;
    
    // MAIN MENU
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
    
    printf("Player Choice: ");//delete after input
    scanf("%d", &userInput);
    
    while(userInput != 0 && userInput != 1 && userInput != 2){
        printf("Invalid Input. Type again your response \n");
        printf("Player Choice: "); //delete after input
        scanf("%d", &userInput);
    }
    
    if(userInput == 0){
        // EXIT
        printf("EXIT PROGRAM");
    }else if(userInput == 2){
        // VIEW RULES
        system("clear");
        printf("VIEW RULES"); //new window - Show Rules window
    }else{
        // NEW GAME
        system("clear");
        printf("NEW GAME"); //new window - New Game window
    }
    return 0;
}

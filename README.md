# Poker Game
*Project proposed by Salomon Aduen and Paola Dorado G.*

*C language*

  Poker is a popular card game played all around the world, known for its combination of strategy, probability, and chance. 
  
  In this project, we aim to develop a terminal-based Poker inspired on the Texas Hold’em game. In our implementation one human player competes against three computer-controlled opponents. The program will simulate the full game experience, including dealing cards, managing blinds, betting rounds, and determining the winner based on standard poker hand rankings. The player will start with an initial amount of chips and will continue until all are lost. 

## Overview
  This implementation will help us understand the logic behind game mechanics, basic decision-making algorithms, and card shuffling. The program will consist of the following steps:
  * The program will begin by displaying a terminal menu to the user. It will have options such as "Start New Game," "View Rules," or "Exit." If the user selects "Start New Game," the program will proceed with initializing the game setup.
  * The program will initialize a standard 52-card deck and shuffle it randomly. Each player will then be assigned a starting amount of chips, and the roles of small blind, and big blind will be set for the first round.
  * The program will deal two hole cards to each player and display the human player’s cards on the screen. The program will also post the small and big blinds automatically for the respective players, display the current pot, and prompt the player to make their first decision.
  * The program will manage the pre-flop betting round, where the player is given 2 hole cards and can choose to fold, call, or raise using menu options displayed in the terminal.
  * The program will continue to the flop, where three community cards are revealed. The cards will be displayed in the terminal, and a second betting round will take place with the same options as before.
  * The program will deal a fourth and fifth community card, one at a time, displaying the updated board in the terminal after each card. A betting round will follow each card reveal.
  * At the end of the betting rounds, if there are still more than 1 player in the game, the program will reveal the hole cards for all players and determine the winner based on who has the best five-card hand.
  * The program will ask the player if they want to play another round or exit.

##

**Department of Electrical and Computer Engineering**

**Florida International University**

**EEL 2880 – C Programming for Embedded Systems**

**Fall 2024**




  

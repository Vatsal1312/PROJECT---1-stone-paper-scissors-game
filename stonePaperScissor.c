#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ANSI escape codes for colors
#define WHITE_BG "\033[48;2;255;255;255m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define ORANGE "\033[38;2;255;165;0m"
#define LIGHT_BLUE "\033[38;2;173;216;230m"
#define RESET "\033[0m"

// Function to get the computer's choice
int getComputerChoice()
{
    return rand() % 3;
}

// Function to print the choice
const char *choiceToString(int choice)
{
    switch (choice)
    {
    case 0:
        return "Stone";
    case 1:
        return "Paper";
    case 2:
        return "Scissors";
    default:
        return "Unknown";
    }
}

// Function to play one round of the game
int playRound()
{
    int userChoice, computerChoice;

    printf(YELLOW "\n\n\t\t\t\tChoose: 0 for Stone, 1 for Paper, 2 for Scissors: " RESET);

    if (scanf("%d", &userChoice) != 1 || userChoice < 0 || userChoice > 2)
    {
        printf(RED "\n\n\t\t\t\t\tInvalid input! Please enter a number between 0 and 2.\n" RESET);
        return -1; // For invalid choice
    }

    computerChoice = getComputerChoice();

    // Print choices
    printf(BLUE "\n\n\t\t\t\tYou chose: %s\n" RESET, choiceToString(userChoice));
    printf(BLUE "\n\n\t\t\t\tComputer chose: %s\n" RESET, choiceToString(computerChoice));

    // Determine the winner or tie
    if (userChoice == computerChoice)
    {
        printf(ORANGE "\n\n\n\t\t\t\t\tIt's a tie!\n" RESET);
        return 0; 
    }
    else if ((userChoice == 0 && computerChoice == 2) ||
             (userChoice == 1 && computerChoice == 0) ||
             (userChoice == 2 && computerChoice == 1))
    {
        printf(GREEN "\n\n\t\t\t\t\t\tYou win!\n" RESET);
        return 1; 
    }
    else
    {
        printf(RED "\n\n\t\t\t\t\t\tYou lose!\n" RESET);
        return -1;
    }
}

// Function to get the number of games
int getNumberOfGames()
{
    int numberOfGames;
    do
    {
        printf(LIGHT_BLUE "\n\n\t\t\tHow many games do you want to play (must be an odd number)? " RESET);
        scanf("%d", &numberOfGames);
        if (numberOfGames % 2 == 0)
        {
            printf(RED "\n\n\t\t\t\tYou must enter an odd number!\n" RESET);
        }
    } while (numberOfGames % 2 == 0);

    return numberOfGames;
}

// Function to print the final results
void printResults(int userWins, int computerWins, int ties)
{
    printf(LIGHT_BLUE "\n\n\t\t\tGame Over! Here are the final results:\n" RESET);
    printf(GREEN "\t\t\t\tUser wins: %d\n" RESET, userWins);
    printf(RED "\t\t\t\tComputer wins: %d\n" RESET, computerWins);
    printf(ORANGE "\t\t\t\tTies: %d\n" RESET, ties);

    if (userWins > computerWins)
    {
        printf(GREEN "\n\t\t\t\tCongratulations! You won the series!\n" RESET);
    }
    else if (computerWins > userWins)
    {
        printf(RED "\n\t\t\t\tSorry, the computer won the series!\n" RESET);
    }
    else
    {
        printf(ORANGE "\n\t\t\t\tIt's a tie series!\n" RESET);
    }
}

// Main game logic function
void playGameSeries()
{
    srand(time(NULL)); // giving current time as seed to the random number generator

    int numberOfGames = getNumberOfGames();
    int userWins = 0, computerWins = 0, ties = 0;

    // Play the specified number of rounds
    for (int i = 0; i < numberOfGames; i++)
    {
        int result = playRound(); // Play a single round

        // If result is invalid  redo the round
        if (result == -1)
        {
            printf(RED "\n\n\t\t\t\tRetrying the round due to invalid input.\n" RESET);
            i--; 
            continue;
        }

        // Update score
        if (result == 1)
        {
            userWins++;
        }
        else if (result == -1)
        {
            computerWins++;
        }
        else
        {
            ties++;
        }

        // Check if someone has won the majority of games early
        if (userWins > numberOfGames / 2 || computerWins > numberOfGames / 2)
        {
            break;
        }
    }

    // Print the final results
    printResults(userWins, computerWins, ties);
}

int main()
{
    printf(LIGHT_BLUE "\n\n\t\t\t\t\t\tGAME : STONE PAPER SCISSORS\n" RESET);
    playGameSeries(); // Start the game series
    return 0;
}

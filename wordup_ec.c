// Author: Ryan Austin Q. Stevens
// Purpose: Project 10 extra credit, added random word selector from file and accounts for duplicate letters.
// Due Date: May 6, 2025
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define FILE_NAME "mystery.txt"
#define MAX_LENGTH 5
#define MAX_WORDS 20
#define MAX_GUESSES 6
#define NUM_ROWS 15

// Function prototype
void readfile(char* filename, char* word);
void getWord(char* input, int count);
void convertToLower(char* input);
void convertToUpper(char* input);
int checkValidLetter(char* input);
void checkWinner(bool guessed, int count, char* word);
bool checkWord(char* guess, char* word);
void checkLetter(char* guess, char* word, int count, char trackLetter[][MAX_LENGTH+1]);
void checkPosition(char* guess, char* word, int count, char trackGuess[][MAX_LENGTH+1]);
void printGuess(char trackLetter[][MAX_LENGTH+1], char trackGuess[][MAX_LENGTH+1], int count);

int main() {

    char word[MAX_LENGTH+1]; // +1 for null terminator
    char guess[MAX_WORDS];
    char trackGuess[MAX_WORDS][MAX_LENGTH+1]; // Array to track guesses
    char trackLetter[MAX_WORDS][MAX_LENGTH+1]; // Array to track correct letters
    int count = 1;
    bool guessed = false; // Flag to check if the word is guessed

    // Read a random word from the file
    readfile(FILE_NAME, word);

    do {
        getWord(guess, count);
        guessed = checkWord(guess, word);
        if (!guessed) {
            checkLetter(guess, word, count, trackLetter);
            checkPosition(guess, word, count, trackGuess);
            printGuess(trackLetter, trackGuess, count);
            count++;
        }
        
    } while (count < MAX_GUESSES && guessed == false);

    checkWinner(guessed, count, word);

    return 0;
}

void printGuess(char trackLetter[][MAX_LENGTH+1], char trackGuess[][MAX_LENGTH+1], int count) {
    // Print the guesses
    for(int i = 1; i <= count; i++) {
        printf("%s\n", trackLetter[i]);
        printf("%s\n", trackGuess[i]);
    }
}

void checkWinner(bool guessed, int count, char* word) {
    char level[][15] = {
        "Cheater",
        "GOATED",
        "AMAZING",
        "CRAFTY",
        "BRILLIANT",
        "LUCKY"
    };
    char indent[8] = "       \0";

    convertToUpper(word);
    if (guessed) {
        // Winner

        printf("%s%s%s\n", indent, indent, word);
        printf("%sYou won in %d guesses!\n", indent, count);
        printf("%s%s%s!\n", indent, indent, level[count]);
    } else {
        // Loser
        printf("You lost, better luck next time! The word was: %s\n", word);
    }
}

bool checkWord(char* guess, char* word) {
    // Check if the guess is correct
    for (int i = 0; i < MAX_LENGTH; i++) {
        if (guess[i] != word[i]) {
            return false; // Not a match
        }
    }
    return true; // Match found
}
void checkPosition(char* guess, char* word, int count, char trackGuess[][MAX_LENGTH+1]) {
    int i, j;
    // Check if the letter is in the word but not in the correct position
    for (i = 0; i < MAX_LENGTH; i++) {
        if (guess[i] == word[i]) {
            trackGuess[count][i] = ' '; // add space
        } else {
            trackGuess[count][i] = ' '; // add space
        }

        if (guess[i] != word[i]) {
            for (j = 0; j < MAX_LENGTH; j++) {
                if (guess[i] == word[j]) {
                    trackGuess[count][i] = '^'; // mark letter in word
                }
            }
        }
    }
    trackGuess[count][i] = '\0';
}
void checkLetter(char* guess, char* word, int count, char trackLetter[][MAX_LENGTH+1]) {
    int i, j;
    // Check if the letter is in the correct position
    for (int i = 0; i < MAX_LENGTH; i++) {
        if (guess[i] == word[i]) {
            trackLetter[count][i] = guess[i] - 32; // correct position
        } else {
            trackLetter[count][i] = guess[i]; // incorrect
        } 
    }
    trackLetter[count][i] = '\0';
}

void getWord(char* input, int count) {
    int valid; // Validation flag 1=true, 0=false
    
    // Prompt user for input
    printf("GUESS %d! Enter your guess: ", count);
    fgets(input, MAX_WORDS, stdin);

    do {
        int i;
        valid = 1; // Assume valid input
        convertToLower(input);

        // Check if more than 5 letters
        for (i = 0; input[i] != '\0'; i++) {
            if ( i >= MAX_LENGTH) {
                valid = 0; // Set valid to false
                printf("Your guess must be %d letters long. ", MAX_LENGTH);
                break;
            }
        }
        // Check if less than 5 letters
        if ( i < MAX_LENGTH && input[i] =='\0') {
            valid = 0; // Set valid to false
            printf("Your guess must be %d letters long. ", MAX_LENGTH);
        }
        // Check if the letter is not a-z
        if (checkValidLetter(input) == 0) {
            valid = 0; // Set valid to false
            printf("Your guess must contain only letters. ");
        }

        if (valid == 0) {
            printf("\n");
            printf("Please try again: ");
            fgets(input, MAX_WORDS, stdin);
        }
        // When the input is valid exit the loop
    } while (valid == 0);
    printf("================================\n");
}

void convertToLower(char* input) {
    // Convert the letter to lower case
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        // Remove newline character if present
        if (input[i] == '\n' || input[i] == '\r') {
            input[i] = '\0';
            break;
        }
        // Convert to lower case
        if (input[i] >= 'A' && input[i] <= 'Z') {
            input[i] = input[i] + 32;
        }
    }
}

void convertToUpper(char* input) {
    // Convert the letter to upper case
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        // Remove newline character if present
        if (input[i] == '\n' || input[i] == '\r') {
            input[i] = '\0';
            break;
        }
        // Convert to upper case
        if(input[i] >= 'a' && input[i] <= 'z') {
            input[i] = input[i] - 32;
        }
    }
}

int checkValidLetter(char* input) {
    // Check if the letter is not a-z
    for (int i = 0; input[i] != '\0'; i++) {
        if ((input[i] < 'a') || (input[i] > 'z')) {
            return 0; // Set valid to false
        }
    }
    return 1; // Set valid to true
}


// Function to read a word from a file
void readfile(char* filename, char* word) {
    char wordlist[NUM_ROWS][MAX_LENGTH+1]; // Array to store words
    // Open the file for reading
    FILE* fp;
    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) {
        printf("Could not open file: %s", filename);
        return;
    }

    int size = 0;
    // Read line into an array of characters
    while (fscanf(fp, "%s", wordlist[size]) == 1) {
        size++;
    }
    // Close the file
    fclose(fp);

    // Generates number in range 0 to size-1
    srand(time(NULL));  // Seed
    int random = rand() % size;  

    // Get random word
    int i = 0;
    while (wordlist[random][i] != '\0') {
        word[i] = wordlist[random][i];
        i++;
    }
    word[i] = '\0';
}

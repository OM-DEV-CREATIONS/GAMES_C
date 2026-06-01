// HANG MAN GAME RUNS IN TERMINAL ITSELF
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 60
#define MAX_TRIES 7

// Struct to hold a word and its hint
struct WordWithHint {
    char word[MAX_WORD_LENGTH];
    char hint[MAX_WORD_LENGTH];
};

// Function to display the current state of the word
void displayWord(const char word[], const bool guessed[]);

// Function to draw the hangman
void drawHangman(int tries);

// driver code
int main()
{
    // Seed the random number generator with the current
    // time
    srand(time(NULL));
    // Array of words with hints
    struct WordWithHint wordList[] = {
        { "GTA-V", "One of the Peak Realism Game even though it came in 2013 " },
        { "elephant", "A large mammal with a trunk" },
        { "pizza", "A popular Italian dish" },
        { "beach", "Sandy shore by the sea" },
        { "Kratos" ,"The God killer in Games"},
        { "Wukong" , "The Monkey king"} ,
        {"FORTRAN" , "A High-level general-purpose programming language, released by IBM in 1957."} ,
        {"Plankalkul" , "The first high-level programming language, created by Konrad Zuse in 1943 "} ,
        {"Bjarne Stroustrup" , "The Creator of C programming Language"}
        // You can add more words and hints here
    };

    // Select a random word from the list
    int wordIndex = rand() % 9 ;

    const char* secretWord = wordList[wordIndex].word;
    const char* hint = wordList[wordIndex].hint;

    int wordLength = strlen(secretWord);
    char guessedWord[MAX_WORD_LENGTH] = { 0 };
    bool guessedLetters[26] = { false };

    printf("Welcome to Hangman!\n");
    printf("Hint: %s\n", hint);

    int tries = 0;

    while (tries < MAX_TRIES) {
        printf("\n");
        displayWord(guessedWord, guessedLetters);
        drawHangman(tries);

        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (guessedLetters[guess - 'a']) {
            printf("You've already guessed that letter. "
                   "Try again.\n");
            continue;
        }

        guessedLetters[guess - 'a'] = true;

        bool found = false;
        for (int i = 0; i < wordLength; i++) {
            if (secretWord[i] == guess) {
                found = true;
                guessedWord[i] = guess;
            }
        }

        if (found) {
            printf("Good guess!\n");
        }
        else {
            printf("Sorry, the letter '%c' is not in the "
                   "word.\n",
                   guess);
            tries++;
        }

        if (strcmp(secretWord, guessedWord) == 0) {
            printf("\nCongratulations! You've guessed the "
                   "word: %s\n",
                   secretWord);
            break;
        }
    }

    if (tries >= MAX_TRIES) 
    {
        printf("\nYou've run out of tries. The word was : %s\n",secretWord);
        printf("You Lost !  ") ;
    }

    return 0;
}

void displayWord(const char word[], const bool guessed[])
{
    printf("Word: ");
    for (int i = 0; word[i] != '\0'; i++) {
        if (guessed[word[i] - 'a']) {
            printf("%c ", word[i]);
        }
        else {
            printf("_ ");
        }
    }
    printf("\n");
}

void drawHangman(int tries)
{
    const char* hangmanParts[]
        = { "     _________",    "    |         |",
            "    |         O",   "    |        /|\\",
            "    |        / \\", "    |" };

    printf("\n");
    for (int i = 0; i <= tries; i++) {
        printf("%s\n", hangmanParts[i]);
    }
}

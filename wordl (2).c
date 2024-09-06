#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining color escape sequences.
const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * const WHITE = "\x1b[0m";

// Keeping track of the current color.
const char * current = WHITE;

// Setting terminal color.
void setColour(const char *colour) {
    // Checking if the color is already set.
    if (strcmp(current, colour) == 0)
        return; // If color is already set, do nothing.
    // Otherwise, setting the color.
    printf("%s", colour);
    current = colour; // Updating the current color.
}

// Printing guess with color codes.
void printColorizedGuess(const char* guess, const char* code) {
    int code_length = strlen(code);
    // Allocating memory for arrays to store color info.
    char* arr = (char*)malloc(code_length * sizeof(char));
    char* color = (char*)malloc(code_length * sizeof(char));
    char* checked = (char*)malloc(code_length * sizeof(char));

    // Checking if memory allocation failed.
    if (arr == NULL || color == NULL || checked == NULL) {
        printf("Memory allocation failed. Exiting...\n");
        exit(1);
    }
 
    // Initializing arrays.
    for (int i = 0; i < code_length; i++) {
        arr[i] = '\0';
    }

    // Checking for correct guesses.
    for (int i = 0; i < strlen(guess); i++) {
        if (guess[i] == code[i]) {
            setColour(GREEN); // Setting color to green.
            arr[i] = guess[i];
            color[i] = 'g';
            checked[i] = 'y';
        }
    }

    // Checking for partially correct guesses.
    for (int i = 0; i < strlen(guess); i++) {
        if (arr[i] == '\0') {
            for (int j = 0; j < code_length; j++) {
                if (guess[i] == code[j] && arr[i] == '\0' && checked[j] != 'y') {
                    setColour(YELLOW); // Setting color to yellow.
                    arr[i] = guess[i];
                    color[i] = 'y';
                    checked[j] = 'y';
                    break;
                }
            }
        }
    }

    // Remaining incorrect guesses.
    for (int i = 0; i < code_length; i++) {
        if (arr[i] == '\0') {
            setColour(WHITE); // Setting color to white.
            arr[i] = guess[i];
            color[i] = 'w';
        }
    }

    // Printing guess with colors.
    for (int i = 0; i < code_length; i++) {
        if (color[i] == 'g') {
            setColour(GREEN);
            printf("%c", guess[i]);
        }
        else if (color[i] == 'y') {
            setColour(YELLOW);
            printf("%c", guess[i]);
        }
        else {
            setColour(WHITE);
            printf("%c", guess[i]);
        }
    }
    printf("\n");
    setColour(WHITE); // Resetting color.

    // Freeing dynamically allocated memory.
    free(arr);
    free(color);
    free(checked);
}

int main(int argc, char *argv[]) {
    // Checking if the correct number of command-line arguments is provided.
    if (argc != 2) {
        printf("Usage: %s <code_word>\n", argv[0]);
        return 1;
    }

    // Initializing code word and maximum guesses.
    const char *code = argv[1];
    const int max_guesses = 6;
    int guesses = 0;

    // Main game loop.
    while (guesses < max_guesses) {
        printf("Enter guess: ");
        char *guess = (char *)malloc(13 * sizeof(char));
        if (guess == NULL) {
            printf("Memory allocation failed. Exiting...\n");
            return 1;
        }
        scanf("%s", guess);

        // Checking if guess is correct.
        if (strcmp(guess, code) == 0) {
            setColour(GREEN); // Setting color to green.
            printf("%s\n", guess); // Printing correct guess.
            setColour(WHITE); // Resetting color.
            printf("Finished in %d guesses\n", guesses + 1); // Printing number of guesses.
            free(guess); // Freeing memory allocated for guess.
            return 0;
        }
        // Checking if guess length matches code length.
        else if (strlen(guess) == strlen(code)) {
            printColorizedGuess(guess, code); // Printing colorized guess.
            free(guess); // Freeing memory allocated for guess.
            guesses++; // Incrementing guess count.
        }
        // If guess length does not match code length.
        else if (guesses == 6) { // Assuming this condition should be about exceeding max_guesses.
            printf("Failed to guess the word: %s\n", code);
            return 0;
        }
        else{
            printf("Invalid guess, guess length must match word length\n");
            break;
        }
    }
}

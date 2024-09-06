//Althernative attempt
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const char * const GREEN = "\x1b[32m";
const char * const YELLOW = "\x1b[33m";
const char * const WHITE = "\x1b[0m";
const char * current = WHITE;

void setColour(const char *colour) {
  if (current == colour) return;
  printf("%s", colour);
  current = colour;
  
}

void printGuess(char *guess, char *code) {
    int i;
    int *count = (int *)calloc(26, sizeof(int));
    int *green = (int *)calloc(12, sizeof(int)); 
    int *yellow = (int *)calloc(12, sizeof(int)); 

    for (i = 0; i < strlen(code); i++) {
        count[code[i] - 'a']++;
    }

    for (i = 0; i < strlen(guess); i++) {
        if (guess[i] == code[i]) {
            green[i] = 1;
            count[guess[i] - 'a']--;
             
        }} 
    for (i = 0; i < strlen(guess); i++) {
        if (count[guess[i] - 'a'] > 0 && !green[i]) {
            
            yellow[i] = 1;
            count[guess[i] - 'a']--; 
             
        } }
           
    for (i = 0; i < strlen(guess); i++) {
        if (green[i] == 1){
            setColour(GREEN); 
            printf("%c", guess[i]);
        }
        else if (yellow[i] == 1){
            setColour(YELLOW); 
            printf("%c", guess[i]);
        }
        else{
            setColour(WHITE); 
            printf("%c", guess[i]);
        }
    }
    
    printf("\n");
    free(count);
    free(green);
    free(yellow);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <word>\n", argv[0]);
        return 1;
    }

    char *code = argv[1];
    char *guess = (char *)malloc(4 * sizeof(char)); 
    int guesses = 0;
    while (guesses < 6) {
        printf("Enter guess: ");
        scanf("%s", guess);
        printGuess(guess, code);

        if (strcmp(guess, code) == 0) {
            printf("Finished in %d guesses\n", guesses + 1);
            free(guess);
            return 0;
        }
        guesses++;

        if (guesses == 5) {
            char *temp = (char *)realloc(guess, 8 * sizeof(char)); 
            if (!temp) {
                free(guess);
                return 1;
            }
            guess = temp;
        }
    }

    printf("Failed to guess the word: %s\n", code);
    free(guess);
    return 0;
}



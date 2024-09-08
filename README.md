# Wordl
This repository contains a terminal-based guessing game implemented in C, where the user tries to guess a secret code word. The program provides visual feedback by colorizing correct, partially correct, and incorrect guesses.

## How the Game Works
The player has up to 6 attempts to guess the secret code word.
The guess is compared to the code word, and each character is colorized based on the following rules:
Green: Correct letter in the correct position.
Yellow: Correct letter in the wrong position.
White: Incorrect letter.
The game uses terminal color codes to provide feedback on each guess.

## Features
Dynamic Memory Allocation: The program dynamically allocates memory for arrays during runtime.
Color-coded Feedback: It uses ANSI escape sequences to colorize the output based on correctness.
Input Validation: Ensures the user inputs guesses of the correct length.

## Prerequisites
You will need a C compiler such as gcc to compile and run the program.

## Compilation
Use the following command to compile the program:
  gcc -o guess_game guess_game.c

## Running the Program
After compiling, run the program by providing the secret code word as a command-line argument:
  ./guess_game <code_word>


## Functions
**setColour(const char *colour):** Sets the terminal color using ANSI escape codes if the color hasn't been set already.

**printColorizedGuess(const char* guess, const char* code):** Compares the user’s guess to the code word and prints each character colorized based on whether it is correct, partially correct, or incorrect.

**main():** The main game loop prompts the user to guess the code word. It checks if the guess is correct, partially correct, or wrong and provides colorized feedback.

## Color Codes
Green (\x1b[32m): Correct character and position.

Yellow (\x1b[33m): Correct character but wrong position.

White (\x1b[0m): Incorrect character.

## Notes
Ensure that the word guessed is the same length as the secret code word.
The code allocates memory dynamically and ensures memory is freed after use to avoid memory leaks.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int number, guess, attempts = 0;
    char ch;

    // Seed the random number generator
    srand(time(0)); 
    number = rand() % 100 + 1; // Random number between 1 and 100

    printf("Welcome to the Number Guessing Game!\n");
    printf("I have selected a number between 1 and 100. Try to guess it!\n");

    do {
        printf("Enter your guess (1-100): ");

        // Validate input
        if (scanf("%d", &guess) != 1) {
            printf("Invalid input. Please enter a number between 1 and 100.\n");

            // Clear input buffer
            while ((ch = getchar()) != '\n' && ch != EOF);
            continue;
        }

        // Ensure the guess is within valid range
        if (guess < 1 || guess > 10000) {
            printf("Out of range! Please enter a number between 1 and 100.\n");
            continue;
        }

        attempts++;

        if (guess > number) {
            printf("Too high! Try again.\n");
        } else if (guess < number) {
            printf("Too low! Try again.\n");
        } else {
            printf("Congratulations! You guessed the number in %d attempts.\n", attempts);
        }

    } while (guess != number);

    return 0;
}

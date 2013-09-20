#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_guess(int x, int y){
    //Assumes x < y
    //This function gets a guess in the correct range
    int value;
    printf("What number am I thinking? ");
    do {
        scanf("%d", &value);
        if (value < x || value > y) {
            printf("I'm sorry. That is not between %d and %d.\n", x, y);
            printf("Please do enter an integer between %d and %d: ", x, y);
        }
    } while (value < x || value > y);
    return value;
}

int main(){
    int number;
    int lives;
    int guess;
    int won;

    srand(time(NULL));
    number = rand() % 100 + 1;
    //Keep a count of the attempts the player has
    lives = 6;
    //Did the player win?
    won = 0;

    printf("I'm thinking of a number between 1 and 100...\n");
    //Play high low until the player runs out of lives or wins
    do {
        guess = get_guess(1, 100);
        lives--;
        if (guess > number) {
            printf("Your guess was too high!\n");
            printf("You have %d guesses left.\n", lives);
        }
        else if (guess < number) {
            printf("Your guess was too low!\n");
            printf("You have %d guesses left.\n", lives);
        } else {
            printf("Congratulations! Your guess was correct!\n");
            won = -1;
        }
    } while (!won && lives > 0);
    if (!won) {
        printf("Sorry your guesses were unsuccessful.\n");
    }
    printf("Thanks for playing high low!\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 20 //max length of words
#define MAX_WORDS 10 //number of words in word bank

//hangman banner
void banner(){
printf(" _____                                                                           _____ \n");
printf("( ___ )-------------------------------------------------------------------------( ___ )\n");
printf(" |   |                                                                           |   | \n");
printf(" |   |  /$$   /$$  /$$$$$$  /$$   /$$  /$$$$$$  /$$      /$$  /$$$$$$  /$$   /$$ |   | \n");
printf(" |   | | $$  | $$ /$$__  $$| $$$ | $$ /$$__  $$| $$$    /$$$ /$$__  $$| $$$ | $$ |   | \n");
printf(" |   | | $$  | $$| $$  \\ $$| $$$$| $$| $$  \\__/| $$$$  /$$$$| $$  \\ $$| $$$$| $$ |   | \n");
printf(" |   | | $$$$$$$$| $$$$$$$$| $$ $$ $$| $$ /$$$$| $$ $$/$$ $$| $$$$$$$$| $$ $$ $$ |   | \n");
printf(" |   | | $$__  $$| $$__  $$| $$  $$$$| $$|_  $$| $$  $$$| $$| $$__  $$| $$  $$$$ |   | \n");
printf(" |   | | $$  | $$| $$  | $$| $$\\  $$$| $$  \\ $$| $$\\  $ | $$| $$  | $$| $$\\  $$$ |   | \n");
printf(" |   | | $$  | $$| $$  | $$| $$ \\  $$|  $$$$$$/| $$ \\/  | $$| $$  | $$| $$ \\  $$ |   | \n");
printf(" |   | |__/  |__/|__/  |__/|__/  \\__/ \\______/ |__/     |__/|__/  |__/|__/  \\__/ |   | \n");
printf(" |___|                                                                           |___| \n");
printf("(_____)-------------------------------------------------------------------------(_____)\n");
}
//clear terminal function
void clearScreen() {
    printf("\033[H\033[J"); 
}
//clear previous inputs
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
//hangman declaration
void hangman(int lives);

//Hangman Game
void Game(int randwordnum,size_t word_size,char guess) {
    clearScreen();
    clearInputBuffer();
    
    FILE *wordbank = fopen("Wordbank.txt", "r"); //opens wordbank
    if (wordbank == NULL) {
        printf("Error accessing wordbank\n"); //makes sure wordbank available
        return;
    }

    char storage[MAX_WORDS][MAX_LINE_LENGTH]; //array for storing wordbank 
    int num_lines = 0; //initialize number of words stored before counting

    //stores each word into storage array until num_lines stored is greater then WORDS meaning all words stored
    while (fgets(storage[num_lines], sizeof(storage[num_lines]), wordbank) && num_lines < MAX_WORDS) {
        //removes an newlines
        storage[num_lines][strcspn(storage[num_lines], "\n")] = '\0';
        num_lines++;
    }

    fclose(wordbank); //close wordbank file
   
    srand(time(NULL)); 
    randwordnum = rand() % num_lines;   //creats a random number based on how many lines stored
    size_t wordlength = strlen(storage[randwordnum]);// count how many letters in the chosen word 

char *word = (char *)malloc((wordlength + 1) * sizeof(char));  //creates a pointer to store each letter in a specific place for later 
    if (word == NULL) {
        printf("Memory allocation failed\n");
        return; 
    }
   
    snprintf(word, wordlength + 1, "%s", storage[randwordnum]);  // Copy the selected word into the dynamically allocated buffer
  
banner();

    int lives = 7;
    char display[wordlength + 1];
    
    // Initialize display 
    for (size_t i = 0; i < wordlength; i++) {
        display[i] = '_';
    }
    display[wordlength] = '\0';

      
        hangman(lives);
while (lives > 0) {

        // Print the current state of the blanks
        for (size_t i = 0; i < wordlength; i++) {
            printf("%c ", display[i]);
        }
        printf("\n");

        printf("Enter your guess: ");
        scanf(" %c", &guess);  //store guess
       
        int found = 0;
        for (size_t i = 0; i < wordlength; i++) { //search word for guess
            if (word[i] == guess) {             
                found = 1;
                display[i] = guess; //if found add to correct location in blank
            }
        }

        if (found) {
            clearScreen();      //correct message with screen reset
            banner();
            hangman(lives);
            printf("Correct!\n");
        } else {
            lives--; 
            clearScreen();    //incorrect message with screen reset 
            banner();
            hangman(lives);
            printf("Incorrect.\n");
        }

        // Check if the user has guessed the entire word
        if (strcmp(word, display) == 0) {
            printf("Congratulations! You've guessed the word: %s\n", word);
            break;
        }

        // Check if lives are zero
        if (lives == 1) {
            printf("Game over! The word was: %s\n", word);
            break;
        }
    }
    
    free(word);
}

int main(){
   
    int randwordnum;
    char word[6];
    size_t word_size;
    char guess;
    char choice;
   
   //start
    clearScreen();
    printf("Enter Y to start or Q to exit:"); 
        scanf("%c",&choice);

if(choice == 'y' || choice == 'Y'){
    Game(randwordnum,word_size,guess);
 }
if(choice == 'q' || choice == 'Q'){
 return 0;
}

 return 0;
}

void hangman(int lives) {
    switch (lives) {
        case 7:
            printf("      _______   \n"); 
            printf("     |/      |  \n");
            printf("     |       \n");
            printf("     |       \n");
            printf("     |         \n");
            printf("     |       \n");
            printf("     |          \n"); 
            printf("_____|___       \n\n"); 
            break;
        case 6:
            printf("      _______   \n"); 
            printf("     |/      |  \n");
            printf("     |      (_) \n");
            printf("     |       \n");
            printf("     |         \n");
            printf("     |       \n");
            printf("     |          \n"); 
            printf("_____|___       \n"); 
            break;
        case 5:
            printf("      _______   \n"); 
            printf("     |/      |  \n");
            printf("     |      (_) \n");
            printf("     |       | \n");
            printf("     |         \n");
            printf("     |        \n");
            printf("     |          \n"); 
            printf("_____|___       \n");
            break;
        case 4:
            printf("      _______   \n"); 
            printf("     |/      |  \n");
            printf("     |      (_) \n");
            printf("     |      \\| \n");
            printf("     |       |  \n");
            printf("     |        \n");
            printf("     |          \n"); 
            printf("_____|___       \n");   
            break;
        case 3:
            printf("      _______   \n"); 
            printf("     |/      |  \n");
            printf("     |      (_) \n");
            printf("     |      \\|/ \n");
            printf("     |       |  \n");
            printf("     |        \n");
            printf("     |          \n"); 
            printf("_____|___       \n");  
            break;
        case 2:
            printf("      _______   \n"); 
            printf("     |/      |  \n");
            printf("     |      (_) \n");
            printf("     |      \\|/ \n");
            printf("     |       |  \n");
            printf("     |      /  \n");
            printf("     |          \n"); 
            printf("_____|___       \n");   
            break;
        case 1:
            printf("      _______   \n"); 
            printf("     |/      |  \n");
            printf("     |      (_) \n");
            printf("     |      \\|/ \n");
            printf("     |       |  \n");
            printf("     |      / \\ \n");
            printf("     |          \n"); 
            printf("_____|___       \n");  
            break;           
    }
}
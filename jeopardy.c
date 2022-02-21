/*
 * Tutorial 3 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <Tanuj Patel:100749957, Harris Athwal: 100750935, Owen Musselman: 100657709>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Colours
#define CORRECT_ANS "\x1b[32m"
#define WRONG_ANS "\x1b[31m"
#define QUESTION "\x1b[33m"
#define COLOUR_RESET "\x1b[0m"

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players);


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    // initialize each of the players in the array
    for(int i =0; i<NUM_PLAYERS;i++){
    	printf("\n");
        printf(QUESTION "Enter the Name for Player %d:" COLOUR_RESET, i + 1);
        scanf("%s", players[i].name);
        players[i].score=0;
    }

    system("clear");

    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Call functions from the questions and players source files
        // Execute the game until all questions are answered
        // Display the final results and exit

        char *current_player = calloc(BUFFER_LEN, sizeof(char));
        char *current_cat = calloc(BUFFER_LEN, sizeof(char));
        int current_val;
        char *firstWord = calloc(BUFFER_LEN, sizeof(char));
        char *secondWord = calloc(BUFFER_LEN, sizeof(char));
        char *response = calloc(BUFFER_LEN, sizeof(char));
        char *token;

        display_categories();

        printf("\nEnter Player:");
        scanf("%s", current_player);

        if(player_exists(players,NUM_PLAYERS,current_player)){
            printf("Choose a category and the value:");
            scanf("%s %d", current_cat, &current_val);

            if(!already_answered(current_cat, current_val)){
                display_question(current_cat, current_val);
                scanf("%s %s %s", firstWord, secondWord, response);
                token =strtok(response, "");

                while(token != NULL){
                    strcpy(response, token);
                    token = strtok(NULL, "");
                }

                if(valid_answer(current_cat, current_val, response)){
                    for(int i=0;i<NUM_PLAYERS; i++){
                        if(strcmp(players[i].name, current_player)==0){
                            players[i].score =players[i].score +current_val;
                            printf("Score is: $%d\n", players[i].score);
                            break;
                        }
                    }
                }
            }

            else{
                system("clear");
                printf("The question you have selected has already been answered");
            } 
        }

        else{
            system("clear");
            printf("Invalid Input. The player you enter does not exist\n");
        }

        free(current_player);
        free(current_cat);
        free(response);
        free(token);
    }
    return EXIT_SUCCESS;
}

void show_results(player *players, int num_players) {
    int tempScore = 0, placement = 1;
    char tempName[MAX_LEN];
    
    // Sort the scores from highest to lowest, and copy the names of the contestents to match the sorting process.
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++ ) {
            if (players[i].score < players[j].score) {
               tempScore = players[i].score;
               strcpy(tempName, players[i].name);
               players[i].score = players[j].score;
               strcpy(players[i].name, players[j].name);
               players[j].score = tempScore;
               strcpy(players[j].name, tempName);
           }
        }
    }

    // Prints the final results of each player.
    printf(QUESTION "Final results:\n" COLOUR_RESET);
    for (int k = 0; k < 4; k++) {
        printf(CORRECT_ANS"%d. %s's Score: $%d\n" COLOUR_RESET, placement, players[k].name, players[k].score);
        placement++;
    }
}

void tokenize(char *input, char **tokens) {
    char *whoWhatTok;
    whoWhatTok = strtok(input, " ");
    char *isTok;
    isTok = strtok(NULL, " ");
    char *ansTok;
    ansTok = strtok(NULL, " ");

    // Checks if the answer contains "what is" or "who is"
    if (strcmp(whoWhatTok, tokens[0])==0 || strcmp(whoWhatTok, tokens[1])==0 && strcmp(isTok, tokens[2])==0) {
        tokens[3] = ansTok;
    } else {
        printf("Sorry, you did not answer with in the form of ""who is, or what is"" and you miss a turn.");
    }
}


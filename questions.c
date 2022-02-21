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
#include "questions.h"

#define CORRECT_ANS "\x1b[32m"
#define WRONG_ANS "\x1b[31m"
#define QUESTION "\x1b[33m"
#define COLOUR_RESET "\x1b[0m"
#define CATE_COL "\033[0;36m"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    question questionOne = {.category="programming", .question = "What is the numbering scheme computers use?", .answer = "binary", .value = 50, .answered=false};
    question questionTwo = {.category="programming", .question = "The logical operator that returns true if both operands are true?", .answer = "AND", .value = 100, .answered=false};
    question questionThree = {.category="programming", .question = "The markup language used to create websites?", .answer = "HTML", .value = 150, .answered=false};
    question questionFour = {.category="programming", .question = "A programming paradigm based on the concept of objects in short form?", .answer = "OOP", .value = 200, .answered=false};

     question questionFive = {.category="science", .question = "It is the largest planet in the solar system?", .answer = "Jupiter", .value = 50, .answered=false};
    question questionSix = {.category="science", .question = "The creator of the lightbulbs first name?", .answer = "Thomas", .value = 100, .answered=false};
    question questionSeven = {.category="science", .question = "How many elements are there in the periodic table?", .answer = "118", .value = 150, .answered=false};
    question questionEight = {.category="science", .question = "What is the hardest known natural material?", .answer = "diamond", .value = 200, .answered=false};

    question questionNine = {.category="math", .question = "What is the only even prime number?", .answer = "2", .value = 50, .answered=false};
    question questionTen = {.category="math", .question = "26 divided by 2 is what?", .answer = "13", .value = 100, .answered=false};
    question questionEleven = {.category="math", .question = "What does the square root of 144 equals?", .answer = "12", .value = 150, .answered=false};
    question questionTwelve = {.category="math", .question = "The perimeter of a circle is also known as?", .answer = "circumference", .value = 200, .answered=false};


    questions[0] = questionOne;
    questions[1] = questionTwo;
    questions[2] = questionThree;
    questions[3] = questionFour;

    questions[4] = questionFive;
    questions[5] = questionSix;
    questions[6] = questionSeven;
    questions[7] = questionEight;

    questions[8] = questionNine;
    questions[9] = questionTen;
    questions[10] = questionEleven;
    questions[11] = questionTwelve;

    printf(CORRECT_ANS "WELCOME TO JEPOARDY!\n" COLOUR_RESET);
    printf("Rules are simple pick a category and value and answer the questions in the format of who is or what is and win points!");

}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    printf(CATE_COL "%s\t%s\t%s\n" COLOUR_RESET, categories[0], categories[1], categories[2]);
    for(int i=0;i<NUM_QUESTIONS;i++){
        if(i%3==0){
            printf("\n");
        }

        if(questions[i].answered == false){
            printf(CORRECT_ANS "$%d\t\t" COLOUR_RESET, questions[i].value);
        }
        else{
            printf(WRONG_ANS "xxxx\t" COLOUR_RESET);
        }
    }

    printf("\n");
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
    char *question = calloc(MAX_LEN, sizeof(char));
    for(int i=0;i<NUM_QUESTIONS;i++){
        if(strcmp(questions[i].category, category)==0 && questions[i].value == value){
            strcpy(question, questions[i].question);
            break;
        }
    }

    printf(QUESTION "%s" COLOUR_RESET, question);
    free(question);
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    int q_index=0;
    int answered_count = 0;
    if (answered_count == 12) {
    	system("exit");
    } else {

    for(int i=0;i<NUM_QUESTIONS;i++){
        if(strcmp(questions[i].category, category)==0 && questions[i].value == value){
            q_index=i;
            questions[i].answered=true;
            answered_count++;
            break;
        }
    }
    system("clear");

    if(strcmp(questions[q_index].answer, answer)==0){
        printf(CORRECT_ANS "Yay! You got it Correct\n You got $%d\n" COLOUR_RESET, value);
        return true;
    }

    else{
        printf(WRONG_ANS "Incorrect. The correct asnwer was: %s\n" COLOUR_RESET, questions[q_index].answer);
        return false;
    }
    }

    
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    for(int i=0;i<NUM_QUESTIONS;i++){
        if(strcmp(questions[i].category, category)==0 && questions[i].value == value && questions[i].answered){
            return true;
        }
    }
    return false;
}

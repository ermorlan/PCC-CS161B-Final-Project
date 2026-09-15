/******************************************************************************
# Author:           Erin Morlan
# Assignment:       Final Project: Bookshelf
# Date:             started August 13th 2026
# Description:      This program displays information on books for readers. The
#                   user can add books, remove books (all one at a time), as
#                   well as change the star rating on any books that maybe
#                   they read and disagree with the rating on. 
# Input:            char title[], char author[], double rating all to be put in
#                   initialized Book book, then to be placed in Bookshelf
#                   shelves data member.
# Output:           books.txt, updating with books removed, added or edited by
#                   user
# Sources:          Final project specifications
#******************************************************************************/
/* file for any constants and function definitions used in tools.cpp */

#pragma once

#include "booksData.h"

// function prototypes
// printing functions
void displayMenu();
void displaySearch(); 
void printOne(Book book, int longest);
void printAll(Book shelf[], int size, int longest);
// reading data functions
// readOption default bool is false if taking menu option, true
char readOption(string prompt, bool isNameOrTitle = false);
char yesOrNo(string prompt);
double readDouble(string prompt);
void readText(string prompt, char array[]);
bool caseInsensitiveMatch(char array1[], char array2[]);
// changing pieces of the bookshelf
void changeStars(Book &book);
// execution
//void exeOption(Book shelf[], int &size, char &userChoice, int longest);
void exeOption(Bookshelf &books, char &choice);
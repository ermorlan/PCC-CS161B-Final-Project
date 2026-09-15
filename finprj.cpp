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

#include "tools.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    Bookshelf myBooks;
    
    char userChoice = 'z'; //d for default
    
    // introducing the program and program details
    cout << "Welcome!" << endl;
    cout << "This Bookshelf Program displays your personal \"to be read\" (TBR)"; 
    cout << "\nlist. You can add and remove books from the list, display a";
    cout << "\nspecific book and edit its rating, find the highest rated book";
    cout << "\non the list, discover your next read, or quit the program." << endl;
    
    cout << "\nIf you would like to edit the star rating of a book on the shelf,";
    cout << "\nselect 'F' to find, or search for it first." << endl;
    
    // loading in our data
    //if (!loadData(bookshelf, count, longest)) {
    if (!loadData(myBooks)) {
        cout << "Error loading data, program terminating." << endl;
        return 0;
    }

    // getting user input, looping until they quit
    do {
        displayMenu();
        
        userChoice = readOption(">> ");
        
        //exeOption(bookshelf, count, userChoice, longest);
        exeOption(myBooks, userChoice);
        
    } while (tolower(userChoice) != 'q');
    
    if (!printData(myBooks)) {
        cout << "Error updating data, program terminating." << endl;
        return 0;
    }
    // exiting the program
    cout << "\nThank you for using my Bookshelf Program." << endl;
        
    return 0;
}
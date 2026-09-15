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
#
#
# This file is for the tools we are using for the program, but not to alter or
# manipulate the structs.
# Tools include printing, reading data like chars, doubles
#******************************************************************************/

#include "tools.h"

using namespace std;

// name: displayMenu()
// displays the menu for the user to make a character choice
//
void displayMenu() {
    cout << "\nPick an option:" << endl;
    cout << "  (A)dd a book" << endl;
    cout << "  (R)emove a book" << endl;
    cout << "  (F)ind a specific book" << endl;
    cout << "  (G)et the highest rated book" << endl;
    cout << "  (D)iscover your next read" << endl;
    cout << "  (P)rint all books" << endl;
    cout << "  (Q)uit" << endl;
}

// name: displaySearch()
// this prints the menu when a user is searching for a book, to decide how to
// find it
void displaySearch() {
    cout << "\nSearching by..." << endl;
    cout << "  (T)itle" << endl;
    cout << "  (N)ame of the Author" << endl;
    cout << "  (E)xit and go back to main menu" << endl;
}

// name: printOne()
// prints a single book using it's indice position
// to be called by printAll, as well as the findBook related functions
//
void printOne(Book book, int longest) {
    cout << book.title << endl;
    cout << "    by " << setw(longest) << left << book.author << " | ";
    cout << fixed << setprecision(1) << book.rating << " stars" << endl;
}

// name: printAll()
// prints entire catalog of books on the shelf
// 
void printAll(Bookshelf books) {
    for (int i = 0; i < books.count; i++) {
        if (i == 0) {
            cout << "\n";                                         
        }
        printOne(books.shelves[i], books.longest);
    }
}

// name: readOption()
// takes the option as a char array to prevent words starting with "Q" being
// valid entries. We only want "quit", at most. ** Remember this function uses 
// a parameter set to false by default in prototype. If called with true, it will
// validate under the assumption that we're choosing n or t, for name or title
//
char readOption(string prompt, bool isNameOrTitle) {
    char choice[MAXCHAR] = "z";
   
    // getting that initial choice to validate
    cout << prompt;
    cin.getline(choice, MAXCHAR);
    
    // handling immediate quit
    if (strcmp(choice, "quit") == 0 || strcmp(choice, "Quit") == 0) {
        return tolower(choice[0]);
    }
    
    // if this is NOT a search for a book
    if (!isNameOrTitle) {
        while (!cin || (
        tolower(choice[0]) != 'a' && 
        tolower(choice[0]) != 'r' &&
        tolower(choice[0]) != 'f' && 
        tolower(choice[0]) != 'd' &&
        tolower(choice[0]) != 'g' &&
        tolower(choice[0]) != 'p' && 
        tolower(choice[0]) != 'q') ||
        strlen(choice) > 1) {
            if (tolower(choice[0]) == 'q') {
                if (strcmp(choice, "quit") == 0 ||
                strcmp(choice, "Quit") == 0) {
                    return tolower(choice[0]);
                }
            }
            cout << "Invalid choice, please try again." << endl;
            cout << prompt;
            cin.getline(choice, MAXCHAR);
        }
    }
    // isNameOrTitle is called as true
    else { 
        while (!cin || (
            tolower(choice[0]) != 'n' &&
            tolower(choice[0]) != 't' &&
            tolower(choice[0]) != 'e') || 
            strlen(choice) > 1) {
                cout << "Invalid choice, please enter N / T / E." << endl;
                cout << prompt;
                cin.getline(choice, MAXCHAR);
        }
        if (tolower(choice[0]) == 'e') {
            cout << "Returning to the main menu..." << endl;
        }
    }                                                                 
    return tolower(choice[0]);
}

// name: yesOrNo()
// there are enough opportunities for the user to check data, or incorrectly enter
// something that this function acts as a fail safe. Accepts a character argument,
// returns that character if it is a valid entry.
char yesOrNo(string prompt) {
    char decision = 'd'; // default
    
    cout << prompt;
    cin >> decision;
    
    while (!cin || cin.peek() != '\n' ||
    (tolower(decision) != 'y' && tolower(decision) != 'n')) {
        cout << "Oops, I didn't understand that." << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << prompt;
        cin >> decision;
    }
    cin.ignore(100, '\n');
    
    return tolower(decision);
}

// name: readDouble() 
// this function will take a user-input double, after given a prompt entered 
// as a parameter, and validate the double and return it.
double readDouble(string prompt) {
    double dbl = 0.0;
    
    cout << prompt;
    cin >> dbl;
    
    while (!cin || (dbl < 0.0 || dbl > 5.0) || cin.peek() != '\n') {
        cout << "Invalid entry! Please re-enter." << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << prompt;
        cin >> dbl;     
    }
    cin.ignore(100, '\n'); 
    
    return dbl;
}

// name: readText()
// this function, given a prompt to print to the user and a character array by
// reference that will be either title, or author name. This function validates
// the user by ensuring that input entered is NOT longer than MAXCHAR
void readText(string prompt, char array[]) {
    cout << prompt;
    cin.getline(array, MAXCHAR);
    
    while (cin.fail()) { // prevent user from entering title too long
        cout << "Error, please re-enter." << endl;
        cin.clear();
        cin.ignore(100, '\n');
        cout << prompt;
        cin.getline(array, MAXCHAR);
    }
}

// name: changeStars()
// this function will change the star rating at the user's request, called in
// case 'F' of the switch case in exeOption()
void changeStars(Book &book) {
    cout << "Enter new star rating: " << endl;
    book.rating = readDouble(">> ");
}

// name: caseInsensitiveMatch()
// This function will use the strcmp on two char arrays, after they've both 
// been altered to all lower case.
// returns true if the two arrays match, false if they do not
bool caseInsensitiveMatch(char array1[], char array2[]) {
    if (strlen(array1) != strlen(array2)) {
        return false;
    }
    for (int i = 0; i < strlen(array1); i++) {
        if (tolower(array1[i]) != tolower(array2[i])) {
            return false;
        }
    }
    return true;
}

// name: exeOption()
// "switchboard" for our program, takes the user through program after entering
// choice from menu
//void exeOption(Book shelf[], int &size, char &userChoice, int longest) {
void exeOption(Bookshelf &books, char &choice) {
    int index = -1;
    
    switch (choice) {
        case 'p':
            printAll(books);
            break;
            
        case 'q':
            // exiting the program
            break;

        case 'f':
            displaySearch();
            choice = readOption(">> ", true);
            if (choice != 'e') {
                char searchStr[MAXCHAR] = "default";
                
                if (choice == 'n') { // name
                    readText("\nEnter Author: ", searchStr);
                    index = findByAuthor(books, searchStr);
                }
                else if (choice == 't') { //title
                    readText("\nEnter Title: ", searchStr);
                    index = findByTitle(books, searchStr);
                }
                
                if (index != -1) {
                    cout << "\nFound book... " << endl;
                    printOne(books.shelves[index], books.longest);
                    
                    cout << "\nWould you like to change the stars? (Y/N)" << endl;
                    choice = yesOrNo(">> ");
                    if (choice == 'y') {
                        changeStars(books.shelves[index]);
                    }
                }
                // for if no book was found, and the user did not search by author
                else if (choice == 't') {
                    cout << "\nCould not find book..." << endl;
                }
            }
            break;
        case 'r':
            displaySearch();
            choice = readOption(">> ", true);
            // if 'e' back to main loop
            if (choice != 'e') {
               char searchStr[MAXCHAR] = "default";
                
                if (choice == 'n') { // name
                    readText("\nEnter Author: ", searchStr);
                    index = findByAuthor(books, searchStr);
                }
                else if (choice == 't') { //title
                    readText("\nEnter Title: ", searchStr);
                    index = findByTitle(books, searchStr);
                }
                
                if (index != -1) {
                    cout << "Removing book..." << endl;
                    removeBook(books, index);
                }
            }
            break;            
        case 'g':
            Book mostStars;
            mostStars = highestRated(books);
            cout << "\n";
            printOne(mostStars, books.longest);
            break;
        case 'a':
            if (books.count < MAXBOOK) {
                addBook(books);
            }
            else {
                cout << "Your bookshelf is full! Returning to menu..." << endl;
            }
            break;
        case 'd':
            Book toRead;
            toRead = nextRead(books);
            printOne(toRead, books.longest);
            break;
        default:
            cout << "Program error, terminating options." << endl;
            choice = 'q';
            break;
    }
}
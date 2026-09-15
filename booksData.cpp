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
# This file is for the functions that alter the struct, or affect the struct.
# find printing in tools.cpp
#******************************************************************************/

#include "booksData.h"
#include "tools.h"

using namespace std;

// name: loadData()
// this function opens our file from file stream, and places each book in the
// array of Book struct, shelf.
bool loadData(Bookshelf &books) {
    ifstream inFS;
    Book newBook;
    // opening the file
    inFS.open(fileName);
    if (!inFS) 
    {
        return false;
    }
    // prevent from loading a file too big by && less than MAXBOOK
    inFS.ignore(100, '\n'); // ignore the first line
    while (inFS.getline(books.shelves[books.count].title, MAXCHAR, ';') &&
    books.count < MAXBOOK)
    {
        inFS.getline(books.shelves[books.count].author, MAXCHAR, ';');
        inFS >> books.shelves[books.count].rating;
        inFS.ignore(100, '\n');
        if (strlen(books.shelves[books.count].author) > books.longest)
        {
            books.longest = strlen(books.shelves[books.count].author);
            
        }
        books.count++;
    }
    inFS.close();
    
    return true;
}

// name: findByTitle(Bookshelf &books)
// this function will look for a single book on the bookshelf by its title, only
// looks for exact matches, but makes sure they are not case sensitive.
// This function returns -1 if there is no match found.
int findByTitle(Bookshelf books, char title[]) {
    for (int index = 0; index < books.count; index++) {
        if (caseInsensitiveMatch(books.shelves[index].title, title)) {
            return index;
        }
    }
    return -1;
}

// name: findByAuthor()
// this function finds a book by author name. This function will find the FIRST
// occurence of a matching author. 
// If NO author is found it returns -1.
int findByAuthor(Bookshelf books, char author[]) {
    char choice = 'z';
    Bookshelf catalog;
    
    for (int index = 0; index < books.count; index++) {
        if (caseInsensitiveMatch(books.shelves[index].author, author)) {
            cout << "\nFound book: " << books.shelves[index].title << endl;
            cout << "Keep searching? (Y/N)" << endl;
            choice = yesOrNo(">> ");
            
            if (choice == 'y') {
                continue;
            }
            else {
                return index;
            }
        }
    }
    // no matches ever found
    if (choice == 'z') {
        cout << "\nUnable to find a book by " << author << "." << endl;
    }
    // matches found but unwanted by the user
    else {
        cout << "\nUnable to find more books by " << author << "." << endl;
    }
    cout << "Returning to main menu..." << endl;

    return -1;
}

// name: highestRated()
// this function will loop and just return a Book struct to be printed in the
// printOne() function.
Book highestRated(Bookshelf books) {
    Book highest;
    for (int i = 0; i < books.count; i++) {
        highest = (books.shelves[i].rating > highest.rating) ? books.shelves[i] : highest;
    }
    return highest;
}

// name: nextRead()
// this function uses random number generation, limited to the size of the current
// shelves, to pick an index of a book to read. This function takes our struct
// of books and returns a single book from that struct.
Book nextRead(Bookshelf books) {
    int index = 0;
    
    // random number seed
    srand(time(0));
    index = rand() % books.count;
    
    cout << "\nYou should consider reading..." << endl;

    return books.shelves[index];
}

// name: initBook()
// initializes a book from user input, exclusively called in addBook()
Book initBook() {
    Book book;
    
    char title[MAXCHAR];
    char author[MAXCHAR];
    double stars = 0.0;
    
    // grab user input
    cout << "\nLet's add a book!" << endl;
    readText("  Title: ", book.title);
    readText("  Author: ", book.author);
    book.rating = readDouble("  Star Rating: ");
    
    return book;
}

// name: addBook()
// this function will add a single book to our struct Bookshelf at shelves and
// update that struct at count, and longest IF the author name entered is longer
// this function will utilize initBook() from the user give input.
void addBook(Bookshelf &books) {
    int pos = 0;
    char decision = 'd';

    // initialize the book, initBook()
    Book newBook = initBook();
    
    // if book already exists, we search for it so we can return and not add
    // a duplicate
    if (findByTitle(books, newBook.title) != -1) {
        cout << "\nYou already have this book on the shelf!!!" << endl;
        return;
    }   
    
    // confirming with the user
    cout << endl;
    printOne(newBook, strlen(newBook.author));
    cout << "\nIs this the book to add? (Y/N)" << endl;
    decision = yesOrNo(">> ");
    
    while (decision != 'y') {
        cout << "\nLet's try again!" << endl;
        Book newBook = initBook();
        cout << endl;
        printOne(newBook, strlen(newBook.author));
        decision = yesOrNo(">> ");
    }
    
    // loop through books, find start position on alphabetical order,
    while (strcmp(books.shelves[pos].title, newBook.title) < 0) {
        pos++;
    }
    // shift book shelves to the right;
    for (int i = books.count; i > pos; i--) {
        books.shelves[i] = books.shelves[i-1];
    }
    books.shelves[pos] = newBook;
    // update books.count
    books.count++;
    
    // check if our new book's author name is longest, update that if so
    if (strlen(newBook.author) > books.longest &&
    strlen(newBook.author) < MAXCHAR) {
        books.longest = strlen(newBook.author);
    }
    
    cout << "\nBook added!" << endl;
}

// name: removeBook()
// this function removes a book and updates the books.count.
// Will need to watch out for books being removed when it's empty.
void removeBook(Bookshelf &books, int index) {
    if (books.count == 0) {
        cout << "Your shelves are empty! Maybe try to add something?" << endl;
        return;
    }
    
    for (int i = index; i < books.count - 1; i++) {
        books.shelves[i] = books.shelves[i + 1];
    }
    
    books.count--;
    
    return;
}

// name: printData()
// after the user enters quit, this function will print the updated data back
// into the text file.
bool printData(const Bookshelf books) {
    ofstream outFile;
    
    outFile.open(fileName);
    if (!outFile) {
        return false;
    }
    
    cout << "\nUpdating bookshelves..." << endl;
    
    // getting the header of the document printed
    outFile << "Title;Author;# Stars" << endl;
    for (int i = 0; i < books.count; i++) {
        outFile << books.shelves[i].title << ";";
        outFile << books.shelves[i].author << ";";
        outFile << books.shelves[i].rating << endl;
    }
    outFile.close();
    
    return true;
}
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
/* file for functions that will affect, change, or adjust values in our structs
This file has the struct definitions for our bookshelf */

#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cctype>
#include <fstream> 
#include <cstdlib>
#include <ctime>

using namespace std;

// any constants
const int MAXCHAR = 51;
const int MAXBOOK = 100;
const char fileName[MAXCHAR] = "books.txt";

// structs

struct Book {
    char title[MAXCHAR];
    char author[MAXCHAR];
    double rating;
};

struct Bookshelf { // initialized empty
    Book shelves[MAXBOOK]; 
    int longest = 0;
    int count = 0;
};

// function prototypes for booksData.cpp
//
// loading data into program
bool loadData(Bookshelf &books);
// initializing new books not loaded in program
Book initBook(char title[], char author[], double stars);
// adding, removing, or adjusting books
int findByAuthor(Bookshelf books, char author[]);
int findByTitle(Bookshelf books, char title[]);
Book highestRated(Bookshelf books);
Book nextRead(Bookshelf books);
void addBook(Bookshelf &books);
void removeBook(Bookshelf &books, int index);
bool printData(const Bookshelf books);
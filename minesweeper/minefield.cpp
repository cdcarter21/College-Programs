//------------------------------------------------------------------------------
// Developer---Cole Carter
// Course------CS3123-01
// Project-----Program #4
// Due---------April 18, 2025

// This is the implementation file for the minefield class.  
//------------------------------------------------------------------------------

#include <iostream>
#include "minefield.h"
#include "cell.h"
using namespace std;

//-------------------------------------------------------------------------------
// Minefield()
//
// The constructor for the Minefield class iterates through the Minefield array
// and creates a Cell object for each element to point to. 
//-------------------------------------------------------------------------------
Minefield::Minefield() {
    for (int i=0; i<8; i++) {
        for (int j=0; j<48; j++) {
            field[i][j] = new Cell();
        }
    }
}


//-------------------------------------------------------------------------------
// ~Minefield()
//
// The destructor for the Minefield class iterates through the Minefield array
// and deallocates each pointer to a Cell object. 
//-------------------------------------------------------------------------------
Minefield::~Minefield() {
    for (int i=0; i<8; i++) {
        for (int j=0; j<48; j++) {
            delete field[i][j];
        }
    }
}


//-------------------------------------------------------------------------------
// addMine
//
// This function will reassign a given element in the Minefield array to a Mine
// object. 
//-------------------------------------------------------------------------------
void Minefield::addMine(int row, int col) {
    delete field[row][col];
    field[row][col] = new Mine();
}


//-------------------------------------------------------------------------------
// show
//
// This function will output the Minefield to the screen. 
//-------------------------------------------------------------------------------
void Minefield::show(int revealMines) {
    cout << "                        1                   2                   3                   4" << endl; 
    cout << "    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 " << endl; 
    cout << "  +=================================================================================================+" << endl; 
    for (int i=0; i<8; i++) {
        cout << i << " | ";
        for (int j=0; j<48; j++) {
            if (revealMines)
                step(i, j);
            field[i][j]->showCell(revealMines);
        }
        cout << "|" << endl; 
    }
    cout << "  +=================================================================================================+" << endl; 
}


//-------------------------------------------------------------------------------
// winGame
//
// This function checks to see if all cells that aren't mines have been revealed. 
//-------------------------------------------------------------------------------
int Minefield::winGame() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 48; j++) {
            if (!field[i][j]->isMine() && !field[i][j]->isRevealed())
                return 0; 
        }
    }
    return 1;
}


//-------------------------------------------------------------------------------
// mark
//
// This function checks to see if a cell has been revealed. If it hasn't, it will
// call the setFlag() function. 
//-------------------------------------------------------------------------------
void Minefield::mark(int row, int col) {
    if (!field[row][col]->isRevealed())
        field[row][col]->setFlag();
}


//-------------------------------------------------------------------------------
// step
//
// This function implements stepping on a cell if it isn't flagged, protected, 
// or revealed. 
//-------------------------------------------------------------------------------
int Minefield::step(int row, int col) {
    if (row < 0 || row > 7 || col < 0 || col > 47)
        return 0;
    if (field[row][col]->isFlagged() || field[row][col]->isProtected() || field[row][col]->isRevealed()) 
        return 0;

    if (field[row][col]->isMine()) {
        return -1;
    }

    int mineCount = countMines(row, col);

    //make the cell a Revealed cell 
    delete field[row][col];
    field[row][col] = new Revealed(mineCount); 

    if (mineCount > 0) 
        return 0;

    for (int rowNum = -1; rowNum <= 1; rowNum++) {
        for (int colNum = -1; colNum <= 1; colNum++) {
            step(row + rowNum, col + colNum);
        }
    }
    return 0;
}


//-------------------------------------------------------------------------------
// countMines
//
// This function will take a given cell and check if all the surrounding cells
// are mines. 
//-------------------------------------------------------------------------------
int Minefield::countMines(int row, int col) {
    int mineCount = 0; 

    if (row != 0 && col != 0 && field[row-1][col-1]->isMine())
        mineCount++;
    if (row != 0 && field[row-1][col]->isMine())
        mineCount++;
    if (row != 0 && col != 47 && field[row-1][col+1]->isMine())
        mineCount++;
    if (col != 0 && field[row][col-1]->isMine())
        mineCount++;
    if (col != 47 && field[row][col+1]->isMine())
        mineCount++;
    if (row != 7 && col != 0 && field[row+1][col-1]->isMine())
        mineCount++;
    if (row != 7 && field[row+1][col]->isMine())
        mineCount++;
    if (row != 7 && col != 47 && field[row+1][col+1]->isMine())
        mineCount++;

    return mineCount;
}
//------------------------------------------------------------------------------
// Developer---Cole Carter
// Course------CS3123-01
// Project-----Program #4
// Due---------April 18, 2025

// This is the header file for the Minefield class.  
//------------------------------------------------------------------------------

#include "cell.h"

#ifndef MINEFIELD_H
#define MINEFIELD_H

class Minefield {
private:
	Cell* field[8][48];

public:
    Minefield();
    ~Minefield();

    int winGame();
    void show(int revealMines); 
    
    void mark(int row, int col);
    int step(int row, int col); 
    int countMines(int row, int col);
    void addMine(int row, int col);
};

#endif

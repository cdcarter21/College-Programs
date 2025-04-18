//------------------------------------------------------------------------------
// Developer---Cole Carter
// Course------CS3123-01
// Project-----Program #4
// Due---------April 18, 2025

// This is the implementation file for the Cell, Mine, and Revealed classes.  
//------------------------------------------------------------------------------

#include <iostream>
#include "cell.h"
#include "features.h"
using namespace std;

//-------------------------------------------------------------------------------
// Cell()
//
// The constructor the for the Cell class. 
//-------------------------------------------------------------------------------
Cell::Cell() {
    status = '.';
}


//-------------------------------------------------------------------------------
// Revealed()
//
// The constructor the for the Revealed class. 
//-------------------------------------------------------------------------------
Revealed::Revealed(int num) {
    number = num; 
}


//-------------------------------------------------------------------------------
// setFlag
//
// This function will set the flag of a cell according to what the cell already is.
//-------------------------------------------------------------------------------
void Cell::setFlag() {
    if (status == '.')
        status = 'F';
    else if (status == 'F')
        status = '?';
    else 
        status = '.';
}


//-------------------------------------------------------------------------------
// Cell::showCell
//
// This function will output a Cell according to what the status is. 
//-------------------------------------------------------------------------------
void Cell::showCell(bool revealMines) {
    //i utilized ANSI escape codes to provide color for various cells
    if (COLORS) {
        switch (status) {
            //orange
            case 'F':   cout << "\033[38;5;208mF\033[0m" << " ";
                        break;
            //black
            case '?':   cout << "\033[1;30m?\033[0m" << " ";
                        break;

            default:    cout << status << " ";
                        break;
        }
    }
    else 
        cout << status << " ";
}


//-------------------------------------------------------------------------------
// Mine::showCell
//
// This function overrides the Cell::showCell() function by outputting a Mine
// if the option is turned on.  
//-------------------------------------------------------------------------------
void Mine::showCell(bool revealMines) {
    if (revealMines) {
        if (COLORS)
            //red
            cout << "\033[1;31mM\033[0m" << " ";
        else 
            cout << "M" << " ";
    }
    else {
        //if not revealing mines, call the original method
        Cell::showCell(0);
    }

}


//-------------------------------------------------------------------------------
// Revealed::showCell
//
// This function overrides the Cell::showCell() function by outputting a the 
// number of mines surrounding the cell. 
//-------------------------------------------------------------------------------
void Revealed::showCell(bool revealMines) {
    //i utilized ANSI escape codes to provide color for various cells
    if (COLORS) {
        switch (number) {
            //blue
            case 1:     cout << "\033[1;34m1\033[0m" << " ";
                        break;
            //green
            case 2:     cout << "\033[1;32m2\033[0m" << " ";
                        break;
            //yellow
            case 3:     cout << "\033[1;33m3\033[0m" << " ";
                        break;
            //magenta
            case 4:     cout << "\033[1;35m4\033[0m" << " ";
                        break;
            //cyan
            case 5:     cout << "\033[1;36m5\033[0m" << " ";
                        break;
            //bright green
            case 6:     cout << "\033[38;5;121m6\033[0m" << " ";
                        break;
            //bright blue
            case 7:     cout << "\033[38;5;27m7\033[0m" << " ";
                        break;
            //bright green
            case 8:     cout << "\033[38;5;226m8\033[0m" << " ";
                        break;

            default:    cout << number << " ";
                        break;
        }
    }
    else 
        cout << number << " ";
}


//-------------------------------------------------------------------------------
// isFlagged
//
// This function checks if a Cell is flagged or not.
//-------------------------------------------------------------------------------
bool Cell::isFlagged() {
    if (status == 'F')
        return true;
    else
        return false;
}


//-------------------------------------------------------------------------------
// isProtected
//
// This function checks if a Cell is protected or not. 
//-------------------------------------------------------------------------------
bool Cell::isProtected() {
    if (status == '?')
        return true;
    else
        return false; 
}
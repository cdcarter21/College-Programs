//------------------------------------------------------------------------------
// Developer---Cole Carter
// Course------CS3123-01
// Project-----Program #4
// Due---------April 18, 2025

// This is the main driver for the minesweeper program.  
//------------------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <random>
#include "minefield.h"
#include "features.h"

#ifdef _WIN32
#define CLEAR "cls"
#include <windows.h>
#else
#define CLEAR "clear"
#include <unistd.h>
#endif

using namespace std;


int main()
{
    char action; 
    int row, column;
    Minefield m; 

    //if turned on, this will provide random generation of mines based on difficulty level:
    if (RANDOM_MINES)
    {
        char level; 
        system(CLEAR);
        cout << "Enter B for Beginner, I for Intermediate, or M for Master: ";
        cin >> level; 

        int mineNumber;
        if (level == 'B')
            mineNumber = 10;
        else if (level == 'I')
            mineNumber = 40;
        else if (level == 'M')
            mineNumber = 100;
        else {
            cout << "Please try again.\n";
            return 0;
        }

        mt19937 engine(random_device{}());
        uniform_int_distribution<int> mineRow(0, 7);
        uniform_int_distribution<int> mineCol(0, 47);

        for (int i = 0; i < mineNumber; i++) {
            m.addMine(mineRow(engine), mineCol(engine));
        }
    }
    else {
        //alternatively, you can manually change mines here:
        m.addMine(3, 7);
        m.addMine(3, 8);
        m.addMine(3, 9);
        m.addMine(4, 45);
        m.addMine(6, 43);
        m.addMine(2, 22);
        m.addMine(4, 22);
        m.addMine(0, 47);
    }

    while (action != 'E') {
        //if turned on, clear the terminal on each iteration for a better visual
        if (SCREEN_WIPE)
            system(CLEAR);

        m.show(0); 

        if (m.winGame() == 1) {
            cout << "\nCONGRATULATIONS!! YOU WIN!" << endl;
            return 0;
        }

        cout << "\nAction --- ";
        cin >> action; 
        if (action == 'E')
            return 0;

        cout << "Row ------ ";
        cin >> row; 
        if (row < 0 || row > 7) 
            continue; 

        cout << "Column --- ";
        cin >> column;
        if (column < 0 || column > 47) 
            continue;

        if (action == 'M')
            m.mark(row, column);
        else if (action == 'S') {
            if (m.step(row, column) == -1) {
                if (SCREEN_WIPE)
                    system(CLEAR);

                m.show(1); 
                
                cout << "\nYou stepped on the mine at (" << row << ", " << column << ")... GAME OVER!" << endl; 
                return 0;
            }
        }
    }
}

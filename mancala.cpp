#include "mancala.h"
#include <iostream>

Mancala::Mancala()
{
    for (int i=0; i<14; i++){
        if (i == 6 || i == 13)
            cells[i] = 0;
        else
            cells[i] = 4;
    }
    currentPlayer = 0;
}
int Mancala::getPlayer()
{ 
    //the counter variables are used to see if all of a player's cells are empty. if so, then the game is over.
    int counter1 = 0; 
    int counter2 = 0;
    for(int p= 0; p < 6; p++){
        if (cells[p] == 0)
            counter1++;
    }
    for (int q = 7; q < 13; q++)
        if (cells[q] == 0)
            counter2++;
    if (counter1 == 6){
        currentPlayer = -1; //I use currentPlayer being -1 or -2 later on to determine which player's pits are empty.
        return -1; 
    }
    else if (counter2 == 6){
        currentPlayer = -2;
        return -1;
    }
    else
        return currentPlayer; 
}
int Mancala::getScore(int player){
    if (player == 0)
        return cells[6];
    else
        return cells[13];
}
std::string Mancala::getBoard(){
    board = "";
    if (cells[13] > 9)
        board += std::to_string(cells[13]) + " |";
    else
        board += " " + std::to_string(cells[13]) + " |";
    for (int n=12; n>=7; n--)
    {
        if (cells[n] > 9)
            board += " " + std::to_string(cells[n]);
        else
            board += "  " + std::to_string(cells[n]); 
    }
    board += " |  ";
    if (currentPlayer == 0)
        board += "*\n - |";
    else if (currentPlayer == 1)
        board += "-\n * |";
    else if (currentPlayer == -1 || currentPlayer == -2)
        board += "-\n - |";
    for (int k=0; k<6; k++)
    {
        if (cells[k] > 9)
            board += " " + std::to_string(cells[k]);
        else
            board += "  " + std::to_string(cells[k]);
    }
    board += " | ";
    if (cells[6] > 9)
        board += std::to_string(cells[6]) + "\n";
    else 
        board += " " + std::to_string(cells[6]) + "\n";
    return board;
}
bool Mancala::move(int n){
    if (currentPlayer == 0)
        position = 6 - n;
    else 
        position = (6 - n) + 7;
    int value = cells[position];
    if (value == 0)
        return false; 
    cells[position] = 0;
    //the for loop moves through each pit and places a stone in it unless it's the opponent's goal
    for(int m=value; m > 0; m--){
        position = (position + 1)%14;
        if (position == 13 && currentPlayer == 0)
            position = (position + 1)%14;
        else if (position == 6 && currentPlayer == 1)
            position = (position + 1)%14;
        
        /*this is for if the last mancala stone ends in one of the current player's empty pits, then take all
        the stones from the opponent's pit across from it.*/
        if (m == 1){
            if (cells[position] == 0 && position != 6 && position != 13)
            {
                if (currentPlayer == 0 && position >= 0 && position < 6){
                    cells[6] += 1 + cells[(position - 12) * -1];
                    cells[(position - 12) * -1] = 0;
                }
                else if (currentPlayer == 1 && position > 6 && position < 13){
                    cells[13] += 1 + cells[(position - 12) * -1];
                    cells[(position - 12) * -1] = 0;
                }
                else 
                    cells[position] += 1;
            }
            else
                cells[position] += 1;
        }
        else 
            cells[position] += 1;
    }
    /*this if statement's purpose is for when the game is over, all the stones in the loser's pits are placed
    in their goal.*/
    if (getPlayer() == -1){
        if (currentPlayer == -1)
        {
            for (int w = 7; w < 13; w++){
                cells[13] += cells[w];
                cells[w] = 0;
            }
        }
        else
        {
            for (int y= 0; y < 6; y++){
                cells[6] += cells[y];
                cells[y] = 0;
            }
        }
    }

    /*this is for if the last stone is in the player's goal then the player goes again or
    if not then the players switch*/
    if (position == 6 && currentPlayer == 0)
        currentPlayer = 0; 
    else if (position == 13 && currentPlayer == 1)
        currentPlayer = 1;
    else
    {
        if (currentPlayer == 0)
            currentPlayer = 1;
        else if (currentPlayer == 1)
            currentPlayer = 0;
    }
    return true;
}
#include <iostream>
class Mancala{
    int cells[14];
    int currentPlayer, position;
    std::string board;
public:
    Mancala();
    int getPlayer();
    int getScore(int player);
    std::string getBoard();
    bool move(int n);
};
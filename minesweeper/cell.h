//------------------------------------------------------------------------------
// Developer---Cole Carter
// Course------CS3123-01
// Project-----Program #4
// Due---------April 18, 2025

// This is the header file for the Cell, Mine, and Revealed classes.  
//------------------------------------------------------------------------------

#ifndef CELL_H
#define CELL_H

class Cell {
protected:
    char status;

public:
    Cell();

    bool isFlagged();
    bool isProtected();
    
    void setFlag();
    char getStatus() { return status; }; 

    virtual bool isMine() const { return false; }; 
    virtual bool isRevealed() const { return false; }
    virtual void showCell(bool revealMines);
};


class Mine : public Cell {
public:
    bool isMine() const override { return true; }; 
    void showCell(bool revealMines) override; 
};


class Revealed : public Cell {
private:
    int number; 

public: 
    Revealed(int num);
    
    bool isRevealed() const override { return true; }
    bool isMine() const override { return false; }; 
    void showCell(bool revealMines) override; 
};

#endif
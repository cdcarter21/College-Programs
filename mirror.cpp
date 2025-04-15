#include <iostream>
using namespace std;


int main(int argc,char *argv[])
{
    (void)argc;
    int height = stoi(argv[1]); //rows
    int width = stoi(argv[2]); //columns
    /*this statement gives us a dynamically allocated array to hold the size of the
    parameters given and initializes all the elements with 0.*/
    bool *grid { new bool[height * width]{false}};
    int y = 0;
    int x = 0;
    int dx = 1;
    int dy = 1;
    int cells = 0;
    int reflections = 0;
    bool a = true;
    /*this while loop continutes as long as we don't reach a cell we've already been to.*/
    while (grid[y * width + x] != 1)
    {
        /*this statement will mark our territory for this current cell.*/
        grid[y * width + x] = 1;
        cells++;
        /*I used this if statement for a continue statement simply because I needed 
        x and y to both be one before the next if statements but I also needed them 
        to equal 0 at the beginning of this loop*/
        if (a == true){
            a = false;
            x++;
            y++;
            continue;
        }
        /*these next two if statements check to see if we need to change direction since
        we our bumping into a wall. it also adds to our number of reflections counter.*/
        if (y == height-1 || y == 0){
            dy *= -1;
            reflections++;
        }
        if (x == width-1 || x == 0){
            dx *= -1;
            reflections++;
        }
        /*these two statements change where our next cell is.*/
        x += dx;
        y += dy;
    }
    /*use this to see grid
    int counter = 0;
    for (int i = 0; i < (height*width); i++){
        cout << grid[i] << " ";
        counter++;
        if (counter == height){
            cout << "\n";
            counter = 0; 
        }
    }*/
    delete[] grid;
    cout << cells << " cells, " << reflections << " reflections" << "\n";
    return 0;    
}
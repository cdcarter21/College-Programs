#include "lightsout.h"

LightsOut::LightsOut()
{
    //all the elements are set to false which will be considered "off"
    for(int i=0; i < 25; i++)
        grid[i] = false;
}
void LightsOut::on (int row, int col){
    //i multiply by 5 in the grid indexing to get to the current row we're on and then add the column number
    //i also subtract row and column by 1 because row 1 would technically be row 0 in the array
    //lastly, i set that element to true to turn the light on
    grid[(5 * (row - 1)) + (col - 1)] = true;
}
bool LightsOut::get (int row,int col){
    return grid[(5 * (row - 1)) + (col - 1)];
}
void LightsOut::toggle (int row,int col){
    //i use start here to simply make my indexing shorter to type
    int start = 5 * (row - 1) + (col - 1);
    //i set our starting element to whatever the opposite of it is
    grid[start] = !grid[start];
    
    //these if statements toggle all the available neighbors of the starting element
    if ((start - 5) > -1)
        grid[start - 5] = !grid[start - 5];
    if ((start + 5) < 25)
        grid[start + 5] = !grid[start + 5];
    if (col != 1)
        grid[start - 1] = !grid[start - 1];
    if (col != 5)
        grid[start + 1] = !grid[start + 1];
}
bool LightsOut::success(){
    /*i use counter here to check if all the lights are off by traversing the array and 
    adding one to the counter if the element is off. if the counter is 25, indicating all
    elements were off, then we return true.*/
    int counter = 0;
    for (int j = 0; j < 25; j++){
        if (grid[j] == false)
            counter++;
    }
    if (counter == 25)
        return true;
    else
        return false;
}
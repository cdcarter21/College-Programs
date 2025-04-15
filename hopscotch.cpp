#include <iostream>
using namespace std;

int main()
{
    int times, size, x, element;
    cin >> times;
    //program will loop for as many times as the user enters.
    for (int i=0; i<times; i++){
        element = 0;
        cin >> size;
        /*the program creates an int array to hold the values the user entered and a bool
        array to be used to check if we've been here before for each time we go through the loop.*/
        int* list = new int[size]{0};
        bool* beenHere = new bool[size]{false};

        //inputing list
        for(int j=0; j<size; j++){
            cin >> x;
            list[j] = x;
        }
        //we will keep hopping as long as we haven't been at the current element before.
        while (beenHere[element] == false)
        {
            beenHere[element] = true;
            element += list[element];
            /*I used the element variable which represents the current index number to see 
            if we exit at the far or near side by seeing if the index number would be larger 
            or smaller than the array. I also check to see if we've been here before and output 
            the invalid message if so.*/
            if (element >= size){
                cout << "valid\n";
                break;
            }
            else if (element < 0){
                cout << "invalid\n";
                break;
            }
            else if (beenHere[element] == true)
                cout << "invalid\n";
        }

        delete[] list;
        delete[] beenHere;
    }
}
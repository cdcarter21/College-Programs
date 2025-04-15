#include <iostream>
#include "adt_list.h"
using namespace std;

int main(int argc, char *argv[])
{
    (void) argc;
    int num = 0;  
    int factor = stoi(argv[1]);
    List<int> list;
    
    //the while loop reads in the data from the command line and appends each number to the list
    while(cin >> num) {
        list.append(num);
    }

    //the for loop checks whether an element is a multiple of factor (the K factor) and if it isn't, it removes it from the list, increments it 
    //until it is a multiple of the factor, and then will put it back in the list as many spaces ahead as it took to increment the element. 
    //if an element is already a multiple of factor, we just increment the operator to move to the next element. if we are at the end of the list,
    //the else block will simply append the element at the end of the list and then set i equal to the tail so i won't be invalid. 
    for (List<int>::Iterator i=list.getHead(); i; i++) {
        int j = *i;
        bool executed = false; 
        while(j % factor != 0) {
            if (executed == false)
                i.remove();
            j++;
            if (i) {
                i++; 
            }
            executed = true; 
        }
        if (executed == true) {
            if (i) {
                i.insert(j);
            }
            else {
                list.append(j);
                //break;
                i=list.getTail();
            }
        }
    }

    //for loop to print out the final list
    for (List<int>::Iterator i=list.getHead(); i; i++) {
        cout << *i << " ";
    }
    cout << "\n";
}
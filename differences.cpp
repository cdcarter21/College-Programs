#include <iostream>
using namespace std;

bool contains (int array[], int checking, int count) {
    for (int j=0; j<count; j++) {
        if (array[j] == checking)
            return true;
    }
    return false;
}

int main(int argc, char *argv[]) 
{
    int count = argc - 2; 
    int data[50] = { 0 };
    int arrayCounter = 0;
    int difference = 0;
    for (int i=1; i<=count; i++) {
        difference = abs(stoi(argv[i]) - stoi(argv[i+1]));
        data[arrayCounter] = difference; 
        arrayCounter++;
    }
    bool answer = true;  
    for (int i=1; i<=count; i++) {
        answer = contains(data, i, arrayCounter);
        if (answer == false) { 
            cout << "Bad sequence: missing " << i << ".\n";
            break; 
        }
    }
    if (answer == true)
        cout << "Good sequence.\n";
}
#include <iostream>
using namespace std; 

/*this function takes the user's command line parameters and uses the Gregorian 
calender formulas to compute what day that date falls on. the number returned will be 
0-6 representing Sunday-Saturday*/
int dayofweek (int month, int day, int year)
{
    int ySub = year - ((14 - month)/12);
    int x = ySub + (ySub / 4) - (ySub / 100) + (ySub / 400);
    int mSub = month + 12 * ((14 - month) / 12) - 2;
    int dSub = (day + x + (31 * mSub)/12) % 7;
    return dSub;
}


int main (int argc,char * argv[])
{
    (void)argc;
    int userMonth = stoi(argv[1]);
    int userDay = stoi(argv[2]);
    int userYear = stoi(argv[3]);
    int answer = dayofweek(userMonth, userDay, userYear);
    cout << userMonth << "/" << userDay << "/" << userYear << " falls on ";
    
    /*these if statements take the number computed by the dayofweek function and determines
    what day of the week the user's date falls on using 0-6 as Sunday-Saturday.*/
    if (answer == 0)
        cout << "Sunday.\n";
    else if (answer == 1)
        cout << "Monday.\n";
    else if (answer == 2)
        cout << "Tuesday.\n";
    else if (answer == 3)
        cout << "Wednesday.\n";
    else if (answer == 4)
        cout << "Thursday.\n";
    else if (answer == 5)
        cout << "Friday.\n";
    else if (answer == 6)
        cout << "Saturday.\n";
    
    return 0;
}
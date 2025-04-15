#include <iostream>
#include "adventure.h"
using namespace std;

int main()
{
    Adventure game;
    int count = 1;
    int check = 1;
    Path p[1000];
    p[0] = game.getStart();
    
    while (count != 0)
    {
        check = count;
        Path current = p[count-1];
        Room r = game.getRoom(current);
        if (r.isExit() == true){
            cout << current << "\n";
            break;
        }
        Door first = r.getFirstDoor();
        Path test = current;
        //if (r.isValidDoor(first) == true){
        if (test.add(first) == true){
            count++;
            p[count-1] = test;
        }
            //p[count-1].add(first);
            //cout << "whatever\n";
        //}

        Door d = r.getNextDoor(first);
        if (r.isValidDoor(first) == false || r.isValidDoor(d) == false)
            count--;
        if (p[count-1].add(d) == false)
            count--;
        while (r.isValidDoor(d) == true)
        {
            cout << "hi?\n";
            count++;
            p[count-1] = current;
            p[count-1].add(d);
            d = r.getNextDoor(d);
        }
        cout << "glass\n";
        cout << p[1] << "\n";
        cout << count << "\n";
 /*   for (Door d = r.getNextDoor(first); r.isValidDoor(d) == true; d = r.getNextDoor(d))
        {
            cout << "hi?\n";
            count++;
            p[count-1] = current;
            p[count-1].add(d);
        }
 */
/*      while (current.add(d) == true)
        {
            cout << "huh?\n";
            count++;
            p[count-1] = current;
            p[count-1].add(d);
            d = r.getNextDoor(d);
        }
 */     

/*         if (check == count){
            count--;
            cout << "hola\n";
        }
 */ }
    if (count == 0)
        cout << "no solution\n";
}

/*     for (int i = 0; i < 1000; i++)
    {
        Room r = game.getRoom(p[i]);
        if (r.isExit() == true){
            cout << p[i] << "\n";
            break;
        }
        Door first = r.getFirstDoor();
        Door d = r.getNextDoor(first);
        while (r.isValidDoor(d) == true)
        {
            count++;
            p[count] = p[i];
            p[count].add(d);
            d = r.getNextDoor(d);
        }
 */
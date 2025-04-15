#include <iostream>
#include <cassert>

int hashKey(int x) {
    return x;
}

#include "setHash.h"
using namespace std;

// int main()
// {
//     Set<int> s;
//     initialize(s);
//     assert(size(s) == 0);
//     insert(s,42);
//     peek(s);
//     assert(size(s) == 1);
//     assert(!contains(s,1));
//     assert(contains(s,42));
//     for (int i=0; i<50; i++)
//         insert(s,i);
//     assert(size(s) == 50);
//     peek(s);
//     for (int i=0; i<100; i+=3)
//         remove(s,i);
//     assert(contains(s,1));
//     //peek(s);
//     destroy(s);
// }

// int main()
// {
//     Set<char> s;
//     initialize(s);
//     //peek(s);
//     for (int i=0; i<256; i++) {
//         char c = (char)(i*7);
//         //cout << "we are on: " << i << endl; 
//         assert(!contains(s,c));
//         insert(s,c);
//         assert(contains(s,c));
//         //peek(s);
//         cout << endl; 
//         assert(size(s)==i+1);
//     }
//     //peek(s);
//     for (int i=0; i<256; i++) {
//         char c = (char)(i*11);
//         assert(contains(s,c));
//         remove(s,c);
//         assert(!contains(s,c));
//         assert(size(s)==255-i);
//     }
//     assert(s.size == 640);
// }

int main () {
    Set<string> s;
    initialize(s);
    destroy(s);
}
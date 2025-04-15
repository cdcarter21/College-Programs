#include <iostream>
#include <cassert>
#include "setlinked.h"
using namespace std;

int main()
{
    Set<int> s;
    initialize(s);
    assert(size(s) == 0);
    insert(s,42);
    assert(size(s) == 1);
    assert(!contains(s,1));
    assert(contains(s,42));
    for (int i=0; i<50; i++)
        insert(s,i);
    assert(size(s) == 50);
    for (int i=0; i<100; i+=3)
        remove(s,i);
    assert(contains(s,1));
    destroy(s);
}
#include <iostream>
#include <cassert>
#include "pq.h"
using namespace std;

int main()
{
    PriorityQueue<int,string> pq;
    initialize(pq,10);
    assert(size(pq) == 0);
    insert(pq,42,"hi");
    assert(size(pq) == 1);
    auto x = pop(pq);
    assert(x == "hi");
    assert(size(pq) == 0);
    destroy(pq);
}
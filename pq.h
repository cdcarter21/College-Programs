template <typename R,typename V>
struct PriorityQueue {
    R *         rank;
    V *         value;
    int         values;
    int         size;
};

template <typename R,typename V> void initialize(PriorityQueue<R,V> &pq,int size) {
    pq.rank = new R[size];
    pq.value = new V[size];
    pq.values = 0;
    pq.size = size;
    return; 
}

template <typename R,typename V> void destroy(PriorityQueue<R,V> &pq) {
    delete[] pq.rank;
    delete[] pq.value;
    return;
}

template <typename R,typename V> void swap(PriorityQueue<R,V> &pq,int i,int j) {
    R holdR = pq.rank[i];
    V holdV = pq.value[i];
    pq.rank[i] = pq.rank[j];
    pq.value[i] = pq.value[j];
    pq.rank[j] = holdR;
    pq.value[j] = holdV;
    return;
}

template <typename R,typename V> void resize(PriorityQueue<R,V> &pq) {
    R *newR = new R[pq.size*2];
    V *newV = new V[pq.size*2];
    for (int i=0; i<pq.size; i++) {
        newR[i] = pq.rank[i];
        newV[i] = pq.value[i];
    } 
    destroy(pq);
    pq.rank = newR;
    pq.value = newV;
    pq.size *= 2; 
    return;
}

template <typename R,typename V> void repairInsert(PriorityQueue<R,V> &pq) {
    int i = pq.values;
    while (i > 0 && pq.rank[i] > pq.rank[(i-1)/2]) {
        swap(pq, i, (i-1)/2);
        i = (i-1)/2;
    }
 }

template <typename R,typename V> void insert(PriorityQueue<R,V> &pq,R rank,V value) {
    if (pq.values == pq.size)
        resize(pq);
    pq.rank[pq.values] = rank;
    pq.value[pq.values] = value; 
    int i = pq.values; 
    repairInsert(pq);
    pq.values++;
    return;
}

template <typename R,typename V> void repairPop(PriorityQueue<R,V> &pq) {
    int i = 0;
    while (i < pq.values/2) {
        int j = i;
        if ((2*i)+1 < pq.values && pq.rank[i] < pq.rank[(2*i)+1])
            j = (2*i)+1;
        if ((2*i)+2 < pq.values && pq.rank[j] < pq.rank[(2*i)+2])
            j = (2*i)+2;
        if (i == j)
            break;
        swap(pq, i ,j);
        i = j;
    }
}

template <typename R,typename V> V pop(PriorityQueue<R,V> &pq) {
    V m = pq.value[0];
    swap(pq,0, pq.values-1);
    int i=0;
    pq.values--;
    repairPop(pq);
    return m;
}

template <typename R,typename V> int size(PriorityQueue<R,V> &pq) {
    return pq.values; 
}

//remember to remove
#include <iostream>
using namespace std;
template <typename R,typename V> void peek(PriorityQueue<R,V> &pq) {
    for(int i=0; i<pq.values; i++) {
        cout << pq.value[i] << " " << pq.rank[i] << endl; 
    }
}
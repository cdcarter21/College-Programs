using namespace std;

enum Status { UNUSED, USED, TOMBSTONE };
int hashKey(int x);

template <typename T>
struct Bucket {
    Status  status;
    T       value;
};

template <typename T>
struct Set {
    Bucket<T> * table;
    int         keys;
    int         size;
};

template <typename T> void initialize(Set<T> &set) {
    set.size = 10;
    set.keys = 0;
    set.table = new Bucket<T>[set.size];
    for(int i = 0; i < set.size; i++) 
        set.table[i].status = UNUSED;
}

template <typename T> void destroy(Set<T> &set) {
    delete set.table;
}

template <typename T> int find(Set<T> &set,T item) {
    int i = hashKey(item)%set.size;
    int tomb = -1;
    while( set.table[i].status != UNUSED && set.table[i].value != item) {
        if(tomb == -1 && set.table[i].status == TOMBSTONE)
            tomb = i; 
        i = (i+1)%set.size;
    }
    return tomb == -1 ? i : tomb;
}

template <typename T> void insert(Set<T> &set,T item) {
    int i = find(set, item);
    if(set.table[i].status == USED)
        return;
    set.keys++;
    set.table[i].value = item; 
    set.table[i].status = USED;
    if(set.keys*2 >= set.size)
        resize(set);
}

template <typename T> void remove(Set<T> &set,T item) {
    int i = find(set, item);
    if(set.table[i].status != USED) 
        return;
    set.keys--;
    set.table[i].status = TOMBSTONE;
}

template <typename T> bool contains(Set<T> &set,T item) {
    int i = find(set, item);
    return set.table[i].value == item && set.table[i].status == USED;
}

template <typename T> int size(Set<T> &set) {
    return set.keys;
}

template <typename T> void resize(Set<T> &set) {
    Set<T> newSet;
    newSet.table = new Bucket<T>[set.size*2];
    newSet.keys = 0;
    newSet.size = set.size*2;
    for(int i = 0; i < set.size; i++) {
        if(set.table[i].status == USED)
            insert(newSet, set.table[i].value);
    }
    delete set.table;
    set = newSet;
}

//stuff below removed before submission
// #include <iostream>
// template <typename T> void peek(Set<T> &set) {
//     for(int i = 0; i < set.size; i++) {
//         cout << set.table[i].status << " : " << set.table[i].value << endl;
//     }    
// }


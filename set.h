template <typename T>
struct Set {
    T *  items;
    int  count;
};

template <typename T> void initialize(Set<T> &set,int max)
{
    set.items = new T[max];
    set.count = 0; 
};
template <typename T> void destroy(Set<T> &set)
{
    delete[] set.items;
};
template <typename T> void insert(Set<T> &set,T item)
{
    for (int i=0; i<set.count; i++) {
        if (set.items[i] == item)
            return;
    }
    set.items[set.count] = item;  
    set.count++;
};
template <typename T> void remove(Set<T> &set,T item)
{
    for (int i=0; i<set.count; i++) {
        if (set.items[i] == item) {
            for (int j=i; j<set.count; j++) {
                set.items[j] = set.items[j+1];
            }
            set.count--; 
        }
    }
};
template <typename T> bool contains(Set<T> &set,T item)
{
    for (int i=0; i<set.count; i++) {
        if (set.items[i] == item)
            return true; 
    }
    return false; 
};
template <typename T> int  size(Set<T> &set)
{
    return set.count; 
};
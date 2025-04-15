template <typename T>
struct Node {
    T value;
    Node* next;
};

template <typename T>
struct Set {
    Node<T>* head;
};

template <typename T> void initialize(Set<T> &set) {
    set.head = nullptr;
}

template <typename T> void destroy(Set<T> &set) {
    Node<T>* current = set.head;
    Node<T>* currentNext;
    while(current != nullptr) {
        currentNext = current -> next;
        delete current;
        current = currentNext;
    }
    set.head = nullptr;
    return;
}

template <typename T> void insert(Set<T> &set,T item) {
    if(contains(set,item))
        return;
    Node<T>* hold = new Node<T>;
    hold -> value = item;
    hold -> next = set.head;
    set.head = hold;
}

template <typename T> void remove(Set<T> &set,T item) {
    Node<T>* current = set.head;
    Node<T>** from = &(set.head);
    while(current != nullptr) {
        if(current -> value == item) {
            *from = current -> next;
            delete current;
            return;
        }
        from = &(current -> next);
        current = current -> next;
    }
}

template <typename T> bool contains(Set<T> &set,T item) {
    Node<T>* current = set.head;
    Node<T>** from = &(set.head);
    while(current != nullptr) {
        if(current -> value == item){
            *from = current -> next;
            current -> next = set.head;
            set.head = current;
            return true;
        }
        from = &(current -> next);
        current = current -> next;
    }
    return false;
}

template <typename T> int  size(Set<T> &set) {
    Node<T>* current = set.head;
    int count = 0;
    while(current != nullptr) {
        current = current -> next;
        count += 1;
    }
    return count;
}

//This was not in the submission, but was very helpful for testing.
// template <typename T> void  peek(Set<T> &set) {
//     Node<T> * current = set.head;
//     while(current != nullptr) {
//         std::cout << current -> value << std::endl;
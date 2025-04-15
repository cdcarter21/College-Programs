#include <iostream>
#include <algorithm>
template <typename T>
struct Node {
    T       value;
    Node *  left;
    Node *  right;
};

template <typename T>
struct Set {
    Node<T> *  root;
};

template <typename T> void rDestroy(Node<T> *node) {
    if(node == nullptr) return;
    rDestroy(node->left);
    rDestroy(node->right);
    delete node;
}


template <typename T> void rInsert(Node<T> **node, T value) {
    if(*node == nullptr) {
        *node = new Node<T>;
        (*node)->value = value;
        return;
    }

    if(value == (*node)->value) return;
    
    if(value < (*node)->value)
        rInsert(&(*node)->left, value);
    else
        rInsert(&(*node)->right, value);
}
//finds the minimum item of the right child of the node we are removing 
// template <typename T> T rFindMin(Node<T> *node) {
//     Node<T>* p = node; 
//     while (p->left != nullptr)
//         p = p->left; 
//     return p->value; 
// }

template <typename T> void rRemove(Node<T> **node, T value) {
    if(*node == nullptr) return;
    if(value == (*node)->value) {
        //No children case
        if((*node)->right == nullptr && (*node)->left == nullptr) {
            delete(*node);
            *node = nullptr;
        }
        //two children case
        else if ((*node)->right != nullptr && (*node)->left != nullptr) {
            Node<T>** successor = &((*node)->right);
            while((*successor)->left != nullptr) successor = &(*successor)->left;
            (*node)-> value = (*successor)->value;
            Node<T>* hold = (*successor); 
            (*successor) = (*successor)->right;
            delete hold;
        }
        //one child case
        else {
            Node<T>* hold;
            if((*node)->right != nullptr) hold = (*node)->right;
            else hold = (*node)->left;
            delete (*node);
            (*node) = hold;
        }
        return;
    }

    if(value < (*node)->value) {
        rRemove(&(*node)->left, value);
    }else {
        rRemove(&(*node)->right, value);
    } //comment
}

// template <typename T> Node<T>* rRemove(Node<T> *node, T value) {
//     if(node == nullptr) 
//         return nullptr; 
//     //look at the left node is the value we want to remove is less than the current value
//     if (value < node->value) 
//         node->left = rRemove(node->left, value);
//     //look at the right node is the value we want to remove is greater than the current value
//     else if (value > node->value)
//         node->right = rRemove(node->right, value);
//     //once we have found the node we want to remove
//     else {
//         //if we have two children
//         if (node->left != nullptr && node->right != nullptr) {
//             node->value = rFindMin(node->right); 
//             node->right = rRemove(node->right, node->value);
//         }
//         //if we only have the left child
//         else if (node->left != nullptr) 
//             node = node->left; 
//         //if we only have the right child
//         else if (node->right != nullptr) 
//             node = node->right;
//         //if we have no children
//         else    
//             node = nullptr; 
//     }
//     return node; 
// }

template <typename T> int rContains(Node<T> * node, T value) {
    if(node == nullptr) return 0;
    if(node->value == value) return 69;
    int contains = 0;
    //left
    contains = std::max(rContains(node->left, value), contains);
    //right
    contains = std::max(rContains(node->right, value), contains);
    return contains;
}

template <typename T> int rSize(Node<T> * node) {
    if(node == nullptr) return 0;
    return 1 + rSize(node->left) + rSize(node->right);
}

// used for testing:
// template <typename T> void peek(Node<T> *node) {
//     if(node == nullptr) return;
//     std::cout << node->value << std::endl;
//     peek(node->left);
//     peek(node->right);
// }

template <typename T> void initialize(Set<T> &set) {
    set.root = nullptr;
}

template <typename T> void destroy(Set<T> &set) {
    rDestroy(set.root);
    set.root = nullptr;
}

template <typename T> void insert(Set<T> &set,T item) {
    rInsert(&set.root, item);
}

template <typename T> void remove(Set<T> &set,T item) {
    rRemove(&set.root, item);
}

template <typename T> bool contains(Set<T> &set,T item) {
    return rContains(set.root, item);
}

template <typename T> int size(Set<T> &set) {
    return rSize(set.root);
}
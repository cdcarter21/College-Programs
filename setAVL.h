#include <algorithm>
template <typename T>
struct Node {
    T       value;
    int     height;
    Node *  left;
    Node *  right;
};

template <typename T>
struct Set {
    Node<T> *  root;
};


template <typename T> Node<T>* rotateR(Node<T> *node) {
    Node<T> *q = node->left;
    Node<T> *p = q->right;
    q->right = node;
    node->left = p;

    node->height = std::max(node->left->height, node->right->height) + 1; 
    q->height = std::max(q->left->height, q->right->height) + 1; 
    return q; 
}

template <typename T> Node<T>* rotateL(Node<T> *node) {
    Node<T> *q = node->right;
    Node<T> *p = q->left;
    q->left = node;
    node->right = p;

    node->height = std::max(node->left->height, node->right->height) + 1; 
    q->height = std::max(q->left->height, q->right->height) + 1;
    return q; 
}

template <typename T> void rDestroy(Node<T> *node) {
    if(node == nullptr) return;
    rDestroy(node->left);
    rDestroy(node->right);
    delete node;
}

template <typename T> int rContains(Node<T> * node, T value) {
    if(node == nullptr) return 0;
    if(node->value == value) return 1;
    if(node->value > value)
        return rContains(node->left, value);
    return rContains(node->right, value);
}

// template <typename T> void insertBalance(Node<T> **node, T value) {
//     if ((*node) == NULL)
//         return 0; 
//     else
//         int b = (*node)->left->height - (*node)->right->height;
//     if (b > 1 && value < (*node)->left->value)
//         return rotateR(*node);
//     else if (b < -1 && value > (*node)->right->value)
//         return rotateL(*node);
//     else if (b > 1 && value > (*node)->left->value) {
//         (*node)->left = rotateL((*node)->left);
//         return rotateR(*node);
//     }
//     else if (b < -1 && value < (*node)->right->value) {
//         (*node)->right = rotateR((*node)->right);
//         return rotateL(*node);
//     }
//     return node;
// }

template <typename T> Node<T>* rInsert(Node<T> *node, T value) {
    if(node == nullptr) {
        node = new Node<T>;
        node->value = value;
        node->height = 1;
        node->left = nullptr;
        node->right = nullptr;
        return 0; 
    }
    
    if (value < node->value)
        node->left = rInsert(node->left, value);
    else if (value > node->value)
        node->right = rInsert(node->right, value);
    else
        return node; 

    node->height = 1 + std::max(node->left->height, node->right->height);

    int b = 0; 
    if (node == NULL)
        return 0; 
    else
        b = node->left->height - node->right->height;
    if (b > 1 && value < node->left->value)
        return rotateR(node);
    else if (b < -1 && value > node->right->value)
        return rotateL(node);
    else if (b > 1 && value > node->left->value) {
        node->left = rotateL(node->left);
        return rotateR(node);
    }
    else if (b < -1 && value < node->right->value) {
        node->right = rotateR(node->right);
        return rotateL(node);
    }
    return node;
}

template <typename T> void rRemove(Node<T> **node, T value) {
    if(*node == nullptr) return;
    if(value == (*node)->value) {

        if((*node)->right == nullptr && (*node)->left == nullptr) {
            //No children case
            delete(*node);
            *node = nullptr;
        }
        else if ((*node)->right != nullptr && (*node)->left != nullptr) {
            //two children case
            auto successor = &((*node)->right);
            while((*successor)->left != nullptr) successor = &(*successor)->left;
            (*node)-> value = (*successor)->value;
            auto hold = (*successor); 
            (*successor) = (*successor)->right;
            delete hold;
        }
        else {
            //one child case
            auto hold = (*node)->left;
            if((*node)->right != nullptr) hold = (*node)->right;
            delete (*node);
            (*node) = hold;
        }
    }

    else if(value < (*node)->value)
        rRemove(&(*node)->left, value);
    else
        rRemove(&(*node)->right, value);
}

template <typename T> int rSize(Node<T> *node) {
    if(node == nullptr) return 0;
    return 1 + rSize(node -> right) + rSize(node -> left);
}

template <typename T> void initialize(Set<T> &set) {
    set.root = nullptr;
}

template <typename T> void destroy(Set<T> &set) {
    rDestroy(set.root);
    set.root = nullptr;
}

template <typename T> void insert(Set<T> &set,T value) {
    rInsert(set.root, value);
}

template <typename T> void remove(Set<T> &set,T value) {
    rRemove(&set.root, value);
}

template <typename T> bool contains(Set<T> &set,T value) {
    return rContains(set.root, value);
}

template <typename T> int  size(Set<T> &set) {
    return rSize(set.root);  
}



#include <iostream>
#include <string>
#include <algorithm>
#include <random>
std::string tree[1000];
int maxDepth = 6;
template <typename T> void peek(Set<T> &set, int what) {
    rPeek(set.root, 0, what);
    for(int i = 0; i < maxDepth+1; i++) {
        std::cout << tree[i] << std::endl;
    }
}

template <typename T> void rPeek(Node<T> * node, int depth, int what) {
    if(depth > maxDepth)
        return;
    if(tree[depth] == "") {
        for(int j = 0; j < (1 << (maxDepth-depth))/2; j++)
            tree[depth] += " ";
    }
    if(node == nullptr) {
        tree[depth] += " ";
        rPeek(node, depth+1, what);
        rPeek(node, depth+1, what);
    }
    else {
        if(what == 0)
            tree[depth] += std::to_string(node->value);
        else
            tree[depth] += std::to_string(node->height);
        rPeek(node->left, depth+1, what);
        rPeek(node->right, depth+1, what);
    }
    for(int j = 0; j < (1 << (maxDepth-depth)); j++)
        tree[depth] += " ";
}
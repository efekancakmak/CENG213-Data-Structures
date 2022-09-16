#ifndef BST_HPP
#define BST_HPP

#include <iostream>

#include "BSTNode.hpp"

template <class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot();

    void insert(const T &data);
    void remove(const T &data);
    BSTNode<T> *find(const T &data);
    void printInorder();

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void printInorder(BSTNode<T> *node);
    BSTNode<T> *copier(BSTNode<T> *root);
    void destroyer(BSTNode<T> *root);
    BSTNode<T> *inserter(BSTNode<T> *root,const T &data);
    BSTNode<T> *getRightMin(BSTNode<T> *root);
    void remover(BSTNode<T> *& root,const T &data);

private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_HPP

template <class T>
BST<T>::BST() {
    root = NULL;
}


template <class T>
BSTNode<T> *BST<T>::copier(BSTNode<T> *root){
    if(root==NULL)
        return NULL;
    BSTNode<T> *nw = new BSTNode<T>;
    nw->data = root->data;
    nw->left = copier(root->left);
    nw->right = copier(root->right);
    return nw;
}

template <class T>
BST<T>::BST(const BST<T> &obj) {
    BSTNode<T> *trv = obj.root;
    root = copier(trv);
}

template <class T>
void BST<T>::destroyer(BSTNode<T> *root){
    if(root==NULL)
        return;
    destroyer(root->left);
    destroyer(root->right);
    delete root;
    root = NULL;
}

template <class T>
BST<T>::~BST() {
    destroyer(root);
}

template <class T>
BSTNode<T> *BST<T>::getRoot() {
    return root;
}

template <class T>
BSTNode<T> *BST<T>::inserter(BSTNode<T> *root,const T &data){
    if(root==NULL)
        return new BSTNode<T>(data, NULL, NULL);
    if(data < root->data)
        root->left = inserter(root->left,data);
    else if(data > root->data)
        root->right = inserter(root->right,data);
    return root;
}

template <class T>
void BST<T>::insert(const T &data) {
    root = inserter(root,data);
}

template <class T>
BSTNode<T> *BST<T>::getRightMin(BSTNode<T> *root) {
    BSTNode<T> *mn = root;
    if(mn->right==NULL)
        return NULL;
    mn = mn->right;
    while(mn->left!=NULL)
        mn = mn->left;
    return mn;
}
template <class T>
void BST<T>::remover(BSTNode<T> *& root,const T &data){
    if(root==NULL)
        return;
    else if(root->data > data)
        remover(root->left,data);
    else if(data > root->data)
        remover(root->right,data);
    else{
        if(root->left!=NULL && root->right!=NULL){
            BSTNode<T> *min = getRightMin(root);
            root->data = min->data;
            remover(root->right,root->data);
        }
        else{
            BSTNode<T> *trv = root;
            if(root->left!=NULL)
                root = root->left;
            else
                root = root->right;
            delete trv;
        }
    }    
}

template <class T>
void BST<T>::remove(const T &data) {
    remover(root,data);
}

template <class T>
BSTNode<T> *BST<T>::find(const T &data) {
    BSTNode<T> *trv = root;
    while(trv!=NULL){
        if(data == trv->data)
            return trv;
        if(data > trv->data){
            trv = trv->right;
            continue;
        }
        if(data < trv->data){
            trv = trv->left;
            continue;
        }
    }
    return trv;
}

template <class T>
void BST<T>::printInorder() {

    if (root == NULL) {
        std::cout << "{}" << std::endl;
    } else {
        std::cout << "{" << std::endl;
        printInorder(root);
        std::cout << std::endl << "}" << std::endl;
    }
}

template <class T>
void BST<T>::printInorder(BSTNode<T> *node) {

    if (node == NULL)
        return;

    printInorder(node->left);
    if (node->left) {
        std::cout << "," << std::endl;
    }
    std::cout << "\t" << node->data;
    if (node->right) {
        std::cout << "," << std::endl;
    }
    printInorder(node->right);
}

template <class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    destroyer(root);
    BSTNode<T> *trv = rhs.root;
    root = copier(trv);
    return *this;
}


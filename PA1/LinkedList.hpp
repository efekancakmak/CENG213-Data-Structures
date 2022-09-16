#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>

#include "Node.hpp"

template <class T>
class LinkedList
{
    public: // DO NOT CHANGE THIS PART.
        LinkedList();
        LinkedList(const LinkedList &obj);

        ~LinkedList();

        Node<T> *getFirstNode() const; //
        Node<T> *getHead() const;
        Node<T> *getTail() const;
        int getNumberOfNodes();
        bool isEmpty(); //

        void insertAtTheFront(const T &data); //
        void insertAtTheEnd(const T &data); //
        void insertAfterGivenNode(const T &data, Node<T> *prev); //

        void removeNode(Node<T> *node);
        void removeAllNodes();

        Node<T> *findNode(const T &data); //

        void printAllNodes();
        void printReversed();

        LinkedList &operator=(const LinkedList &rhs);

    private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

    private: // DO NOT CHANGE THIS PART.
        Node<T> *head;
        Node<T> *tail;
};

template<class T>
LinkedList<T>::LinkedList()
{
    Node<T> *front = new Node<T>;
    Node<T> *back = new Node<T>; 
    tail=front;
    head=back;
    head->next = tail;
    tail->prev = head;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList &obj)
{
    Node<T> *front = new Node<T>;
    Node<T> *back = new Node<T>;
    front->prev = NULL;
    back->next = NULL;
    tail=back;
    head=front;
    tail->prev = head;
    head->next = tail;
    Node<T> *trv = obj.getHead();
    Node<T> *faketail = obj.getTail();
    if(trv->next == faketail){
        return;
    }
    trv=trv->next;
    while(trv!=faketail){
        insertAtTheEnd(trv->element);
        trv=trv->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList()         
{
    removeAllNodes();
    delete head;
    delete tail;
    tail = head = NULL;
}

template<class T>
Node<T> * LinkedList<T>::getFirstNode() const
{
    if(head->next==tail)
        return NULL;
    return head->next;
}

template<class T>
Node<T> * LinkedList<T>::getHead() const   
{
    return head;
}

template<class T>
Node<T> * LinkedList<T>::getTail() const   
{
    return tail;
}

template<class T>
int LinkedList<T>::getNumberOfNodes()
{
    int sum=0;
    Node<T> *trv = head;
    if(trv->next==tail)
        return sum;
    trv=trv->next;
    while(trv!=tail){
        sum++;
        trv=trv->next;
    }
    return sum;
}

template<class T>
bool LinkedList<T>::isEmpty()  
{
    if(head->next==tail)
        return true;
    return false;
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data)
{
    Node<T> *nw= new Node<T>;
    nw->element=data;
    if(isEmpty()){
        head->next=nw;
        tail->prev=nw;
        nw->next = tail;
        nw->prev = head;
        return;
    }
    Node<T> *trv;
    trv=head->next;
    trv->prev=nw;
    nw->next=trv;
    head->next = nw;
    nw->prev = head;
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data)
{
    Node<T> *nw= new Node<T>;
    Node<T> *trv;
    nw->element=data;
    if(isEmpty()){
        nw->next=tail;
        nw->prev=head;
        tail->prev = nw;
        head->next = nw;
        return;
    }
    trv=tail->prev;
    tail->prev = nw;
    nw->next = tail;
    trv->next = nw;
    nw->prev = trv;
}

template<class T>
void LinkedList<T>::insertAfterGivenNode(const T &data, Node<T> *prev)
{   
    Node<T> *nw=new Node<T>;
    nw->element = data;
    if(prev == head){
        insertAtTheFront(data);
        return;
    }
    if(prev == tail->prev){
        insertAtTheEnd(data);
        return;
    }
    int check=0;
    Node<T> *trv = head->next;
    while(trv!=tail){
        if (trv==prev)
            check = 1;
        trv=trv->next;
    }
    if(check==0)
        return;
    nw->next=prev->next;
    nw->next->prev=nw;
    nw->prev=prev;
    prev->next=nw;
}
template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    if(isEmpty())
        return;
    Node<T> *trv=head->next;
    int check=0;
    while(trv!=tail){
        if(node==trv)
            check=1;
        trv=trv->next;
    }
    trv=NULL;
    if(check==0)
        return;
    if(head->next == tail->prev && head->next == node){
        delete node;
        node = NULL;
        head->next = tail;
        tail->prev = head;
        return;
    }
    if(head->next == node && node != tail->prev){ 
        head->next=node->next;
        node->next->prev=head;
        delete node;
        node = NULL;
        return;
    }
    if(tail->prev == node && node != head->next){ 
        tail->prev = node->prev;
        node->prev->next = tail;
        delete node;
        node = NULL;
        return;
    }
    if(node!=tail->prev && node!=head->next){ 
        node->prev->next=node->next;
        node->next->prev=node->prev;
        delete node;
        node = NULL;
        return;
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()  
{
    if(head->next==tail)
        return;
    Node<T> *pre=head;
    Node<T> *trv=head->next;
    while(trv!=tail){
        pre = trv;
        trv = trv->next;
        delete pre;
    }
    head->next=tail;
    tail->prev=head;
    pre = NULL;
    trv = NULL;
}

template<class T>
Node<T> * LinkedList<T>::findNode(const T &data)       
{
    if(head->next==tail)
        return NULL;
    Node<T> *trv = head->next;
    while(trv!=tail){
        if(trv->element == data)
            return trv;
        trv=trv->next;
    }
    return NULL;
}

template<class T>
void LinkedList<T>::printAllNodes()    
{
    if(head->next==tail)
        return;
    Node<T> *trv=head->next;
    while(trv!=tail){
        std::cout<<trv->element<<std::endl;
        trv=trv->next;
    }
}

template<class T>
void LinkedList<T>::printReversed()  
{
    if(head->next==tail)
        return;
    Node<T> *trv=tail->prev;
    while(trv!=head){
        std::cout<<trv->element<<std::endl;
        trv=trv->prev;
    }
}


template<class T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList &rhs) 
{
    removeAllNodes();
    Node<T> *trv = rhs.getHead();
    Node<T> *faketail = rhs.getTail();
    if(trv->next==faketail)
        return *this;
    trv = rhs.getFirstNode();
    while(trv!=faketail){
        insertAtTheEnd(trv->element);
        trv=trv->next;
    }
    return *this;
}

#endif //LINKED_LIST_HPP
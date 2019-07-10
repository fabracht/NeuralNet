//
//  linkedl.h
//  neuralnetwork1
//
//  Created by Fabricio Bracht on 2019-06-11.
//  Copyright © 2019 Fabricio Bracht. All rights reserved.
//

#ifndef linkedl_h
#define linkedl_h
#include <iostream>

using namespace std;

template<typename T>
struct Node {
    T value;
    Node* next;
};

template<typename T>
class linkedl {
private:
    int len = 0;
    Node<T>* head;
    void deletell(Node<T>*);
public:
    linkedl();
    virtual ~linkedl();
    linkedl(T[], int);
    Node<T>* copy(Node<T>* ll, Node<T>* &temp);
    void add(T);
    T remove();
    T remove(int);
    void print();
    bool isEmpty();
    T getnthvalue(size_t);
    T operator [](size_t);
};

// Deleting each ll
template<typename T>
void linkedl<T>::deletell(Node<T>* p) {
    while(p) {
        Node<T>* temp = p->next;
        delete p;
        p = temp;
    }
}

// Making a deep copy of the ll
template<typename T>
Node<T>* linkedl<T>::copy(Node<T>* ll, Node<T>* &temp) {
    if (!ll) {
        return nullptr;
    }
    copy(ll->next, temp);
    temp = cons(ll->data, temp);
    return temp;
}

template<typename T>
linkedl<T>::linkedl() {
    head = nullptr;
}

template<typename T>
linkedl<T>::linkedl(T list[], int length) {
    head = nullptr;
    for (int i = 0; i < length; ++i) {
        head = new Node<T>{list[i], head};
        len++;
    }
}

template<typename T>
linkedl<T>::~linkedl() {
    deletell(head);
    cout << "Destroyed linkedl!" << endl;
}

template<typename T>
void linkedl<T>::add(T data) {
    head = new Node<T>{data, head};
    len++;
}

template<typename T>
void linkedl<T>::print() {
    Node<T>* temp = head;
    while(temp) {
        cout << temp->value << "->";
        temp = temp->next;
    }
    cout << "nullptr" << endl;
}

template<typename T>
T linkedl<T>::remove() {
    T data = head->value;
    Node<T>* temp = head->next;
    delete head;
    head = temp;
    len--;
    return data;
}

template<typename T>
T linkedl<T>::remove(int position) {
    Node<T>* temp = head;
    T query;
    if (position == 0) {
        query = head->value;
        temp = head->next;
        delete head;
        head = temp;
        len--;
        return query;
    }
    for (int i = 0; temp != nullptr && i < position - 1; ++i) {
        temp = temp->next;
        if (temp->next == nullptr) {
            perror("Index out of bounds\n");
            exit(EXIT_FAILURE);
        }
    }
    query = temp->next->value;
    delete temp->next;
    temp->next = temp->next->next;
    len--;
    return query;
}

template<typename T>
bool linkedl<T>::isEmpty() {
    if(!head) {
        return true;
    }
    return false;
}

template<typename T>
T linkedl<T>::getnthvalue(size_t position) {
    if (!head) {
        perror("List is empty\n");
        exit(EXIT_FAILURE);
    }
    
    Node<T>* lead = head;
    int count = 0;
    while(lead != nullptr && count != position) {
        lead = lead->next;
        count++;
    }if (!lead) {
        perror("Item not found\n");
        exit(EXIT_FAILURE);
    }
    return lead->value;
}

template<typename T>
T linkedl<T>::operator [](size_t index) {
    return getnthvalue(index);
}


#endif /* linkedl_h */

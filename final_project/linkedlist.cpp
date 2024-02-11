#include "linkedlist.h"
#include <iostream>
using namespace std;

template <typename Item>
LinkedNode<Item>::LinkedNode(Item obj){
    this->obj = obj;
    next = NULL;
    prev = NULL;
}

template <typename Item>
LinkedList<Item>::LinkedList(){
    head = NULL;
    tail = NULL;
    N = 0;
}

template <typename Item>
LinkedList<Item>::~LinkedList(){
    for(int i = 0; i < N; i++){
        this->removeFirst();
    }
}

template <typename Item>
void LinkedList<Item>::addFirst(Item value){
    LinkedNode<Item>* node = new LinkedNode<Item>(value);
    node->next = head;
    if(N > 0){
        LinkedNode<Item>* oneAfter = head;
        oneAfter->prev = node;
    }
    this->head = node;
    int size = N;
    if(size == 0){
        this->tail = node;
    }
    N++;
}

template <typename Item>
void LinkedList<Item>::addLast(Item value){
    LinkedNode<Item>* node = new LinkedNode<Item>(value);
    node->prev = tail;
    if(N > 0){
        LinkedNode<Item>* oneBefore = tail;
        oneBefore->next = node;
    }
    this->tail = node;
    int size = N;
    if(size == 0){
        this->head = node;
    }  
    N++;
}


template<typename Item>
Item LinkedList<Item>::removeFirst(){
    Item ret;
    if(N > 0){
        LinkedNode<Item>* oldHead = head;
        ret = head->obj;
        head = head->next;
        delete oldHead;
        N--;
        if(N < 1){
            tail = NULL;
        }
    }
    return ret;
}

template<typename Item>
Item LinkedList<Item>::removeLast(){
    Item ret;
    if(N > 0){
        LinkedNode<Item>* oldTail = tail;
        ret = tail->obj;
        tail = tail->prev;
        delete oldTail;
        N--;
        if(N < 1){
            head = NULL;
        }
    }
    return ret;
}

template<typename Item>
Item* LinkedList<Item>::toArray(size_t* N){
    *N = this->N;
    Item* arr = new Item[this->N];
    LinkedNode<Item>* cursor = this->head;
    for(int i = 0; i < this->N; i++){
        arr[i] = cursor->obj;
        cursor = cursor->next;
    }
    return arr;
}

template<typename Item>
void LinkedList<Item>::print(){
    LinkedNode<Item>* cursor = this->head;
    while(cursor != NULL){
        cout << cursor->obj << " ==> ";
        cursor = cursor->next;
    }
    cout << "\n";
} 

template<typename Item>
Item LinkedList<Item>::remove(Item value){
    LinkedNode<Item>* cursor = this->head;
    while(cursor->obj != value){
        cursor = cursor->next;
    }
    if(cursor != this->head){
        LinkedNode<Item>* oneBefore = cursor->prev;
        oneBefore->next = cursor->next;
    } else {
        this->head = cursor->next;
    }
    if(cursor != this->tail){
        LinkedNode<Item>* oneAfter = cursor->next;
        oneAfter->prev = cursor->prev;
    } else {
        this->tail = cursor->prev;
    }
    Item ret;
    ret = cursor->obj;
    delete cursor;
    N--;
    return ret;
}

template<typename Item>
size_t LinkedList<Item>::size(){
    return N;
}

template<typename Item>
Item LinkedList<Item>::get(int N){
    LinkedNode<Item>* cursor = this->head;
    for(int i = 0; i < N; i++){
        cursor = cursor->next;
    }
    return cursor->obj;
}

template class LinkedNode<int>;
template class LinkedList<int>;
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
using namespace std;

template <typename Item>
class LinkedNode {
    public:
        Item obj;
        LinkedNode* next;
        LinkedNode* prev;
        LinkedNode(Item obj);
        ~LinkedNode(){};
};

template <typename Item> 
class LinkedList {
    private:
        // TODO: Add appropriate private variables
        LinkedNode<Item>* head;
        LinkedNode<Item>* tail;
        int N;
    public:
        LinkedList();
        ~LinkedList();
        
        /**
         * @brief Add an item to the beginning of the list
         * This method should run in constant time
         * 
         * @param value 
         */
        void addFirst(Item value);
        
        /**
         * @brief Remove and return the first item from the list, or return
         * null if nothing is there
         * This method should run in constant time
         * 
         * @return The first item in the list, or null if empty
         */
        Item removeFirst();
        
        /**
         * @brief  Add an item to the end of the list
         * This method should run in constant time
         * 
         * @param value Item to add
         */
        void addLast(Item value);

        /**
         * @brief Remove and return the last item from the list, or return null
         * if nothing is there
         * This method should run in constant time
         * 
         * @return The last item in the list, or null if empty
         */
        Item removeLast();
        
        /**
         * @brief Remove and return the first occurrence of an item from the 
         * list, if it exists.  Otherwise, return null
         * (This method does not have to run in constant time, and should
         * probably use a while or do while loop)
         * 
         * @param value The value to remove
         * @return The value if found, or null if not found
         */
        Item remove(Item value);
        
        /**
         * @brief Return how many elements are currently stored in the list.
         * This method should run in constant time.
         * The easiest way to do this is by storing a private variable 
         * that tracks the size as different operations are performed.
         * 
         * @return Number of elements stored in the list
         */
        size_t size();
        
        /**
         * @brief Loop through the linked list and return
         * the elements in an array
         * 
         * @param N Pointer to size of array
         * @return Item* 
         */
        Item* toArray(size_t* N);

        /**
         * @brief Print out the linked list as item1 => item2 => item3 => ...
         * 
         */
        void print();

        Item get(int N);

        
};

#endif
/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 * 
 * Evana Pradhan
 */

#include "pqueue-doublylinkedlist.h"
#include "util.h"
#include <iostream>

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
    // Setting up an empty priority queue
    count = 0;
    head = nullptr;
    tail = nullptr;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
    node *del;
    while (head != nullptr) {
        del = head;
        head = head->prev;
        delete del;
    }
}

int DoublyLinkedListPriorityQueue::size() {
    return count;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
    // Returning if count == 0 is True
    return count == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
    // Creating a new node with the given value
    node *newNode = new node;
    newNode->data = value;
    
    newNode->prev = newNode->next = nullptr;
    if (!isEmpty()) {
        tail->next = newNode;
        node *temp = tail;
        newNode->prev = temp;
    }
    tail = newNode;
    if (isEmpty()) {
        head = newNode;
    }
    count++;

    // for (node *p = head; p != nullptr; p = p->next) {
    //     cout << p->data << " -> ";
    // } 
    // cout << endl;
}

string DoublyLinkedListPriorityQueue::peek() {
    // Error handling for if the doubly-linked list is empty
    if (head == nullptr) {
        error("Cannot call peek() on an empty priority queue."); 
    }
    else  {
        string min = head->data;

        // Scanning thorugh the doubly linked list to find the prioritized value/minimum value
        for (node *p = head; p != nullptr; p = p->next) {
            if (min > (p->data)) {
                min = p->data;
            }
        }
        return min;

    }
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
    // Error handling for if the doubly-linked list is empty
    if (isEmpty())
        error("Cannot call dequeueMin() on empty priority queue.");
    
    /**************************************************************/
    /* Finding the priority node/node with minimum value */

    string sMin = head->data;

    // Edge case: if there is only one node in the doubly linked list
    if (count == 1) {
        node *del = head;
        head = nullptr;
        delete del;
        count --;
        return sMin;
    }

    // Setting up pointer to store min value
    node *min = head;

    // Scanning thorugh the doubly linked list to find the prioritized value/minimum value
    for (node *p = head; p != nullptr; p = p->next) {
        if ((min->data) > (p->data)) {
            min = p;
        }
    }
    sMin = min->data;
    // cout << "Min found: " << sMin << endl;

    /**************************************************************/
    /* Dequeueing the priority node/node with minimum value */

    // If priority node is the head
    if (min->prev == nullptr) {
        head = min->next;
        head->prev = nullptr;
        min->next = nullptr;

        delete min;
        count--;

        // for (node *p = head; p != nullptr; p = p->next)
        //     cout << p->data << " -> ";
        // cout << endl;
        return sMin;
    }

    // If priority node is the tail
    if (min->next == nullptr) {
        tail = min->prev;
        tail->next = nullptr;
        head->prev = nullptr;
        delete min;
        count--;

        // for (node *p = head; p != nullptr; p = p->next)
        //     cout << p->data << " -> ";
        // cout << endl;
        return sMin;
    }

    // If priority node is neither head nor tail/is in middle
    // cout << "min: " << min->data << endl;
    min->prev->next = min->next;
    min->next->prev = min->prev;

    min->next = min->prev = nullptr;
    delete min;

    count--;

    // for (node *p = head; p != nullptr; p = p->next) 
    //     cout << p->data << " -> ";
    // cout << endl;
    
    return sMin;

    // Using next and prev pointers
    // int c = 0;
    // int l = 0;
    // int r = count - 1;

    // while (l < r) {
    //     cout << l << ", " << r << endl;

    //     if (head->data < min) {
    //         min = head->data;
    //         cout << "first case ran: " << min << endl;
    //     }


    //     if (tail->data < min) {
    //         min = tail->data;
    //         cout << "second case ran: " << min << endl;
    //     }

    //     temp = head->next;
    //     head = temp;

    //     cout << "new head: " << head->data << endl;

    //     tail = tail->prev;
    //     cout << "new tail: " << tail->data << endl;

    //     l++;
    //     r--;
    // }
    // return min;
}

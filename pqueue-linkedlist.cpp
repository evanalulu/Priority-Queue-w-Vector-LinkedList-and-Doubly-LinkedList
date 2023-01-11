/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 * 
 * Evana Pradhan 
 * 
 */

#include <iostream>
#include "pqueue-linkedlist.h"
#include "util.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
    // Setting up an empty queue
    head = nullptr;
    count = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
    // Delete allocated memory for each node
    while (head != nullptr) {
        node *del = head;
        head = head->next; 
        delete del; 
    }
}

int LinkedListPriorityQueue::size() {
    return count;
}

bool LinkedListPriorityQueue::isEmpty() {
    // Returning if count == 0 is True
    return count == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
    // Creating new node with a given value
    node *newNode = new node;
    newNode->data = value;

    // Using two pointers: current and previous
    node *curr;
    node *prev;
    prev = nullptr;

    // Inserting the new node in the appropriate position
    for (curr = head; curr != nullptr; curr = curr->next) {
        if (curr->data > value) 
            break;
        prev = curr;
    }

    newNode->next = curr;
    if (prev != nullptr)
        prev->next = newNode;
    else    
        head = newNode;

    // Incrementing size
    count++;
}

string LinkedListPriorityQueue::peek() {
    // Error handling for if linked list is empty
    if (head == nullptr)
        error ("Cannot call peek() on an empty priority queue.");
    // Returning the head.data of linked list
    return head->data;
}

string LinkedListPriorityQueue::dequeueMin() {
    // Error handling for if linked list is empty
    if (head == nullptr)
        error ("Cannot call dequeueMin() on an empty priority queue.");

    // Storing the dequeue value
    string dequeueVal = head->data;

    // Storing head in a temporary node
    node *temp = head;

    // Assigning the new head as the next node in the linked list
    head = head->next;

    // Deleting allocated memory for the previous head
    delete temp;

    // Decrementing size
    count --;

    // Returning the stored dequeue value
    return dequeueVal;

}

/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 * 
 * Evana Pradhan 
 * 
 */

#include "pqueue-vector.h"
#include "util.h"

VectorPriorityQueue::VectorPriorityQueue() {
    // Setting up an empty queue
    pq;
}

VectorPriorityQueue::~VectorPriorityQueue() {
    pq.clear();
}

int VectorPriorityQueue::size() {
    // Returning the size of the vector using vector::size()
    return pq.size();
}

bool VectorPriorityQueue::isEmpty() {
    // TODO: Fill this in!
    return pq.size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
    // Appending value using vector::push_back() if vector pq is empty
    if (isEmpty())
        pq.push_back(value);

    // Else comparing and inserting using vector<string::insert(iterator, value)
    else {
        vector<string>::iterator it;
        it = pq.begin();

        for (int i = 0; i < pq.size(); i++) {
            // If value is lesser than or equal to the value at index i
            if (pq[i] > value or pq[i] == value) {
                pq.insert(it + i, value);
                break;
            
            // If value is greater than all values, insert at end
            } else if (i == pq.size() - 1) {
                pq.push_back(value);
                break;
            }
        }
    }
}

string VectorPriorityQueue::peek() {
    // Error handling for if vector pq is empty
    if (isEmpty())
        error("Cannot call peek() on an empty priority queue.");
    // Returning the first element of vector pq
    else
        return pq.front();
}

string VectorPriorityQueue::dequeueMin() {
    // Error handling for if vector pq is empty
    if (isEmpty())
        error ("Cannot call dequeueMin() on empty priority queue.");

    // Returning the first element then deleting it using vector::erase(position)
    else {
        string dequeueVal = pq.front();
        pq.erase(pq.begin());
        return dequeueVal;
    }
}

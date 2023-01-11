# Priority Queue with Vector, Linked List and Doubly Linked List

NOTE: Assignment for COSC 220 Whittier College

Implementing priority queue using vector, linked list and doubly-linked list in C++!


Priority queues are queues are queues that store data in a certain order given by some priority value. Since a built-in data structure for a priority queue does not exist in C++, we tried to make it using three different data structures.
  1. Sorted Vector: Whenever data is enqueued into the priority queue, it finds it correct position according to it's priority value, and enqueued into the correct position.
  2. Sorted Linked List: Whenever data is enqueued into the priority queue, it finds it correct position according to it's priority value, and enqueued into the correct position.
  3. Unsorted Doubly Linked List: Data is enqueues like a regular queue, but the data with the highest priority is searched for then dequeued when dequeuing an element.


The functions our priority queues can perform are:
  1. size: Returns how many elements are in the priority queue.
  2. isEmpty: Returns whether the priority queue is empty.
  3. enqueue: Inserts an element into the priority queue.
  4. peek: Returns, but does not remove, the lexicographically first string in the queue. If the queue is empty, peek should call error to report an error.
  5. dequeueMin: Returns and removes the lexicographically first string in the queue. If the queue is empty, dequeueMin should call error to report an error.


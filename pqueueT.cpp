//
//  pqqueuT.cpp
//  pqueueT
//
//  Created by Vince Mansel on 10/27/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

/*
 * ------------------
 * This file implements the priority queue class as a balanced sorted heap
 * of ElemTypes stored in priority order according to heap rules.  Priority is defined
 * by a client-supplied comparison function. This makes it easy
 * enqueue new elements in order, and as easy to dequeue the highest priority right off the top.
 *
 * Based on pqvector.cpp, Julie Zelenski, CS106
 */

#include "pqueueT.h"
#include "genlib.h"
#include <iostream>

/* Implementation notes: PQueueT class
 * ----------------------------------
 * The private section for the pqueueT.h looks like this:
 *
 *	Vector<ElemType> heap;
 */

template <typename ElemType>
void swapT(ElemType &one, ElemType &two);

template <typename ElemType>
int getHigherChildIndex(Vector<ElemType> &heap, int index, int (*cmpFn)(ElemType, ElemType));

/*
 * There is a dummy cell at the beginning of the vector
 */

template <typename ElemType>
PQueueT<ElemType>::PQueueT(int (*cmp)(ElemType, ElemType))
{
    // Attempt to initialize dummy cell produces a warning.
    // Handle dummy cell in is enqueue, dequeue, isEmpty, size
    
    cmpFn = cmp;
}

template <typename ElemType>
PQueueT<ElemType>::~PQueueT()
{
    heap.clear();
}

template <typename ElemType>
bool PQueueT<ElemType>::isEmpty()
{
    return (heap.size() == 0);  // Dummy cell is added on first enqueue
}

template <typename ElemType>
int PQueueT<ElemType>::size()
{
	if (heap.size() > 1)
        return (heap.size() - 1); // Dummy cell is added on first enqueue
    return 0;
}


/* Implementation notes: enqueue
 * -----------------------------
 */
template <typename ElemType>
void PQueueT<ElemType>::enqueue(ElemType newValue)
{
    //cout << "PQueueT::enqueue(" << newValue << "):";
    // Heap insert
    if (heap.size() == 0) { // Dummy cell is added on first enqueue
        heap.add(newValue);
    }
    heap.add(newValue);
    
    // Bubble up the newValue;
    
    int index = heap.size() - 1;
    while (index != 1) {
        if (cmpFn(newValue,heap[index/2]) > 0) { // TODO: Comparison Function
            swapT(heap[index], heap[index/2]);
            index /= 2;
        }
        else break;
    }
}


/* Implementation notes: dequeueMax
 * --------------------------------
 */
template <typename ElemType>
ElemType PQueueT<ElemType>::dequeue()
{
	//cout << "PQueueT::dequeueMax():";
    if (isEmpty()) {
        cout << endl;
        Error("PQueueT is empty");
    }
    
	ElemType value = heap[1];
    heap[1] = heap[heap.size()-1];
    heap.removeAt(heap.size()-1);
    int heapSize1 = heap.size()-1;
    
    // Trickle down the new root
    
    int index = 1;
    
    while (2*index < heapSize1) {
        //cout << endl << "index:*2:*2-1:heap.size()-1 >> " << index << ":" << 2*index << ":" << 2*index+1 << ":" << heap.size()-1 << "=" << endl;
        int higherChildIndex = getHigherChildIndex(heap,index,cmpFn);
        //cout << "heap[higherChildIndex] = heap[" << higherChildIndex << "] = " << heap[higherChildIndex] << endl;
        if (cmpFn(heap[higherChildIndex],heap[index]) > 0) { // TODO: Comparison Function
            //cout << "swapT " << heap[higherChildIndex] << "," << heap[index] << endl;
            swapT(heap[higherChildIndex],heap[index]);
            index = higherChildIndex;
        }
        else break;
    }
    // Quick Fix
    if (size() == 2) {
        if (cmpFn(heap[1],heap[2]) < 0) {  // TODO: Comparison Function
            swapT(heap[1], heap[2]);
        }
    }
    
    if (heap.size() == 1) { // Dummy cell is deleted on last dequeue
        heap.clear();
    }
    
    return value;
}

template <typename ElemType>
string PQueueT<ElemType>::implementationName()
{
	return "binary heap";
}

template <typename ElemType>
void PQueueT<ElemType>::printDebuggingInfo()
{
	cout << "------------------ START DEBUG INFO ------------------" << endl;
	cout << "PQueueT contains " << size() << " entries" << endl;
	for (int i = 1; i < heap.size(); i++) {
		//cout << heap[i] << " ";
    }
	cout << endl;
	cout << "------------------ END DEBUG INFO ------------------" << endl;
}

template <typename ElemType>
void swapT(ElemType &one, ElemType &two) {
    ElemType temp = one;
    one = two;
    two = temp;
}

// Assumes (2*index < heap.size() + 1) has been checked by calling function
template <typename ElemType>
int getHigherChildIndex(Vector<ElemType> &heap, int index, int (*cmpFn)(ElemType, ElemType)) {
    int result = 2*index;
    if (2*index + 1 <= heap.size() - 1) {
        if (cmpFn(heap[2*index],heap[2*index + 1]) < 0) // TODO: Comparison Function
            result += 1;
    }
    return result;
}

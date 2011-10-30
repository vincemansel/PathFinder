/*
 * File: PQueueT.h
 * --------------
 * Defines the interface for the templatized priority queue class. 
 * 
 * Based on initial starter file by Julie Zelenski, CS106, Fall 2007
 */
 

 
#ifndef _pqueueT_h
#define _pqueueT_h

#include "genlib.h"
#include "disallowcopy.h"
#include "vector.h"
#include "cmpFn.h"

/*
 * Class: PQueueT
 * -------------
 * This is the class for a priority queue.  This is not
 * simple FIFO queue, it is a priority queue, where elements are
 * retrieved in order of priority, not just by longevity in queue.
 * The elements are any type (primative, class or struct). 
 * Priority is defined by a client-supplied comparison function.
 * For primative types, the default OperatorCmp is used.
 */

template <typename ElemType>
class PQueueT 
{
  public:

	/*
	 * Constructor: PQueueT
	 * Usage: PQueueT<int> pq;
     *        PQueueT<cars> students(CompareCarsByHorsePower);
	 *        PQueueT<string> *ppq = new PQueueT<string>;
	 * ---------------------------------
	 * Initializes a new PQueueT to have no elements. The optional
     * argument is a function pointer that is applied to
     * two elements to determine their relative ordering (priority). The
     * comparison function should return 0 if the two elements
     * are equal, a negative result if first is "less than" second,
     * and a positive resut if first is "greater than" second. If
     * no argument is supplied, the OperatorCmp template is used as
     * a default, which applies the bulit-in < and == to the
     * elements to determine ordering.
	 */
	PQueueT(int (*cmpFn)(ElemType, ElemType) = OperatorCmp);
    
	/*
	 * Destructor: ~PQueueT
	 * Usage: delete ppq;
	 * ------------------
	 * Deallocates all the storage associated with this PQueueT.
	 */
	~PQueueT();


	/*
	 * Member function: isEmpty
	 * Usage: if (pq.isEmpty()) . . .
	 * -------------------------------
	 * Returns true if this PQueueT contains no elements.
	 */
	bool isEmpty();


	/*
	 * Member function: size
	 * Usage: nElemes = pq.size();
	 * ---------------------------
	 * Returns number of elements contained in this PQueueT.
	 */
	int size();


	/*
	 * Member function: enqueue
	 * Usage: pq.enqueue(val);
	 * -----------------------
	 * Adds the specified element to this PQueueT. No effort is made to
	 * avoid duplicates. 
	 */
	void enqueue(ElemType newElem);


	/*
	 * Member function: eequeueMax
	 * Usage: maxElem = pq.dequeueMax();
	 * ---------------------------------
	 * Removes the largest priority element from this PQueueT and returns it.
	 * If this PQueueT is empty, this function raises an error.
	 */
	ElemType dequeue();

	/*
	 * Member function: implementationName
	 * Usage: cout << pq.implementationName();
	 * ---------------------------------------
	 * This operation would not usually be included as part of the class
	 * class, but is included to help with analyzing and reporting results.
	 * This member function returns a string that describes the PQueueT
	 * implementation strategy ("sorted linked list", "vector", etc.).
	 */
	string implementationName();

	/*
	 * Member function: printDebuggingInfo
	 * Usage: pq.printDebuggingInfo();
	 * -------------------------------
	 * This operation would not usually be included as part of the class,
	 * but is included to give you a hook to put any helpful debugging
	 * print code (for example, something that prints the goopy details of
	 * the internal structure). You don't need to implement this routine and can
	 * ignore it entirely, but you may find it helpful to use as you are
	 * doing development.
	 */
	void printDebuggingInfo();

  private:

	// Disallow copying for all implementations as
	// a precaution
	DISALLOW_COPYING(PQueueT)
    
	Vector<ElemType> heap;
    int (*cmpFn) (ElemType, ElemType);

};

#include "pqueueT.cpp"

#endif
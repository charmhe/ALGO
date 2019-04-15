//
// Created by Charles on 2019-04-14.
//

#ifndef ALGO_MINHEAP_H
#define ALGO_MINHEAP_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <initializer_list>

using namespace std;

template< class T >
class minheap
{
public:
	vector<T> arr, sorted;
	unsigned int size = 0;
	minheap()= default;
	minheap (unsigned int i);
	minheap (initializer_list<T> param);
	unsigned int parent (unsigned int i )
	{ return i / 2; } // i/2 can be cast in C++
	unsigned int left (unsigned int i )
	{ return 2 * i; }
	unsigned int right (unsigned int i )
	{ return 2 * i + 1; }
	/*
	 * MAX-HEAPIFY of a heap.
	 * */
	void min_heapify(unsigned int i);
	void build_min_heap( );
	void print(int i);
	void print( );
	void print_sorted( );
	void sort( );
	void swap(unsigned int i, unsigned int j)
	{
		T temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}

};
#endif //ALGO_MINHEAP_H

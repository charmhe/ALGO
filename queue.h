//
//  queue.h
//  ALGO
//
//  Created by Charles on 2019-04-01.
//

#ifndef queue_h
#define queue_h

#include "heap.h"
#include <cmath>

template< class T >
class queue : public heap<T>
{
public:
	queue ( initializer_list<T> param );
	T max ()
	{ return this->arr[1]; }

//push the max element out
	T pop ()
	{
		T max = this->arr[1];
		this->arr[1] = this->arr[this->size];//No need for swap. Why?
		this->size -= 1;
		this->max_heapify(1);
		return max;
	}

	void increase_key(int i, T key)
	{
		if(key < this->arr[i]) cout<< "Error: Increase_Key: No need to increase this key." <<endl;
		this->arr[i] = key;
		while( i > 1 )
		{
			if (this->parent(i) < this->arr[i])
			{
				this->swap(i, this->parent(i));
				i = this->parent(i);
			}
		}
	}

	void insert(T key)
	{
		this->size+=1;
		this->arr.push_back(-INFINITY);
		increase_key(this->size, key);
	}
};

template< class T >
queue<T>::queue ( initializer_list<T> param )
{
	T ass;
	this->arr.push_back(ass);
	for ( auto ptr = param.begin(); ptr != param.end(); ptr++ )
	{
		this->arr.push_back(*ptr);
		this->size++;
	}
	this->build_max_heap();
};


#endif /* queue_h */

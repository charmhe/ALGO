//
// Created by Charles on 2019-03-31.
//

#ifndef ALGO_HEAP_H
#define ALGO_HEAP_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <initializer_list>

using namespace std;

template< class T >
class heap
{
public:
    vector<T> arr, sorted;
	unsigned int size = 0;
	heap(){ };
	heap (unsigned int i);
	heap (initializer_list<T> param);
	unsigned int parent (unsigned int i )
	{ return i / 2; } // i/2 can be cast in C++
	unsigned int left (unsigned int i )
	{ return 2 * i; }
	unsigned int right (unsigned int i )
	{ return 2 * i + 1; }
	/*
	 * MAX-HEAPIFY of a heap.
	 * */
	void max_heapify(unsigned int i);
	void build_max_heap( );
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

template< class T >
heap<T>::heap (unsigned int i):size(i) { }

template< class T >
heap<T>::heap ( initializer_list<T> param )
{
	T ass;
	arr.push_back(ass);
	for(auto ptr = param.begin(); ptr!=param.end(); ptr++)
	{
		arr.push_back(*ptr);
		size++;
	}
};

template< class T >
ostream& operator<<(ostream& os, const heap<T>& h)
{
	os<<"This heap:\n";
	int level = 1;
	int count = level;
	for(int i = 1; i <= h.size; i++)
	{
		auto ptr = h.arr[i];
		os.width(3); os<<std::left<<ptr<<" ";
		count-=1;
		if(count == 0)
		{
			os<<std::endl;
			for(count = 0; count < level; count++) os << "|  \\    ";
			os<<std::endl;
			level *= 2;
			count = level;
			continue;
		}
	}
	return os;
}

template <class T>
void heap<T>::print(int i)
{
	string os;
	os = os + "This heap @A[" + to_string(i) + "]:" + to_string((int)arr[i]) + "\n";
	int level = 1;
	int count = level;
	for(int i = 1; i <= size; i++)
	{
		auto ptr = arr[i];
		os += to_string((int)ptr) ; os += "  ";
		count-=1;
		if(count == 0)
		{
			os+="\n";
			for(count = 0; count < level; count++) os += "|  \\    ";
			os+="\n";
			level *= 2;
			count = level;
			continue;
		}
	}
	std::cout<<os<<std::endl;
}

template <class T>
void heap<T>::print( )
{
    string os;
    int level = 1;
    int count = level;
    for(int i = 1; i <= size; i++)
    {
        auto ptr = arr[i];
        os += to_string((int)ptr) ; os += "  ";
        count-=1;
        if(count == 0)
        {
            os+="\n";
            //avoiding to print unnecessary last branch
            if(i!=size) for(count = 0; count < level; count++) os += "|  \\  ";
            os+="\n";
            level *= 2;
            count = level;
            continue;
        }
    }
    std::cout<<os<<std::endl;
}

template <class T>
void heap<T>::print_sorted( )
{
    string os = "This heap after sorting: ";
    for(auto ptr = sorted.begin(); ptr!=sorted.end(); ptr++)
        os = os + to_string(*ptr) + " ";
    std::cout<<os<<std::endl;
}

template <class T>
void heap<T>::max_heapify(unsigned int i)
{
	unsigned int l = left(i);
	unsigned int r = right(i);
	unsigned int largest;
	if ( l <= size && arr[l] > arr[i] ) largest = l;
	else largest = i;
	if ( r <= size && arr[r] > arr[largest] ) largest = r;
	if ( largest != i )
	{
		swap(i, largest);
		max_heapify(largest);
	}
}

template <class T>
void heap<T>::build_max_heap( )
{
	for ( unsigned int i = size/2; i >= 1; i-- )
	{
		//print(i);
		max_heapify(i);
	}
}

template <class T>
void heap<T>::sort( )
{
    build_max_heap();
    for ( unsigned int i = size; i > 1; i-- )
    {
        swap(1, i);
        size -= 1;
        max_heapify(1);
//        std::cout<<arr[i]<<" pushed;"<< std::endl;
//        print();
        sorted.push_back(arr[i]);
    }
    sorted.push_back(arr[1]);
    print_sorted();
}




#endif //ALGO_HEAP_H

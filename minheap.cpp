//
// Created by Charles on 2019-04-14.
//

#include "minheap.h"


template< class T >
minheap<T>::minheap (unsigned int i):size(i) {
	size = i;
}

template< class T >
minheap<T>::minheap ( initializer_list<T> param )
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
ostream& operator<<(ostream& os, const minheap<T>& h)
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
void minheap<T>::print(int i)
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
void minheap<T>::print( )
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
void minheap<T>::print_sorted( )
{
	string os = "This heap after sorting: ";
	for(auto ptr = sorted.begin(); ptr!=sorted.end(); ptr++)
		os = os + to_string(*ptr) + " ";
	std::cout<<os<<std::endl;
}

template <class T>
void minheap<T>::min_heapify(unsigned int i)
{
	unsigned int l = left(i);
	unsigned int r = right(i);
	unsigned int smallest;
	if ( l <= size && arr[l] < arr[i] ) smallest = l;
	else smallest = i;
	if ( r <= size && arr[r] < arr[smallest] ) smallest = r;
	if ( smallest != i )
	{
		swap(i, smallest);
		min_heapify(smallest);
	}
}

template <class T>
void minheap<T>::build_min_heap( )
{
	for ( unsigned int i = size/2; i >= 1; i-- )
	{
		//print(i);
		min_heapify(i);
	}
}

template <class T>
void minheap<T>::sort( )
{
	build_min_heap();
	for ( unsigned int i = size; i > 1; i-- )
	{
		swap(1, i);
		size -= 1;
		min_heapify(1);
//        std::cout<<arr[i]<<" pushed;"<< std::endl;
//        print();
		sorted.push_back(arr[i]);
	}
	sorted.push_back(arr[1]);
	print_sorted();
}
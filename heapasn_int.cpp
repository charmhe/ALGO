//
// author @Charles.H. For 3340 asn3.
//

#include "heapasn.h"

bool heap_ASN::in_heap ( int id )
{
	return id <= size && id > 0;
}

double heap_ASN::min_key ()
{
	return arr[1];
}

int heap_ASN::min_id ()
{
	return 1;
}

double heap_ASN::key ( int id )
{
	return this->arr[id];
}

void heap_ASN::delete_min ()
{
//	cout << arr[size] << endl;
//	cout << arr[1] << endl;
	swap(1, size);
	arr.pop_back();
	size -= 1;
	min_heapify(1);
}

void heap_ASN::decrease_key ( int id, int new_key )
{
	if ( key(id) > new_key)
	{
		arr[id] = new_key;
		this->min_heapify(parent(id));
	}
	else return;
}

bool heap_ASN::isEmpty ()
{
	return ( this->arr ).size() == 1;
}

double heap_ASN::extractMin ()
{
	double min = this->min_key();
	this->delete_min();
	return min;
}

heap_ASN::heap_ASN ( initializer_list<int> param )
{
	int ass = 0;
	arr.push_back(ass);
	for(int ptr : param)
	{
		arr.push_back(ptr);
		size++;
	}
	build_min_heap();
}

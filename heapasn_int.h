//
// author @Charles.H. For 3340 asn3.
//

#ifndef DIJ_HEAPASN_H
#define DIJ_HEAPASN_H

#include "minheap.cpp"

class heap_ASN:public minheap<int>
{
public:
	heap_ASN(unsigned int i)
	{ }

	heap_ASN(initializer_list<int> param);

	bool isEmpty();

	bool in_heap(int id);
	double min_key();
	int min_id();
	double key(int id);
	void delete_min();
	void decrease_key(int id, int new_key);
	double extractMin();

};


#endif //DIJ_HEAPASN_H

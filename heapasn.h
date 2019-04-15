//
// author @Charles.H. For 3340 asn3.
//

#ifndef DIJ_HEAPASN_H
#define DIJ_HEAPASN_H

#include "minheap.cpp"

class heap_ASN:public minheap<pair<int, double>>
{
public:
	vector<pair<int, double>> arr;
	heap_ASN()= default;
	heap_ASN(initializer_list<pair<int, double >> param);
	heap_ASN(vector<pair<int, double >> param);
	void build_min_heap( );
	bool isEmpty();
	bool in_heap(int id);
	double min_key();
	int min_id();
	double key(int id);
	void delete_min();
	void decrease_key(int id, int new_key);
	double extractMin();
	void swap(unsigned int i, unsigned int j);
	void print( );
	void min_heapify(unsigned int i);
};


#endif //DIJ_HEAPASN_H
